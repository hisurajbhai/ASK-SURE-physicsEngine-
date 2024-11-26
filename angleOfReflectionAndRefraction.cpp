#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// Define M_PI if it's not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to calculate quantities related to angle of reflection and refraction
void calculateAngles(
    double angleOfIncidence = -1,       // Angle of incidence (degrees)
    double refractiveIndex1 = -1,       // Refractive index of medium 1
    double refractiveIndex2 = -1,       // Refractive index of medium 2
    double speedOfLightMedium1 = -1,    // Speed of light in medium 1 (m/s)
    double speedOfLightMedium2 = -1,    // Speed of light in medium 2 (m/s)
    double criticalAngle = -1           // Critical angle for total internal reflection (degrees)
) {
    try {
        // Ensure at least one valid input is provided
        if (angleOfIncidence < 0 && refractiveIndex1 < 0 && refractiveIndex2 < 0 &&
            speedOfLightMedium1 < 0 && speedOfLightMedium2 < 0 && criticalAngle < 0) {
            throw invalid_argument("Insufficient data provided for calculations.");
        }

        // Calculate angle of reflection: angle of incidence equals angle of reflection
        if (angleOfIncidence >= 0) {
            cout << "Angle of Reflection: " << angleOfIncidence << " degrees" << endl;
        }

        // Snell's Law: sin(θ1) / sin(θ2) = n2 / n1
        if (angleOfIncidence >= 0 && refractiveIndex1 > 0 && refractiveIndex2 > 0) {
            double angleOfRefraction = asin((refractiveIndex1 / refractiveIndex2) * sin(angleOfIncidence * M_PI / 180.0)) * 180.0 / M_PI;
            cout << "Angle of Refraction: " << angleOfRefraction << " degrees" << endl;
        }

        // Critical Angle for Total Internal Reflection: sin(θc) = n2 / n1 (n1 > n2)
        if (refractiveIndex1 > 0 && refractiveIndex2 > 0 && refractiveIndex1 > refractiveIndex2) {
            double calculatedCriticalAngle = asin(refractiveIndex2 / refractiveIndex1) * 180.0 / M_PI;
            cout << "Critical Angle: " << calculatedCriticalAngle << " degrees" << endl;
        }

        // Speed of light relationship: v = c / n
        const double speedOfLightInVacuum = 3.0e8; // Speed of light in vacuum (m/s)
        if (refractiveIndex1 > 0 && speedOfLightMedium1 < 0) {
            double calculatedSpeed1 = speedOfLightInVacuum / refractiveIndex1;
            cout << "Speed of Light in Medium 1: " << calculatedSpeed1 << " m/s" << endl;
        }
        if (refractiveIndex2 > 0 && speedOfLightMedium2 < 0) {
            double calculatedSpeed2 = speedOfLightInVacuum / refractiveIndex2;
            cout << "Speed of Light in Medium 2: " << calculatedSpeed2 << " m/s" << endl;
        }

        // Check for missing values but no critical calculations skipped
        if (angleOfIncidence < 0 && refractiveIndex1 < 0 && refractiveIndex2 < 0 &&
            speedOfLightMedium1 < 0 && speedOfLightMedium2 < 0 && criticalAngle < 0) {
            cout << "Insufficient data for any specific calculation." << endl;
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "An unknown error occurred." << endl;
    }
}

int main() {
    // Example use-cases
    calculateAngles(30, 1.33, 1.0);                 // Case 1: Angle of incidence, refraction indices
    calculateAngles(45, 1.5, 1.0);                  // Case 2: With critical angle calculation
    calculateAngles(-1, 1.5, 1.33, -1, -1);         // Case 3: Speed of light calculation
    //calculateAngles();                            // Case 4: No input, should handle gracefully, if there is no input the application won't crash.

    return 0;
}
