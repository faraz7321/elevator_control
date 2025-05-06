#pragma once
#include "utils/types.hpp"

class SchindlerElevator : public Elevator {
public:
    explicit SchindlerElevator(const std::string& host);
    std::string getHost() const override;
    std::optional<std::string> currentFloor() override;
    bool call(Floor floor) override;

private:
    std::string elevatorHost;
};
