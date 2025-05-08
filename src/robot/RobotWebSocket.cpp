#include "robot/RobotWebSocket.hpp"
#include <iostream>

RobotWebSocket::RobotWebSocket(const std::string& host, const std::string& secret, const std::string& businessId)
    : secret(secret), businessId(businessId) {
    url = "ws://" + host + ":8090/socket?businessId=" + businessId;
}

void RobotWebSocket::connect() {
    ws.setUrl(url);

    ws.setExtraHeaders({{"Secret", secret}});

    ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message && messageHandler) {
            messageHandler(msg->str);
        }
    });

    ws.start();
}

void RobotWebSocket::disconnect() {
    ws.stop();
}

void RobotWebSocket::onMessage(std::function<void(const std::string&)> handler) {
    messageHandler = std::move(handler);
}
