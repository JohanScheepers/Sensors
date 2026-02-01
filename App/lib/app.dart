import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart'; // Import GoogleFonts
import 'core/app_router.dart';

/// This is the main application widget.
class SensorApp extends StatelessWidget {
  /// Creates a new instance of the sensor app.
  const SensorApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp.router(
      title: 'Sensor App',
      theme: ThemeData(
        useMaterial3: true, // Enable Material 3
        colorScheme: ColorScheme.fromSeed(
          seedColor: Colors.deepPurple,
          brightness: Brightness.dark, // Dark theme
        ),
        textTheme: GoogleFonts.montserratTextTheme(
          ThemeData.dark().textTheme, // Use Montserrat for text, adapt to dark theme
        ),
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      routerConfig: appRouter,
    );
  }
}
