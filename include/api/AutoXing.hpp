#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class RobotRestAPI;

struct Task {
    std::string id;
};

std::vector<nlohmann::json> loadTasks(const std::string& businessId);
