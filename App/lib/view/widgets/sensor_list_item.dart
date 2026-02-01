import 'package:flutter/material.dart';
import '../../model/sensor.dart';
import '../../model/sensor_value.dart';

/// A widget that displays a single sensor item in a list.
class SensorListItem extends StatelessWidget {
  /// The sensor data to display.
  final Sensor sensor;

  /// Callback when the sensor item is tapped.
  final VoidCallback onTap;

  /// Creates a new instance of the sensor list item.
  const SensorListItem({
    super.key,
    required this.sensor,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Card(
      margin: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 8.0),
      elevation: 4.0,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12.0)),
      child: InkWell(
        onTap: onTap,
        borderRadius: BorderRadius.circular(12.0),
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    sensor.name,
                    style: theme.textTheme.titleLarge?.copyWith(
                      fontWeight: FontWeight.bold,
                      color: theme.colorScheme.primary,
                    ),
                  ),
                  const SizedBox(height: 4.0),
                  Text(
                    sensor.type,
                    style: theme.textTheme.bodyMedium?.copyWith(
                      color: theme.colorScheme.onSurface.withAlpha((255 * 0.7).toInt()), // Replaced withOpacity
                    ),
                  ),
                ],
              ),
              _buildValueDisplay(theme),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildValueDisplay(ThemeData theme) {
    final String displayValue;
    Color valueColor = theme.colorScheme.onSurface;

    if (sensor.value is NumericValue) {
      final numericValue = sensor.value as NumericValue;
      displayValue = numericValue.value.toStringAsFixed(1);
      // Example: color based on value range for numeric sensors
      if (numericValue.value > 70) {
        valueColor = Colors.redAccent;
      } else if (numericValue.value > 40) {
        valueColor = Colors.orangeAccent;
      } else {
        valueColor = Colors.greenAccent;
      }
    } else if (sensor.value is StatusValue) {
      final statusValue = sensor.value as StatusValue;
      displayValue = statusValue.value;
      // Example: color based on status
      if (statusValue.value.toLowerCase() == 'open' || statusValue.value.toLowerCase() == 'on') {
        valueColor = Colors.greenAccent;
      } else {
        valueColor = Colors.redAccent;
      }
    } else {
      displayValue = 'N/A';
    }

    return Text(
      displayValue,
      style: theme.textTheme.headlineSmall?.copyWith(
        fontWeight: FontWeight.bold,
        color: valueColor,
      ),
    );
  }
}
