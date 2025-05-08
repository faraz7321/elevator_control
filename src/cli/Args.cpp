#include "cli/Args.hpp"
#include <iostream>
#include <cstdlib>

static std::string promptFor(const std::string& name) {
    std::string value;
    std::cout << name << ": ";
    std::getline(std::cin, value);
    return value;
}

Args parseArgs() {
    Args args;
    char* env;

    args.robotHost = (env = std::getenv("ROBOT_HOST")) ? env : promptFor("Enter robot host");
    args.robotSecret = (env = std::getenv("ROBOT_SECRET")) ? env : promptFor("Enter robot secret");
    args.robotBusinessId = (env = std::getenv("ROBOT_BUSINESS_ID")) ? env : promptFor("Enter robot business ID");
    args.elevatorType = (env = std::getenv("ELEVATOR_TYPE")) ? env : promptFor("Enter elevator type [geprog|lutz|schindler]");
    args.elevatorHost = (env = std::getenv("ELEVATOR_HOST")) ? env : promptFor("Enter elevator host");

    return args;
}
