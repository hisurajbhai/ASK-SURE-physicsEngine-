#include <iostream>
#include <cmath>
#include <stdexcept>
#include <map>
#include <string>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to calculate kinematics in 1D and 2D
void calculateKinematics(map<string, double> params) {
    try {
        // Check for required parameters
        bool hasInitialVelocity = params.count("initial_velocity") > 0;
        bool hasFinalVelocity = params.count("final_velocity") > 0;
        bool hasAcceleration = params.count("acceleration") > 0;
        bool hasTime = params.count("time") > 0;
        bool hasDisplacement = params.count("displacement") > 0;

        if (!hasInitialVelocity && !hasFinalVelocity && !hasAcceleration && !hasTime && !hasDisplacement) {
            throw invalid_argument("No sufficient parameters provided for kinematics calculations.");
        }

        // Declare variables for calculations
        double initial_velocity = hasInitialVelocity ? params["initial_velocity"] : 0.0;
        double final_velocity = hasFinalVelocity ? params["final_velocity"] : 0.0;
        double acceleration = hasAcceleration ? params["acceleration"] : 0.0;
        double time = hasTime ? params["time"] : 0.0;
        double displacement = hasDisplacement ? params["displacement"] : 0.0;

        // Extend to 2D kinematics (use vector components)
        if (params.count("angle")) {
            double angle = params["angle"]; // Angle in degrees
            double radians = angle * M_PI / 180.0; // Convert to radians

            double horizontal_velocity = initial_velocity * cos(radians);
            double vertical_velocity = initial_velocity * sin(radians);

            cout << "Horizontal Velocity: " << horizontal_velocity << " m/s" << endl;
            cout << "Vertical Velocity: " << vertical_velocity << " m/s" << endl;

            // Additional 2D calculations
        }

        cout << "Kinematics calculations completed successfully." << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Example usage
int main() {
    map<string, double> params = {
        {"initial_velocity", 15.0},
        {"acceleration", 9.8},
        {"time", 4.5},
        {"angle", 90.0}
    };

    calculateKinematics(params);

    return 0;
}
