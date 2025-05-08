#include "robot/useRobot.hpp"
#include "robot/RobotWebSocket.hpp"

Robot::Robot(std::string host, std::string secret, std::string businessId)
    : robotHost(std::move(host)),
      robotSecret(std::move(secret)),
      businessId(std::move(businessId)),
      socketState(ConnectionState::NotConnected) {
    restApi = std::make_shared<RobotRestAPI>(robotHost, robotSecret);
    webSocket = std::make_shared<RobotWebSocket>(robotHost, robotSecret);
}

void Robot::connect() {
    socketState = ConnectionState::Connecting;

    socketState = ConnectionState::Connected;
    std::cout << "[Robot] Connected to WebSocket (stub)\n";
}

void Robot::disconnect() {
    socketState = ConnectionState::NotConnected;
    std::cout << "[Robot] Disconnected (stub)\n";
}
