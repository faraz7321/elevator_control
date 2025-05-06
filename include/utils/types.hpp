#pragma once
#include <string>
#include <optional>

using Floor = std::optional<std::string>;

class Elevator {
public:
    virtual ~Elevator() = default;
    virtual std::string getHost() const = 0;
    virtual std::optional<std::string> currentFloor() = 0;
    virtual bool call(Floor floor) = 0;
};
