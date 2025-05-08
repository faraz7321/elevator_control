#include "elevator/GeprogElevator.hpp"
#include "elevator/LutzElevator.hpp"
#include "elevator/SchindlerElevator.hpp"
#include "useElevator.hpp"
#include <memory>
#include <stdexcept>

std::shared_ptr<Elevator> useElevator(const std::string& type, const std::string& host) {
    if (type == "geprog") {
        return std::make_shared<GeprogElevator>(host);
    } else if (type == "lutz") {
        return std::make_shared<LutzElevator>(host);
    } else if (type == "schindler") {
        return std::make_shared<SchindlerElevator>(host);
    } else {
        throw std::runtime_error("Unsupported elevator type: " + type);
    }
}
