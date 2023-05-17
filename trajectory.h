#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <tuple>
#include <QString>

// Converts miles per hour (mph) to feet per second (fps)
double mphToFps(double velocity);

// Represents the maximum information for x and y trajectories
class MaxInfo {
private:
    int x_angle;
    double x_max;
    int y_angle;
    double y_max;

public:
    MaxInfo();
    void update(double potential_x_max, double potential_y_max, int potential_angle);
    QString print();
};

// Calculates the trajectories for angles 0 to 90 to determine what angles produce the maximum height and distance
MaxInfo trajectoriesAtEachAngle(double arm_length, double body_height, double arm_velocity_mph);

// Calculates the trajectory for a specific launch angle
std::tuple<double, double> trajectory(int launch_angle, double arm_length, double body_height, double arm_velocity_sq);

#endif // TRAJECTORY_H
