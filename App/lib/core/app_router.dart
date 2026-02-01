import 'package:go_router/go_router.dart';
import '../view/screens/sensor_list_screen.dart';
import '../view/screens/sensor_detail_screen.dart';

/// The application's router configuration.
final appRouter = GoRouter(
  routes: [
    GoRoute(
      path: '/',
      builder: (context, state) => const SensorListScreen(),
    ),
    GoRoute(
      path: '/sensor/:id',
      builder: (context, state) {
        final id = state.pathParameters['id']!;
        return SensorDetailScreen(sensorId: id);
      },
    ),
  ],
);
