#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

// Function to calculate quantities related to Newton's Laws of Motion
void calculateNewtonsLaws(map<string, double> params) {
    try {
        // Check for required parameters
        bool hasForce = params.count("force") > 0;
        bool hasMass = params.count("mass") > 0;
        bool hasAcceleration = params.count("acceleration") > 0;
        bool hasFriction = params.count("friction") > 0;
        bool hasCoefficientOfFriction = params.count("coefficient_of_friction") > 0;
        bool hasNormalForce = params.count("normal_force") > 0;

        if (!hasForce && !hasMass && !hasAcceleration && !hasFriction && 
            !hasCoefficientOfFriction && !hasNormalForce) {
            throw invalid_argument("No sufficient parameters provided for Newton's Laws calculations.");
        }

        // Declare variables
        double force = hasForce ? params["force"] : 0.0;
        double mass = hasMass ? params["mass"] : 0.0;
        double acceleration = hasAcceleration ? params["acceleration"] : 0.0;
        double friction = hasFriction ? params["friction"] : 0.0;
        double coefficient_of_friction = hasCoefficientOfFriction ? params["coefficient_of_friction"] : 0.0;
        double normal_force = hasNormalForce ? params["normal_force"] : 0.0;

        // Perform calculations
        if (hasMass && hasAcceleration) {
            // Force using F = ma
            force = mass * acceleration;
            cout << "Calculated Force (F = ma): " << force << " N" << endl;
        }

        if (hasForce && hasMass) {
            // Acceleration using a = F/m
            acceleration = force / mass;
            cout << "Calculated Acceleration (a = F/m): " << acceleration << " m/s^2" << endl;
        }

        if (hasForce && hasAcceleration) {
            // Mass using m = F/a
            mass = force / acceleration;
            cout << "Calculated Mass (m = F/a): " << mass << " kg" << endl;
        }

        if (hasCoefficientOfFriction && hasNormalForce) {
            // Friction force using f = μN
            friction = coefficient_of_friction * normal_force;
            cout << "Calculated Friction Force (f = μN): " << friction << " N" << endl;
        }

        if (hasFriction && hasNormalForce) {
            // Coefficient of friction using μ = f/N
            coefficient_of_friction = friction / normal_force;
            cout << "Calculated Coefficient of Friction (μ = f/N): " << coefficient_of_friction << endl;
        }

        if (hasForce && hasFriction) {
            // Net force considering friction
            double net_force = force - friction;
            cout << "Calculated Net Force (F_net = F - f): " << net_force << " N" << endl;
        }

        // If insufficient parameters for specific calculations
        if (!hasForce && !hasMass && !hasAcceleration && !hasFriction) {
            cout << "Insufficient parameters to calculate primary quantities of Newton's Laws." << endl;
        }

        cout << "Newton's Laws calculations completed successfully." << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Example usage
int main() {
    map<string, double> params = {
        {"mass", 15.0},               // Mass in kg
        {"acceleration", 6.0},       // Acceleration in m/s^2
        {"coefficient_of_friction", 0.3},
        {"normal_force", 40.0}       // Normal force in N
    };

    calculateNewtonsLaws(params);

    return 0;
}
