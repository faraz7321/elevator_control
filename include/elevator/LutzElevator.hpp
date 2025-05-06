#pragma once
#include "utils/types.hpp"

class LutzElevator : public Elevator {
public:
    explicit LutzElevator(const std::string& host);
    std::string getHost() const override;
    std::optional<std::string> currentFloor() override;
    bool call(Floor floor) override;

private:
    std::string elevatorHost;
};
