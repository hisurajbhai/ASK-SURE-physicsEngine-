#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

class PhysicsQuestionEngine {
private:
    const std::regex numberRegex;
    const std::regex vectorRegex;
    std::map<std::string, std::vector<std::string> > physicsKeywords;

    std::string determineType(const std::string& value, const std::string& unit, const std::string& question) {
        std::string type = "unknown";
        
        struct TypeCheck {
            std::string type;
            std::vector<std::string> keywords;
        };

        std::vector<TypeCheck> typeChecks = {
            {"velocity", {"speed", "m/s", "velocity", "moving"}},
            {"acceleration", {"acceleration", "changing speed", "rate"}},
            {"force", {"force", "pushing", "pulling", "Newton"}},
            {"mass", {"mass", "weight", "kg"}},
            {"time", {"time", "duration", "seconds", "hours"}},
            {"distance", {"distance", "length", "meters", "km"}},
            {"energy", {"energy", "work", "joules"}}
        };

        for (size_t i = 0; i < typeChecks.size(); ++i) {
            for (size_t j = 0; j < typeChecks[i].keywords.size(); ++j) {
                if (unit.find(typeChecks[i].keywords[j]) != std::string::npos || 
                    question.find(typeChecks[i].keywords[j]) != std::string::npos) {
                    return typeChecks[i].type;
                }
            }
        }

        return type;
    }

public:
    PhysicsQuestionEngine() : 
        numberRegex("(-?\\d+(?:\\.\\d+)?)\s*([a-zA-Z]*(?:/[a-zA-Z]*)?)?"),
        vectorRegex("\\((-?\\d+(?:\\.\\d+)?),\s*(-?\\d+(?:\\.\\d+)?),\s*(-?\\d+(?:\\.\\d+)?)\\)") {
        
        physicsKeywords["velocity"] = std::vector<std::string>({"speed", "m/s", "velocity", "moving"});
        physicsKeywords["acceleration"] = std::vector<std::string>({"acceleration", "changing speed", "rate"});
        physicsKeywords["force"] = std::vector<std::string>({"force", "pushing", "pulling", "Newton"});
        physicsKeywords["mass"] = std::vector<std::string>({"mass", "weight", "kg"});
        physicsKeywords["time"] = std::vector<std::string>({"time", "duration", "seconds", "hours"});
        physicsKeywords["distance"] = std::vector<std::string>({"distance", "length", "meters", "km"});
        physicsKeywords["energy"] = std::vector<std::string>({"energy", "work", "joules"});
    }

    std::string extractQuestionData(const std::string& question) {
        std::stringstream jsonOutput;
        jsonOutput << "{\n";
        
        // Extract numbers
        jsonOutput << "  \"numerical_data\": [";
        bool firstNumber = true;
        std::sregex_iterator it(question.begin(), question.end(), numberRegex);
        std::sregex_iterator end;
        
        while (it != end) {
            std::string value = (*it)[1];
            std::string unit = (*it)[2];
            std::string type = determineType(value, unit, question);

            if (!firstNumber) jsonOutput << ", ";
            jsonOutput << "{\"value\": " << value 
                       << ", \"unit\": \"" << unit 
                       << "\", \"type\": \"" << type << "\"}";
            firstNumber = false;
            ++it;
        }
        jsonOutput << "],\n";
        
        // Extract vectors
        jsonOutput << "  \"vector_data\": [";
        bool firstVector = true;
        std::sregex_iterator vecIt(question.begin(), question.end(), vectorRegex);
        
        while (vecIt != end) {
            std::string type = "unknown";
            if (question.find("velocity") != std::string::npos) type = "velocity";
            if (question.find("acceleration") != std::string::npos) type = "acceleration";
            if (question.find("force") != std::string::npos) type = "force";

            if (!firstVector) jsonOutput << ", ";
            jsonOutput << "{\"x\": " << (*vecIt)[1] 
                       << ", \"y\": " << (*vecIt)[2] 
                       << ", \"z\": " << (*vecIt)[3] 
                       << ", \"type\": \"" << type << "\"}";
            firstVector = false;
            ++vecIt;
        }
        jsonOutput << "],\n";
        
        // Extract entities
        jsonOutput << "  \"physics_entities\": [";
        bool firstEntity = true;
        std::map<std::string, std::vector<std::string> >::iterator mapIt;
        for (mapIt = physicsKeywords.begin(); mapIt != physicsKeywords.end(); ++mapIt) {
            for (size_t i = 0; i < mapIt->second.size(); ++i) {
                if (question.find(mapIt->second[i]) != std::string::npos) {
                    if (!firstEntity) jsonOutput << ", ";
                    jsonOutput << "{\"type\": \"" << mapIt->first 
                               << "\", \"keyword\": \"" << mapIt->second[i] << "\"}";
                    firstEntity = false;
                    break;
                }
            }
        }
        jsonOutput << "]\n}";
        
        return jsonOutput.str();
    }

    void processQuestion(const std::string& question) {
        std::string result = extractQuestionData(question);
        std::cout << "Extracted Data:\n" << result << std::endl;
    }
};

int main() {
    PhysicsQuestionEngine engine;
    
    std::string sampleQuestion = "A car travels 50 km with a velocity of (3, 4, 5) m/s. Calculate the time taken.";
    engine.processQuestion(sampleQuestion);

    return 0;
}