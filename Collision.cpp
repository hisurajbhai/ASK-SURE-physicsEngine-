#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct CollisionParameters
{
    double mass1 = 0.0;           // Mass of first object
    double mass2 = 0.0;           // Mass of second object
    double velocity1 = 0.0;       // Initial velocity of first object
    double velocity2 = 0.0;       // Initial velocity of second object
    double final_velocity1 = 0.0; // Final velocity of first object
    double final_velocity2 = 0.0; // Final velocity of second object
    bool is_elastic = false;      // True for elastic, false for inelastic
    bool has_mass1 = false;
    bool has_mass2 = false;
    bool has_velocity1 = false;
    bool has_velocity2 = false;
    bool has_final_velocity1 = false;
    bool has_final_velocity2 = false;
    bool has_is_elastic = false;
};

struct CalculationResult
{
    string description;
    double value;
    bool is_success;

    static CalculationResult success(const string &desc, double result)
    {
        return {desc, result, true};
    }

    static CalculationResult failure(const string &desc)
    {
        return {desc, 0.0, false};
    }
};

CalculationResult calculateCollision(const CollisionParameters &params)
{
    try
    {
        // Validate that necessary parameters are provided
        if (!(params.has_mass1 && params.has_mass2 && params.has_velocity1 && params.has_velocity2 && params.has_is_elastic))
        {
            throw invalid_argument("Insufficient parameters provided for collision calculations.");
        }

        double m1 = params.mass1;
        double m2 = params.mass2;
        double v1 = params.velocity1;
        double v2 = params.velocity2;

        vector<CalculationResult> results;

        // Elastic collision calculations
        if (params.is_elastic)
        {
            double final_v1 = ((m1 - m2) / (m1 + m2)) * v1 + ((2 * m2) / (m1 + m2)) * v2;
            double final_v2 = ((2 * m1) / (m1 + m2)) * v1 + ((m2 - m1) / (m1 + m2)) * v2;

            results.push_back(CalculationResult::success("Final velocity of object 1 (elastic collision): ", final_v1));
            results.push_back(CalculationResult::success("Final velocity of object 2 (elastic collision): ", final_v2));

            // Kinetic energy before and after
            double initial_kinetic_energy = 0.5 * m1 * v1 * v1 + 0.5 * m2 * v2 * v2;
            double final_kinetic_energy = 0.5 * m1 * final_v1 * final_v1 + 0.5 * m2 * final_v2 * final_v2;

            results.push_back(CalculationResult::success("Initial kinetic energy (elastic collision): ", initial_kinetic_energy));
            results.push_back(CalculationResult::success("Final kinetic energy (elastic collision): ", final_kinetic_energy));
        }
        // Inelastic collision calculations
        else
        {
            double combined_velocity = (m1 * v1 + m2 * v2) / (m1 + m2);
            results.push_back(CalculationResult::success("Combined velocity after collision (inelastic collision): ", combined_velocity));

            // Kinetic energy before and after
            double initial_kinetic_energy = 0.5 * m1 * v1 * v1 + 0.5 * m2 * v2 * v2;
            double final_kinetic_energy = 0.5 * (m1 + m2) * combined_velocity * combined_velocity;

            results.push_back(CalculationResult::success("Initial kinetic energy (inelastic collision): ", initial_kinetic_energy));
            results.push_back(CalculationResult::success("Final kinetic energy (inelastic collision): ", final_kinetic_energy));

            // Energy loss
            double energy_loss = initial_kinetic_energy - final_kinetic_energy;
            results.push_back(CalculationResult::success("Energy lost during inelastic collision: ", energy_loss));
        }

        // Print all results
        for (const auto &result : results)
        {
            cout << result.description << result.value << endl;
        }

        return CalculationResult::success("Collision calculations completed successfully.", 0.0);
    }
    catch (const exception &e)
    {
        return CalculationResult::failure(string("Error: ") + e.what());
    }
}

int main()
{
    // Test case for elastic collision
    CollisionParameters elastic_params;
    elastic_params.mass1 = 5.0;
    elastic_params.has_mass1 = true;
    elastic_params.mass2 = 3.0;
    elastic_params.has_mass2 = true;
    elastic_params.velocity1 = 10.0;
    elastic_params.has_velocity1 = true;
    elastic_params.velocity2 = -5.0;
    elastic_params.has_velocity2 = true;
    elastic_params.is_elastic = true;
    elastic_params.has_is_elastic = true;

    auto result1 = calculateCollision(elastic_params);
    if (!result1.is_success)
    {
        cout << result1.description << endl;
    }

    // Test case for inelastic collision
    CollisionParameters inelastic_params;
    inelastic_params.mass1 = 2.0;
    inelastic_params.has_mass1 = true;
    inelastic_params.mass2 = 4.0;
    inelastic_params.has_mass2 = true;
    inelastic_params.velocity1 = 3.0;
    inelastic_params.has_velocity1 = true;
    inelastic_params.velocity2 = 1.0;
    inelastic_params.has_velocity2 = true;
    inelastic_params.is_elastic = false;
    inelastic_params.has_is_elastic = true;

    auto result2 = calculateCollision(inelastic_params);
    if (!result2.is_success)
    {
        cout << result2.description << endl;
    }

    return 0;
}
