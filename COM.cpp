#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

using namespace std; // Use the standard namespace

struct Particle
{
    double mass;    // Mass of the particle
    double x = 0.0; // Default x-coordinate (for 1D cases)
    double y = 0.0; // Default y-coordinate (for 2D or 1D cases)
    double z = 0.0; // Default z-coordinate (for 3D or 2D cases)
};

// Function to calculate the center of mass
void calculateCenterOfMass(const vector<Particle> &particles)
{
    try
    {
        // Check if particle list is empty
        if (particles.empty())
        {
            throw invalid_argument("Particle list is empty. Cannot calculate Center of Mass.");
        }

        // Initialize accumulators
        double totalMass = 0.0;
        double xSum = 0.0, ySum = 0.0, zSum = 0.0;

        // Iterate through each particle
        for (const auto &particle : particles)
        {
            if (particle.mass <= 0)
            {
                throw invalid_argument("Invalid mass value encountered. Mass must be positive.");
            }
            totalMass += particle.mass;
            xSum += particle.mass * particle.x;
            ySum += particle.mass * particle.y;
            zSum += particle.mass * particle.z;
        }

        // Check for zero total mass
        if (totalMass == 0)
        {
            throw runtime_error("Total mass is zero. Center of Mass cannot be determined.");
        }

        // Calculate Center of Mass coordinates
        double xCOM = xSum / totalMass;
        double yCOM = ySum / totalMass;
        double zCOM = zSum / totalMass;

        // Detect dimensionality
        bool is1D = true, is2D = false, is3D = false;
        for (const auto &particle : particles)
        {
            if (particle.z != 0.0)
            {
                is1D = false;
                is2D = false;
                is3D = true;
                break;
            }
            if (particle.y != 0.0)
            {
                is1D = false;
                is2D = true;
            }
        }

        // Output results
        cout << fixed << setprecision(6);
        cout << "Total Mass of the System: " << totalMass << "\n";
        cout << "Center of Mass (x): " << xCOM << "\n";
        if (!is1D)
            cout << "Center of Mass (y): " << yCOM << "\n";
        if (is3D)
            cout << "Center of Mass (z): " << zCOM << "\n";

        // Output dimensionality
        if (is1D)
        {
            cout << "The system is 1D.\n";
        }
        else if (is2D)
        {
            cout << "The system is 2D.\n";
        }
        else if (is3D)
        {
            cout << "The system is 3D.\n";
        }
    }
    catch (const exception &e)
    {
        // Handle errors gracefully
        cerr << "Error: " << e.what() << "\n";
    }
}

int main()
{
    // Example test cases
    vector<Particle> particles = {
        {5.0, 2.0},      // Mass = 5, x = 2 (1D)
        {3.0, 4.0, 1.0}, // Mass = 3, x = 4, y = 1 (2D)
        {2.0, -1.0, 0.0} // Mass = 2, x = -1, y = 0 (2D)
    };

    // Call the function
    cout << "Case 1:\n";
    calculateCenterOfMass(particles);

    // 1D case
    vector<Particle> particles1D = {
        {2.0, 4.0}, // Mass = 2, x = 4 (1D)
        {3.0, -2.0} // Mass = 3, x = -2 (1D)
    };

    cout << "\nCase 2:\n";
    calculateCenterOfMass(particles1D);

    // 3D case
    vector<Particle> particles3D = {
        {10.0, 1.0, 2.0, 3.0}, // Mass = 10, x = 1, y = 2, z = 3
        {5.0, 0.0, -1.0, 2.0}, // Mass = 5, x = 0, y = -1, z = 2
    };

    cout << "\nCase 3:\n";
    calculateCenterOfMass(particles3D);

    return 0;
}
