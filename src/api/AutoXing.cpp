#include "api/AutoXing.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

std::vector<nlohmann::json> loadTasks(const std::string& businessId) {
    try {
        auto res = cpr::Post(
            cpr::Url{"https://apiglobal.autoxing.com/task/v1.0/list"},
            cpr::Header{{"Authorization", "APPCODE dd7afee0a068431abb2425ac622e70d2"}, {"Content-Type", "application/json"}},
            cpr::Body{nlohmann::json{
                {"executeStatus", 2},
                {"busiIds", {businessId}},
                {"dataItems", {"taskPts"}}
            }.dump()}
        );

        auto json = nlohmann::json::parse(res.text);
        return json["data"]["list"].get<std::vector<nlohmann::json>>();
    } catch (const std::exception& e) {
        std::cerr << "Failed to load tasks: " << e.what() << "\n";
        return {};
    }
}
