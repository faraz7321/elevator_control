#include "elevator/GeprogElevator.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

GeprogElevator::GeprogElevator(const std::string& host) : elevatorHost(host) {}

std::string GeprogElevator::getHost() const {
    return elevatorHost;
}

std::optional<std::string> GeprogElevator::currentFloor() {
    try {
        auto res = cpr::Get(cpr::Url{"http://" + elevatorHost + "/state"});
        auto json = nlohmann::json::parse(res.text);
        return std::to_string(json["level"].get<int>());
    } catch (...) {
        return std::nullopt;
    }
}

bool GeprogElevator::call(Floor floor) {
    try {
        if (!floor) return false;
        auto url = "http://" + elevatorHost + "/call?level=" + *floor;
        cpr::Post(cpr::Url{url});
        return true;
    } catch (...) {
        return false;
    }
}
