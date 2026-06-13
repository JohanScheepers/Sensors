# FCM Tokens Life Cycle

You want to refresh or confirm that token every single time the user opens the app and completes a login or session validation.

FCM tokens are not permanent. Firebase can rotate or invalidate a token for several reasons:

* The user updates the mobile app.
* The user restores the app onto a new phone from a backup.
* The user clears the app's local data or cache.
*The token simply expires naturally over time.
* To handle this cleanly, you want to build a "Find or Create" (Upsert) workflow on your backend.

## The App Lifecycle Flow

Instead of just blindly inserting a new row every time, your mobile app and backend should follow this lifecycle:

### 1. On the Mobile App (Every Startup/Login)
As soon as your app initializes and the user is authenticated, the app executes these steps:
1. It requests the current token from the Firebase SDK: messaging.getToken().
2. It captures the operating system (Platform.isIOS or Platform.isAndroid if you are using Flutter) to send as your device_type.
3. It sends an HTTP POST request to your backend endpoint (e.g., /api/devices/register-token) carrying the token, the device type, and the user's Firebase Auth JWT header.

### 2. On Your Backend (The Upsert Logic)
When your backend API receives that payload, it handles the database transaction safely using an upsert (Update or Insert) strategy.

Because a token is unique to a specific physical device, you don't want duplicate tokens clogging your database under different IDs, nor do you want a token stuck assigned to an old user if two different people log into the same tablet.

Here is how you handle it cleanly in SQL using MySQL’s native ON DUPLICATE KEY UPDATE syntax:
``` SQL
-- Assume your backend already verified the Firebase JWT and looked up your internal MySQL user_id = 42
INSERT INTO user_device_tokens (user_id, fcm_token, device_type)
VALUES (42, 'bk3rn156p9m...', 'android')
ON DUPLICATE KEY UPDATE 
    user_id = VALUES(user_id),
    updated_at = CURRENT_TIMESTAMP;
```

**Why this specific SQL query is perfect:**
* **Scenario A (First time logging in on this phone):** It creates a brand new row mapping User 42 to this token.
* **Scenario B (User opens the app the next day, token is identical):** The database catches the UNIQUE constraint on fcm_token. It skips creating a new row and simply updates the updated_at timestamp so you know the token is still alive and kicking.
* **Scenario C (User logs out, and a different user logs in on that same phone):** The token stays the same, but the query safely overwrites the user_id to the new logged-in user. This prevents the previous user from accidentally receiving notifications meant for the new user!

## When to clear tokens manually
While refreshing on login handles the arrival of tokens, you should also clean them up on Logout.

When a user taps "Log Out" in your mobile application, have the app make a quick API call to your backend like /api/devices/logout passing that specific FCM token before flushing the local state. Your backend should execute a quick delete:
```SQL
DELETE FROM user_device_tokens 
WHERE fcm_token = 'bk3rn156p9m...' AND user_id = 42;
```
This guarantees that if an employee hands their phone over to a colleague, critical sensor alerts stop routing to that physical device the exact second they log out.