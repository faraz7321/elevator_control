#include "elevator/LutzElevator.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

LutzElevator::LutzElevator(const std::string& host) : elevatorHost(host) {}

std::string LutzElevator::getHost() const {
    return elevatorHost;
}

std::optional<std::string> LutzElevator::currentFloor() {
    try {
        auto res = cpr::Get(cpr::Url{"http://" + elevatorHost + ":1880/elevator/status"});
        auto status = nlohmann::json::parse(res.text);
        return std::to_string(status["currentFloor"].get<int>());
    } catch (const std::exception& e) {
        std::cerr << "Error at LUTZ elevator status API call: " << e.what() << "\n";
        return std::nullopt;
    }
}

bool LutzElevator::call(Floor floor) {
    try {
        if (!floor) return false;
        auto url = "http://" + elevatorHost + ":1880/elevator/call/" + *floor;
        cpr::Post(cpr::Url{url});
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error at LUTZ elevator call API: " << e.what() << "\n";
        return false;
    }
}
