#pragma once
#include "utils/types.hpp"

class GeprogElevator : public Elevator {
public:
    explicit GeprogElevator(const std::string& host);
    std::string getHost() const override;
    std::optional<std::string> currentFloor() override;
    bool call(Floor floor) override;

private:
    std::string elevatorHost;
};
