#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>

using namespace std;

void calculateGravitation(
    double mass1 = -1,                 // Mass of the first object (kg)
    double mass2 = -1,                 // Mass of the second object (kg)
    double distanceBetweenMasses = -1, // Distance between the centers of masses (m)
    double weight = -1,                // Weight of an object (N)
    double gravitationalPotentialEnergy = -1, // Gravitational potential energy (J)
    double accelerationDueToGravity = 9.8 // Gravitational acceleration near Earth (m/s²)
) {
    try {
        // Ensure at least some valid input is provided
        if (mass1 < 0 && mass2 < 0 && distanceBetweenMasses < 0 && weight < 0 && gravitationalPotentialEnergy < 0) {
            throw invalid_argument("Insufficient data provided for any calculation.");
        }

        // Calculate weight: W = m * g
        if (mass1 > 0) {
            double calculatedWeight = mass1 * accelerationDueToGravity;
            cout << "Weight of the Object: " << calculatedWeight << " N" << endl;
        }

        // Calculate gravitational potential energy: U = m * g * h
        if (mass1 > 0 && distanceBetweenMasses > 0) {
            double calculatedPotentialEnergy = mass1 * accelerationDueToGravity * distanceBetweenMasses;
            cout << "Gravitational Potential Energy: " << calculatedPotentialEnergy << " J" << endl;
        }

        // Calculate mass if weight is known: m = W / g
        if (weight > 0) {
            double calculatedMass = weight / accelerationDueToGravity;
            cout << "Mass of the Object (calculated from Weight): " << calculatedMass << " kg" << endl;
        }

        // Edge case: If no specific calculations could be done
        if (mass1 < 0 && mass2 < 0 && distanceBetweenMasses < 0 && weight < 0 && gravitationalPotentialEnergy < 0) {
            cout << "No sufficient data for any specific calculation." << endl;
        }
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error occurred." << endl;
    }
}

int main() {
    // Example use-cases with hardcoded values for testing
    calculateGravitation(10, -1, 5);         // Mass = 10 kg, height = 5 m
    calculateGravitation(-1, -1, -1, 98);   // Weight = 98 N
    calculateGravitation(50);               // Mass = 50 kg (calculates weight)
    //calculateGravitation();                 // No input, should handle gracefully, when there is no input applicaton won't crash.

    return 0;
}
