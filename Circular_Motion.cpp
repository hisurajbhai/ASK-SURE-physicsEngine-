#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

struct MotionParameters
{
    double radius = 0.0;
    double angular_velocity = 0.0;
    double linear_velocity = 0.0;
    double angular_acceleration = 0.0;
    double time = 0.0;
    double mass = 0.0;

    double friction_coefficient = 0.0;
    double road_angle = 0.0;
    double gravity = 9.8;

    double pendulum_length = 0.0;
    double string_angle = 0.0;

    // Flags to check if parameter is set
    bool has_radius = false;
    bool has_angular_velocity = false;
    bool has_linear_velocity = false;
    bool has_angular_acceleration = false;
    bool has_time = false;
    bool has_mass = false;
    bool has_friction_coefficient = false;
    bool has_road_angle = false;
    bool has_pendulum_length = false;
    bool has_string_angle = false;
};

struct CalculationResult
{
    double value;
    string description;
    string error;
    bool is_success;

    static CalculationResult success(double result, const string &desc)
    {
        return {result, desc, "", true};
    }

    static CalculationResult failure(const string &error_message)
    {
        return {0.0, "", error_message, false};
    }
};

CalculationResult calculateCircularMotion(const MotionParameters &params)
{
    try
    {
        // Validate parameters
        if (!params.has_radius && !params.has_angular_velocity && !params.has_linear_velocity)
        {
            throw invalid_argument("Insufficient parameters for circular motion calculation");
        }

        double g = params.gravity;

        // Calculate angular velocity from linear velocity and radius
        if (params.has_radius && params.has_linear_velocity)
        {
            double angular_velocity = params.linear_velocity / params.radius;
            string description = "The angular velocity (ω) of the object is " + to_string(angular_velocity) + " radians/second.";
            return CalculationResult::success(angular_velocity, description);
        }

        // Calculate tangential acceleration
        if (params.has_radius && params.has_angular_acceleration)
        {
            double tangential_acceleration = params.radius * params.angular_acceleration;
            string description = "The tangential acceleration is " + to_string(tangential_acceleration) + " m/s².";
            return CalculationResult::success(tangential_acceleration, description);
        }

        // Calculate centripetal acceleration
        if (params.has_radius && params.has_angular_velocity)
        {
            double centripetal_acceleration = pow(params.angular_velocity, 2) * params.radius;
            string description = "The centripetal acceleration is " + to_string(centripetal_acceleration) + " m/s².";
            return CalculationResult::success(centripetal_acceleration, description);
        }

        // Additional calculations can be added similarly...

        return CalculationResult::failure("Unable to perform calculation with given parameters");
    }
    catch (const exception &e)
    {
        return CalculationResult::failure(string("Error: ") + e.what());
    }
}

int main()
{
    // Test Case 1: Calculate Angular Velocity from Linear Velocity and Radius
    MotionParameters params1;
    params1.radius = 5.0;
    params1.has_radius = true;
    params1.linear_velocity = 10.0;
    params1.has_linear_velocity = true;

    auto result1 = calculateCircularMotion(params1);
    if (result1.is_success)
    {
        cout << result1.description << endl;
    }
    else
    {
        cout << "Error: " << result1.error << endl;
    }

    // Test Case 2: Calculate Tangential Acceleration
    MotionParameters params2;
    params2.radius = 3.0;
    params2.has_radius = true;
    params2.angular_acceleration = 2.0;
    params2.has_angular_acceleration = true;

    auto result2 = calculateCircularMotion(params2);
    if (result2.is_success)
    {
        cout << result2.description << endl;
    }
    else
    {
        cout << "Error: " << result2.error << endl;
    }

    // Test Case 3: Calculate Centripetal Acceleration
    MotionParameters params3;
    params3.radius = 4.0;
    params3.has_radius = true;
    params3.angular_velocity = 3.0;
    params3.has_angular_velocity = true;

    auto result3 = calculateCircularMotion(params3);
    if (result3.is_success)
    {
        cout << result3.description << endl;
    }
    else
    {
        cout << "Error: " << result3.error << endl;
    }

    // Add more test cases as needed...

    return 0;
}
