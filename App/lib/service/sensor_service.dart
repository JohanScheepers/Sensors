import '../model/sensor.dart';
import '../model/sensor_value.dart';

/// A service that provides sensor data.
class SensorService {
  /// A list of available sensors.
  final _sensors = [
    Sensor(id: 'damme', name: 'DamMe', type: 'Water Level', value: NumericValue(75), dataPoints: [20, 30, 50, 60, 75, 80, 70]),
    Sensor(id: 'fenceme', name: 'FenceMe', type: 'Voltage', value: NumericValue(8.5), dataPoints: [8.2, 8.3, 8.5, 8.4, 8.5, 8.6, 8.5]),
    Sensor(id: 'fridgeme', name: 'FridgeMe', type: 'Temperature', value: NumericValue(4), dataPoints: [3, 3.5, 4, 4.2, 4.1, 4, 3.9]),
    Sensor(id: 'gateme', name: 'GateMe', type: 'Status', value: StatusValue('Open'), dataPoints: [0, 0, 1, 1, 0, 1, 1]), // 1 for open, 0 for closed
    Sensor(id: 'moistureme', name: 'MoistureMe', type: 'Moisture', value: NumericValue(60), dataPoints: [50, 55, 58, 62, 60, 59, 61]),
    Sensor(id: 'rainme', name: 'RainMe', type: 'Rainfall', value: NumericValue(2), dataPoints: [0, 0.5, 1, 1.5, 2, 2.5, 2]),
    Sensor(id: 'switchme', name: 'SwitchMe', type: 'Status', value: StatusValue('Off'), dataPoints: [0, 1, 1, 0, 0, 1, 0]), // 1 for on, 0 for off
    Sensor(id: 'tankme', name: 'TankMe', type: 'Water Level', value: NumericValue(90), dataPoints: [80, 82, 85, 88, 90, 92, 91]),
    Sensor(id: 'tempme', name: 'TempMe', type: 'Temperature', value: NumericValue(25), dataPoints: [22, 23, 24, 25, 26, 25, 24]),
    Sensor(id: 'troughme', name: 'TroughMe', type: 'Water Level', value: NumericValue(40), dataPoints: [30, 35, 40, 45, 42, 40, 38]),
    Sensor(id: 'valveme', name: 'ValveMe', type: 'Status', value: StatusValue('Closed'), dataPoints: [1, 1, 0, 0, 1, 0, 1]), // 1 for open, 0 for closed
  ];

  /// Returns a list of all sensors.
  List<Sensor> getSensors() {
    return _sensors;
  }

  /// Returns a sensor by its [id].
  Sensor getSensorById(String id) {
    return _sensors.firstWhere((sensor) => sensor.id == id);
  }
}
