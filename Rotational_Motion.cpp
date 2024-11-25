#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

// Function to calculate rotational motion parameters
void calculateRotationalMotion(
    double *momentOfInertia,     // kg·m²
    double *angularVelocity,     // rad/s
    double *angularAcceleration, // rad/s²
    double *torque,              // N·m
    double *mass,                // kg
    double *radius               // m
)
{
    try
    {
        // Check if we have enough data for calculations
        if (!momentOfInertia && (!mass || !radius))
        {
            throw invalid_argument("Insufficient data to calculate moment of inertia.");
        }

        if (!angularVelocity && !torque && !momentOfInertia)
        {
            throw invalid_argument("Insufficient data to calculate rotational motion quantities.");
        }

        // Calculated quantities
        double calculatedMomentOfInertia = 0.0;
        double rotationalKineticEnergy = 0.0;
        double angularMomentum = 0.0;

        // Calculate moment of inertia if not provided
        if (!momentOfInertia && mass && radius)
        {
            calculatedMomentOfInertia = 0.5 * (*mass) * pow(*radius, 2); // Assuming a solid cylinder
            momentOfInertia = &calculatedMomentOfInertia;
        }
        else if (momentOfInertia)
        {
            calculatedMomentOfInertia = *momentOfInertia;
        }

        // Print calculated or provided moment of inertia
        cout << "Moment of Inertia: " << calculatedMomentOfInertia << " kg·m²\n";

        // Calculate rotational kinetic energy if angular velocity is available
        if (angularVelocity && momentOfInertia)
        {
            rotationalKineticEnergy = 0.5 * (*momentOfInertia) * pow(*angularVelocity, 2);
            cout << "Rotational Kinetic Energy: " << rotationalKineticEnergy << " J\n";
        }
        else
        {
            cout << "Insufficient data to calculate rotational kinetic energy.\n";
        }

        // Calculate angular momentum if angular velocity and moment of inertia are available
        if (angularVelocity && momentOfInertia)
        {
            angularMomentum = (*momentOfInertia) * (*angularVelocity);
            cout << "Angular Momentum: " << angularMomentum << " kg·m²/s\n";
        }
        else
        {
            cout << "Insufficient data to calculate angular momentum.\n";
        }

        // Calculate torque if angular acceleration and moment of inertia are available
        if (angularAcceleration && momentOfInertia)
        {
            double calculatedTorque = (*momentOfInertia) * (*angularAcceleration);
            cout << "Torque: " << calculatedTorque << " N·m\n";
        }
        else if (!torque)
        {
            cout << "Insufficient data to calculate torque.\n";
        }
    }
    catch (const invalid_argument &e)
    {
        // Handle invalid arguments
        cerr << "Error: " << e.what() << "\n";
    }
    catch (const exception &e)
    {
        // Handle other exceptions
        cerr << "An unexpected error occurred: " << e.what() << "\n";
    }
}

int main()
{
    double angularVelocity = 10.0;    // rad/s
    double angularAcceleration = 5.0; // rad/s²
    double mass = 2.0;                // kg
    double radius = 0.5;              // m

    // Example usage of the function
    calculateRotationalMotion(
        nullptr, // Moment of inertia (optional)
        &angularVelocity,
        &angularAcceleration,
        nullptr, // Torque (optional)
        &mass,
        &radius);

    return 0;
}
