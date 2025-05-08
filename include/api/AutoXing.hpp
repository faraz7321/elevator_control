#pragma once
#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>

class AutoXingAPI {
public:
    AutoXingAPI();

    std::vector<nlohmann::json> loadTasks(const std::string& businessId);
    std::vector<nlohmann::json> loadPOIs(const std::string& businessId);

private:
    std::string app_code = "e63f72531dd14ea2aa9959730861cb10";
    std::string baseUrl = "https://apiglobal.autoxing.com/";

    cpr::Response makePostRequest(const std::string& endpoint, const std::string& body);
};