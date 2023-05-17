#include "trajectory.h"
#include "cmath"
#include <tuple>
#include <QString>

const double GRAVITY_FPS_SQUARED = 32.17404855643;

// Roundoff Error Mitigation
// 0.015625 was chosen because it can be represented exactly in binary
const double X_STEP = 0.015625;

MaxInfo::MaxInfo() : x_angle(0), x_max(0.0), y_angle(0), y_max(0.0) {}

void MaxInfo::update(double potential_x_max, double potential_y_max, int potential_angle) {
    if (potential_x_max > x_max) {
        x_angle = potential_angle;
        x_max = potential_x_max;
    }
    if (potential_y_max > y_max) {
        y_angle = potential_angle;
        y_max = potential_y_max;
    }
}

QString MaxInfo::print() {
    return QString("X: %1 %2, Y: %3 %4").arg(x_angle).arg(x_max).arg(y_angle).arg(y_max);
}

MaxInfo trajectoriesAtEachAngle(double arm_length, double body_height, double arm_velocity_mph) {
    double arm_velocity = mphToFps(arm_velocity_mph);
    double arm_velocity_sq = std::pow(arm_velocity, 2);

    MaxInfo max_info;
    for (int launch_angle = 0; launch_angle <= 90; ++launch_angle) {
        double x_max, y_max;
        std::tuple<double, double> maxes = trajectory(launch_angle, arm_length, body_height, arm_velocity_sq);
        max_info.update(std::get<0>(maxes), std::get<1>(maxes), launch_angle);
    }
    return max_info;
}

std::tuple<double, double> trajectory(int launch_angle, double arm_length, double body_height, double arm_velocity_sq) {
    double launch_angle_rad = static_cast<double>(launch_angle) * M_PI / 180.0;
    double launch_angle_cos = std::cos(launch_angle_rad);
    double launch_angle_tan = std::tan(launch_angle_rad);
    double launch_angle_cos_sq = std::pow(launch_angle_cos, 2);
    double arm_height = launch_angle_cos * arm_length;
    double launch_height = body_height + arm_height;
    double y = launch_height;
    double y_max = y;

    // Compute trajectory of current launch angle
    double x = 0.0;
    while (y >= 0.0) {
        double denominator = 2.0 * arm_velocity_sq * launch_angle_cos_sq;
        double x_sq = std::pow(x, 2);
        y = launch_height + (x * launch_angle_tan) - GRAVITY_FPS_SQUARED * (x_sq / denominator);
        y_max = (y > y_max) ? y : y_max;
        x += X_STEP;
    }

    // Walk x back to when y was above 0
    x -= X_STEP;
    double launch_x = std::sin(launch_angle_rad) * arm_length;
    double x_max = x - launch_x;
    return std::make_tuple(x_max, y_max);
}

double mphToFps(double velocity) {
    return (velocity * 5280.0) / (60.0 * 60.0);
}
