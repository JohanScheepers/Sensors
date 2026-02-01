/// A sealed class representing the value of a sensor.
sealed class SensorValue {}

/// A sensor value that is a number.
class NumericValue extends SensorValue {
  /// The numeric value.
  final double value;

  /// Creates a new instance of a numeric sensor value.
  NumericValue(this.value);
}

/// A sensor value that is a status string.
class StatusValue extends SensorValue {
  /// The status value.
  final String value;

  /// Creates a new instance of a status sensor value.
  StatusValue(this.value);
}
