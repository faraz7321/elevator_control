#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <optional>

class RobotRestAPI {
public:
    RobotRestAPI(const std::string& host, const std::string& secret);

    nlohmann::json getMaps();
    nlohmann::json getMap(const std::string& mapId);
    nlohmann::json getCurrentMap();
    nlohmann::json setCurrentMap(const std::string& mapUid);
    nlohmann::json enterElevator(const std::vector<double>& coords, double ori);
    nlohmann::json moveTo(const std::vector<double>& coords, double ori);
    nlohmann::json setCurrentPose(const std::vector<double>& coords, double ori);

private:
    std::string robotHost;
    std::string secret;
    nlohmann::json makeRequest(const std::string& path, const std::optional<nlohmann::json>& body = std::nullopt);
    std::string substituteParams(const std::string& path, const std::map<std::string, std::string>& params);
};
