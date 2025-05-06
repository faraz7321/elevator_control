#pragma once
#include <ixwebsocket/IXWebSocket.h>
#include <functional>
#include <string>

class RobotWebSocket {
public:
    RobotWebSocket(const std::string& host, const std::string& secret, const std::string& businessId);
    void connect();
    void disconnect();

    void onMessage(std::function<void(const std::string&)> handler);

private:
    std::string url;
    std::string secret;
    std::string businessId;
    ix::WebSocket ws;
    std::function<void(const std::string&)> messageHandler;
};
