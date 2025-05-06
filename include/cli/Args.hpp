#pragma once
#include <string>

struct Args {
    std::string robotHost;
    std::string robotSecret;
    std::string robotBusinessId;
    std::string elevatorType;
    std::string elevatorHost;
};

Args parseArgs();
