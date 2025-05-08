#include "AutoXing.hpp"

// Constructor to initialize the auth token
AutoXingAPI::AutoXingAPI(const std::string& authToken) : authToken(authToken) {}

// Helper function to make POST requests
cpr::Response AutoXingAPI::makePostRequest(const std::string& endpoint, const std::string& body) {
    cpr::Response response = cpr::Post(
        cpr::Url{baseUrl + endpoint},
        cpr::Header{{"Authorization", "APPCODE " + authToken}, {"Content-Type", "application/json"}},
        cpr::Body{body}
    );
    return response;
}

// Method to load tasks from AutoXing API
std::vector<nlohmann::json> AutoXingAPI::loadTasks(const std::string& businessId) {
    try {
        nlohmann::json request_body = {
            {"executeStatus", 2},
            {"busiIds", {businessId}},
            {"dataItems", {"taskPts"}}
        };

        cpr::Response response = makePostRequest("task/v1.0/list", request_body.dump());

        if (response.status_code == 200) {
            nlohmann::json json_response = nlohmann::json::parse(response.text);
            return json_response["data"]["list"].get<std::vector<nlohmann::json>>();
        } else {
            std::cerr << "Failed to load tasks. Status code: " << response.status_code << std::endl;
            return {};
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return {};
    }
}

// Method to load POIs from AutoXing API
std::vector<nlohmann::json> AutoXingAPI::loadPOIs(const std::string& businessId) {
    try {
        nlohmann::json request_body = {
            {"businessId", businessId},
            {"floor", nullptr}  // Include more parameters as needed
        };

        cpr::Response response = makePostRequest("geo/poi/list", request_body.dump());

        if (response.status_code == 200) {
            nlohmann::json json_response = nlohmann::json::parse(response.text);
            return json_response["data"]["list"].get<std::vector<nlohmann::json>>();
        } else {
            std::cerr << "Failed to load POIs. Status code: " << response.status_code << std::endl;
            return {};
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading POIs: " << e.what() << std::endl;
        return {};
    }
}
