#pragma once
#include "RobotRestAPI.hpp"
#include "utils/messages.hpp"
#include <optional>
#include <memory>
#include <string>
#include <iostream>

enum class ConnectionState {
    NotConnected,
    Connecting,
    Connected,
    ConnectionFailed
};

class Robot {
public:
    Robot(std::string host, std::string secret, std::string businessId);

    void connect();
    void disconnect();

    ConnectionState socketState;
    std::optional<TrackedPose> trackedPose;
    std::optional<PlanningState> planningState;
    std::optional<Trajectory> trajectory;
    std::optional<AutoDoors> autoDoors;
    std::optional<GlobalPath> globalPath;

    std::shared_ptr<RobotRestAPI> restApi;

private:
    std::string robotHost;
    std::string robotSecret;
    std::string businessId;
    // WebSocket pointer (to be implemented with your preferred library)
};
