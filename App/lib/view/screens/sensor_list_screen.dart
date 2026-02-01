import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:signals_flutter/signals_flutter.dart';
import '../../viewmodel/sensor_list_viewmodel.dart';
import '../widgets/sensor_list_item.dart'; // Import the new SensorListItem

/// A screen that displays a list of sensors.
class SensorListScreen extends StatefulWidget {
  /// Creates a new instance of the sensor list screen.
  const SensorListScreen({super.key});

  @override
  State<SensorListScreen> createState() => _SensorListScreenState();
}

class _SensorListScreenState extends State<SensorListScreen> {
  final _viewModel = SensorListViewModel();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Sensor Dashboard'),
        centerTitle: false,
        backgroundColor: Colors.transparent, // Make AppBar transparent
        elevation: 0, // Remove shadow
      ),
      body: Watch((context) {
        final sensors = _viewModel.sensors.value;
        return ListView.builder(
          padding: const EdgeInsets.symmetric(vertical: 8.0), // Add vertical padding
          itemCount: sensors.length,
          itemBuilder: (context, index) {
            final sensor = sensors[index];
            return SensorListItem(
              sensor: sensor,
              onTap: () => context.go('/sensor/${sensor.id}'),
            );
          },
        );
      }),
    );
  }
}
