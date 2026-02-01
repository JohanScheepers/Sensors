import 'package:signals/signals.dart';
import '../model/sensor.dart';
import '../service/sensor_service.dart';

/// A view model for the sensor list screen.
class SensorListViewModel {
  /// The service that provides sensor data.
  final SensorService _sensorService = SensorService();

  /// A signal that holds the list of sensors.
  late final Signal<List<Sensor>> sensors;

  /// Creates a new instance of the sensor list view model.
  SensorListViewModel() {
    sensors = signal(_sensorService.getSensors());
  }
}
