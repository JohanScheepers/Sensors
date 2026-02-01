import 'package:flutter/material.dart';
import 'package:signals_flutter/signals_flutter.dart';
import '../../viewmodel/sensor_detail_viewmodel.dart';
import '../widgets/custom_gauge.dart';
import 'package:fl_chart/fl_chart.dart';
import '../../model/sensor.dart';
import '../../model/sensor_value.dart';
import 'dart:math' as math; // Import dart:math

/// A screen that displays the details of a sensor.
class SensorDetailScreen extends StatefulWidget {
  /// The ID of the sensor to display.
  final String sensorId;

  /// Creates a new instance of the sensor detail screen.
  const SensorDetailScreen({super.key, required this.sensorId});

  @override
  State<SensorDetailScreen> createState() => _SensorDetailScreenState();
}

class _SensorDetailScreenState extends State<SensorDetailScreen> {
  late final SensorDetailViewModel _viewModel;

  @override
  void initState() {
    super.initState();
    _viewModel = SensorDetailViewModel(sensorId: widget.sensorId);
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Scaffold(
      appBar: AppBar(
        title: Watch((context) => Text(_viewModel.sensor.value.name)),
        backgroundColor: Colors.transparent,
        elevation: 0,
      ),
      body: Watch((context) {
        final sensor = _viewModel.sensor.value;
        return SingleChildScrollView(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              // Sensor Type Card
              Card(
                margin: const EdgeInsets.only(bottom: 16.0),
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12.0)),
                child: Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Text(
                    sensor.type,
                    style: theme.textTheme.headlineMedium?.copyWith(
                      color: theme.colorScheme.primary,
                    ),
                    textAlign: TextAlign.center,
                  ),
                ),
              ),

              // Current Value Display (Gauge or Text)
              Card(
                margin: const EdgeInsets.only(bottom: 16.0),
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12.0)),
                child: Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Column(
                    children: [
                      Text(
                        'Current Value',
                        style: theme.textTheme.titleLarge,
                      ),
                      const SizedBox(height: 20),
                      if (sensor.value is NumericValue)
                        CustomGauge(value: (sensor.value as NumericValue).value)
                      else if (sensor.value is StatusValue)
                        Text(
                          (sensor.value as StatusValue).value,
                          style: theme.textTheme.displaySmall?.copyWith(
                            fontWeight: FontWeight.bold,
                            color: theme.colorScheme.secondary,
                          ),
                        ),
                    ],
                  ),
                ),
              ),

              // History Chart Card
              Card(
                margin: const EdgeInsets.only(bottom: 16.0),
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12.0)),
                child: Padding(
                  padding: const EdgeInsets.all(16.0),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text(
                        'History',
                        style: theme.textTheme.titleLarge,
                      ),
                      const SizedBox(height: 10),
                      SizedBox(
                        height: 200, // Fixed height for the chart
                        child: _buildChart(sensor, theme),
                      ),
                    ],
                  ),
                ),
              ),
            ],
          ),
        );
      }),
    );
  }

  Widget _buildChart(Sensor sensor, ThemeData theme) {
    return LineChart(
      LineChartData(
        gridData: FlGridData(
          show: true,
          drawVerticalLine: true,
          getDrawingHorizontalLine: (value) => FlLine(
            color: theme.colorScheme.onSurface.withAlpha((255 * 0.1).toInt()), // Replaced withOpacity
            strokeWidth: 1,
          ),
          getDrawingVerticalLine: (value) => FlLine(
            color: theme.colorScheme.onSurface.withAlpha((255 * 0.1).toInt()), // Replaced withOpacity
            strokeWidth: 1,
          ),
        ),
        titlesData: FlTitlesData(
          show: true,
          rightTitles: const AxisTitles(
            sideTitles: SideTitles(showTitles: false),
          ),
          topTitles: const AxisTitles(
            sideTitles: SideTitles(showTitles: false),
          ),
          bottomTitles: AxisTitles(
            sideTitles: SideTitles(
              showTitles: true,
              reservedSize: 30,
              getTitlesWidget: (value, meta) {
                // Displaying only some labels for clarity
                if (value.toInt() % (sensor.dataPoints.length ~/ 3).clamp(1, 3) == 0 || value.toInt() == sensor.dataPoints.length - 1) {
                  return Padding(
                    padding: const EdgeInsets.only(top: 8.0),
                    child: Text(
                      'Day ${value.toInt() + 1}',
                      style: theme.textTheme.bodySmall,
                    ),
                  );
                }
                return const Text('');
              },
            ),
          ),
          leftTitles: AxisTitles(
            sideTitles: SideTitles(
              showTitles: true,
              reservedSize: 40,
              getTitlesWidget: (value, meta) {
                return Text(
                  value.toStringAsFixed(0),
                  style: theme.textTheme.bodySmall,
                );
              },
            ),
          ),
        ),
        borderData: FlBorderData(
          show: true,
          border: Border.all(color: theme.colorScheme.onSurface.withAlpha((255 * 0.3).toInt()), width: 1), // Replaced withOpacity
        ),
        minX: 0,
        maxX: (sensor.dataPoints.length - 1).toDouble(),
        minY: sensor.dataPoints.isNotEmpty ? sensor.dataPoints.reduce(math.min) * 0.8 : 0, // Dynamic minY
        maxY: sensor.dataPoints.isNotEmpty ? sensor.dataPoints.reduce(math.max) * 1.2 : 1.0, // Dynamic maxY
        lineBarsData: [
          LineChartBarData(
            spots: sensor.dataPoints.asMap().entries.map((e) {
              return FlSpot(e.key.toDouble(), e.value);
            }).toList(),
            isCurved: true,
            gradient: LinearGradient(
              colors: [
                theme.colorScheme.primary,
                theme.colorScheme.secondary,
              ],
            ),
            barWidth: 4,
            isStrokeCapRound: true,
            dotData: FlDotData(
              show: true,
              getDotPainter: (spot, percent, bar, index) {
                return FlDotCirclePainter(
                  radius: 3,
                  color: theme.colorScheme.secondary,
                  strokeColor: theme.colorScheme.onSurface,
                  strokeWidth: 1,
                );
              },
            ),
            belowBarData: BarAreaData(
              show: true,
              gradient: LinearGradient(
                colors: [
                  theme.colorScheme.primary.withAlpha((255 * 0.3).toInt()), // Replaced withOpacity
                  theme.colorScheme.secondary.withAlpha((255 * 0.1).toInt()), // Replaced withOpacity
                ],
                begin: Alignment.bottomCenter,
                end: Alignment.topCenter,
              ),
            ),
          ),
        ],
      ),
    );
  }
}
