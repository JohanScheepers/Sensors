import 'sensor_value.dart';

/// Represents a sensor with its data.
class Sensor {
  /// The unique identifier of the sensor.
  final String id;

  /// The name of the sensor.
  final String name;

  /// The type of the sensor.
  final String type;

  /// The current value of the sensor.
  final SensorValue value;

  /// A list of historical data points for the sensor.
  final List<double> dataPoints;

  /// Creates a new instance of a sensor.
  Sensor({
    required this.id,
    required this.name,
    required this.type,
    required this.value,
    required this.dataPoints,
  });
}
