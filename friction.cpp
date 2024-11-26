#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>

using namespace std;

void calculateFriction(
    double normalForce = -1,          // Normal force (N)
    double frictionalForce = -1,      // Frictional force (N)
    double coefficientOfFriction = -1,// Coefficient of friction (unitless)
    double mass = -1,                 // Mass of the object (kg)
    double velocity = -1,             // Velocity (m/s)
    double acceleration = -1          // Acceleration (m/s²)
) {
    try {
        // Check for negative values (invalid inputs)
        if (normalForce < 0 && frictionalForce < 0 && coefficientOfFriction < 0 && mass < 0 && velocity < 0 && acceleration < 0) {
            throw invalid_argument("Insufficient data provided for any calculation.");
        }

        // Frictional force calculation: F_friction = µ * N
        if (coefficientOfFriction > 0 && normalForce > 0) {
            double calculatedFriction = coefficientOfFriction * normalForce;
            cout << "Frictional Force: " << calculatedFriction << " N" << endl;
        } else if (frictionalForce > 0 && normalForce > 0) {
            double calculatedCoefficient = frictionalForce / normalForce;
            cout << "Coefficient of Friction: " << calculatedCoefficient << endl;
        }

        // Normal force from mass and acceleration: N = m * g (assuming g = 9.8 m/s²)
        if (mass > 0) {
            double calculatedNormalForce = mass * 9.8; // Gravity acceleration assumed as 9.8 m/s²
            cout << "Normal Force: " << calculatedNormalForce << " N" << endl;
        }

        // Kinetic energy calculation: KE = 0.5 * m * v²
        if (mass > 0 && velocity > 0) {
            double kineticEnergy = 0.5 * mass * velocity * velocity;
            cout << "Kinetic Energy: " << kineticEnergy << " J" << endl;
        }

        // Acceleration check for dynamics: F = m * a
        if (mass > 0 && acceleration > 0) {
            double netForce = mass * acceleration;
            cout << "Net Force: " << netForce << " N" << endl;
        }

        // Edge case: If no specific calculations could be done
        if (normalForce < 0 && frictionalForce < 0 && coefficientOfFriction < 0 && mass < 0 && velocity < 0 && acceleration < 0) {
            cout << "No sufficient data for any specific calculation." << endl;
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error occurred." << endl;
    }
}

int main() {
    // Example use-case
    calculateFriction(50, -1, 0.4);      // Example: Normal force and coefficient of friction
    calculateFriction(-1, -1, -1, 10, 5); // Example: Mass and velocity
    calculateFriction(100, 40);          // Example: Normal force and frictional force
    //calculateFriction();                 // Example: No input, should handle gracefully, for the test case where there is no input->checked the application is not crashing.

    return 0;
}
