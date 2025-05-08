#pragma once
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

class AutoXingAPI {
public:
    AutoXingAPI(const std::string& authToken);

    std::vector<nlohmann::json> loadTasks(const std::string& businessId);
    std::vector<nlohmann::json> loadPOIs(const std::string& businessId);

private:
    std::string authToken;
    std::string baseUrl = "https://apiglobal.autoxing.com/";

    cpr::Response makePostRequest(const std::string& endpoint, const std::string& body);
};