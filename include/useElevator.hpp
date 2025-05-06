#pragma once
#include "utils/types.hpp"
#include <memory>
#include <string>

std::shared_ptr<Elevator> useElevator(const std::string& type, const std::string& host);
