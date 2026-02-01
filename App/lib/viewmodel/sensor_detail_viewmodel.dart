import 'package:signals/signals.dart';
import '../model/sensor.dart';
import '../service/sensor_service.dart';

/// A view model for the sensor detail screen.
class SensorDetailViewModel {
  /// The service that provides sensor data.
  final SensorService _sensorService = SensorService();

  /// The signal that holds the sensor.
  late final Signal<Sensor> sensor;

  /// Creates a new instance of the sensor detail view model.
  SensorDetailViewModel({required String sensorId}) {
    sensor = signal(_sensorService.getSensorById(sensorId));
  }
}
