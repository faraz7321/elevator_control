#include "robot/RobotRestAPI.hpp"
#include <cpr/cpr.h>
#include <iostream>

RobotRestAPI::RobotRestAPI(const std::string& host, const std::string& secret)
    : robotHost(host), secret(secret) {}

nlohmann::json RobotRestAPI::makeRequest(const std::string& path, const std::optional<nlohmann::json>& body) {
    std::string url = "http://" + robotHost + ":8090/" + path;
    try {
        if (body.has_value()) {
            auto res = cpr::Post(
                cpr::Url{url},
                cpr::Header{{"Secret", secret}, {"Content-Type", "application/json"}},
                cpr::Body{body->dump()}
            );
            return nlohmann::json::parse(res.text);
        } else {
            auto res = cpr::Get(
                cpr::Url{url},
                cpr::Header{{"Secret", secret}}
            );
            return nlohmann::json::parse(res.text);
        }
    } catch (const std::exception& e) {
        std::cerr << "Request failed: " << e.what() << "\n";
        return nlohmann::json{{"error", "request failed"}};
    }
}

nlohmann::json RobotRestAPI::getMaps() {
    return makeRequest("maps");
}

nlohmann::json RobotRestAPI::getMap(const std::string& mapId) {
    return makeRequest("maps/" + mapId);
}

nlohmann::json RobotRestAPI::getCurrentMap() {
    return makeRequest("chassis/current-map");
}

nlohmann::json RobotRestAPI::setCurrentMap(const std::string& mapUid) {
    nlohmann::json payload = {
        {"map_uid", mapUid}
    };
    return makeRequest("chassis/current-map", payload);
}

nlohmann::json RobotRestAPI::enterElevator(const std::vector<double>& coords, double ori) {
    nlohmann::json payload = {
        {"creator", "robobridge"},
        {"type", "standard"},
        {"target_x", coords[0]},
        {"target_y", coords[1]},
        {"target_ori", ori}
    };
    return makeRequest("chassis/moves", payload);
}

nlohmann::json RobotRestAPI::moveTo(const std::vector<double>& coords, double ori) {
    return enterElevator(coords, ori);  // Same endpoint/logic
}

nlohmann::json RobotRestAPI::setCurrentPose(const std::vector<double>& coords, double ori) {
    nlohmann::json payload = {
        {"position", {coords[0], coords[1], 0}},
        {"ori", ori}
    };
    return makeRequest("chassis/pose", payload);
}
