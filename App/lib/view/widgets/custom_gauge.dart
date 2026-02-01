import 'package:flutter/material.dart';
import 'dart:math' as math;

/// A custom gauge widget to display a sensor value with animation and enhanced visuals.
class CustomGauge extends StatefulWidget {
  /// The value to display on the gauge.
  final double value;

  /// The minimum value of the gauge.
  final double min;

  /// The maximum value of the gauge.
  final double max;

  /// Creates a new instance of the custom gauge.
  const CustomGauge({
    super.key,
    required this.value,
    this.min = 0,
    this.max = 100,
  });

  @override
  State<CustomGauge> createState() => _CustomGaugeState();
}

class _CustomGaugeState extends State<CustomGauge> with SingleTickerProviderStateMixin {
  late AnimationController _controller;
  late Animation<double> _animation;

  @override
  void initState() {
    super.initState();
    _controller = AnimationController(
      vsync: this,
      duration: const Duration(milliseconds: 500),
    );
    _animation = Tween<double>(begin: widget.min, end: widget.value).animate(_controller)
      ..addListener(() {
        setState(() {}); // Redraw the gauge when the animation value changes
      });
    _controller.forward();
  }

  @override
  void didUpdateWidget(covariant CustomGauge oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.value != widget.value) {
      _animation = Tween<double>(begin: oldWidget.value, end: widget.value).animate(_controller);
      _controller
        ..reset()
        ..forward();
    }
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: 200,
      height: 200,
      child: CustomPaint(
        painter: _GaugePainter(
          value: _animation.value,
          min: widget.min,
          max: widget.max,
          theme: Theme.of(context),
        ),
        child: Center(
          child: Text(
            _animation.value.toStringAsFixed(1),
            style: Theme.of(context).textTheme.headlineLarge?.copyWith(
                  fontWeight: FontWeight.bold,
                  color: _GaugePainter._getForegroundColor(_animation.value, widget.max, Theme.of(context)),
                ),
          ),
        ),
      ),
    );
  }
}

class _GaugePainter extends CustomPainter {
  final double value;
  final double min;
  final double max;
  final ThemeData theme;

  _GaugePainter({
    required this.value,
    required this.min,
    required this.max,
    required this.theme,
  });

  @override
  void paint(Canvas canvas, Size size) {
    final center = Offset(size.width / 2, size.height / 2);
    final radius = math.min(size.width / 2, size.height / 2);
    const startAngle = -math.pi * 0.75;
    const sweepAngle = math.pi * 1.5;

    // Background arc paint
    final backgroundPaint = Paint()
      ..color = theme.colorScheme.onSurface.withAlpha((255 * 0.1).toInt()) // Replaced withOpacity
      ..style = PaintingStyle.stroke
      ..strokeWidth = 20
      ..strokeCap = StrokeCap.round;

    // Draw the background arc
    canvas.drawArc(
      Rect.fromCircle(center: center, radius: radius),
      startAngle,
      sweepAngle,
      false,
      backgroundPaint,
    );

    // Foreground arc paint with gradient
    final foregroundPaint = Paint()
      ..shader = SweepGradient(
        startAngle: startAngle,
        endAngle: startAngle + sweepAngle,
        colors: [
          _getForegroundColor(min, max, theme),
          _getForegroundColor(value, max, theme),
        ],
        stops: [(value - min) / (max - min), (value - min) / (max - min)],
        transform: GradientRotation(startAngle),
      ).createShader(Rect.fromCircle(center: center, radius: radius))
      ..style = PaintingStyle.stroke
      ..strokeWidth = 20
      ..strokeCap = StrokeCap.round
      ..maskFilter = const MaskFilter.blur(BlurStyle.normal, 5); // Add shadow

    // Calculate the sweep angle for the value
    final valueAngle = (value - min) / (max - min) * sweepAngle;

    // Draw the foreground arc
    canvas.drawArc(
      Rect.fromCircle(center: center, radius: radius),
      startAngle,
      valueAngle,
      false,
      foregroundPaint,
    );
  }

  @override
  bool shouldRepaint(covariant _GaugePainter oldDelegate) {
    return oldDelegate.value != value || oldDelegate.theme != theme;
  }

  static Color _getForegroundColor(double value, double max, ThemeData theme) {
    // Color logic based on value
    if (value < max * 0.3) {
      return Colors.blueAccent;
    } else if (value < max * 0.7) {
      return Colors.orangeAccent;
    } else {
      return Colors.redAccent;
    }
  }
}
