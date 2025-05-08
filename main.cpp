#include "cli/Args.hpp"
#include "robot/useRobot.hpp"
#include "useElevator.hpp"
#include "api/AutoXing.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <nlohmann/json.hpp>

void handleTask(const nlohmann::json &taskPt, std::shared_ptr<RobotRestAPI> api, std::shared_ptr<Elevator> elevator);

int main() {

    std::string authToken;
    
    std::cout << "Enter AutoXing Auth Token: ";
    std::cin >> authToken;
    AutoXingAPI AXapi(authToken);

    Args args = parseArgs();
    
    auto robot = Robot(args.robotHost, args.robotSecret, args.robotBusinessId);
    robot.connect();

    auto elevator = useElevator(args.elevatorType, args.elevatorHost);

    auto api = robot.restApi;

    while (true) {
        std::cout << "\n### Polling Tasks ###\n";

        auto tasks = AXapi.loadTasks(args.robotBusinessId);
        if (tasks.empty()) {
            std::cout << "No tasks available. Sleeping 10s...\n";
            std::this_thread::sleep_for(std::chrono::seconds(10));
            continue;
        }

        const auto& task = tasks[0];
        const auto& taskPts = task["taskPts"];

        for (const auto& pt : taskPts) {
            handleTask(pt, api, elevator);
            std::this_thread::sleep_for(std::chrono::seconds(5));  // buffer between tasks
        }

        std::cout << "Task cycle complete. Sleeping 10s...\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
void handleTask(const nlohmann::json& taskPt, std::shared_ptr<RobotRestAPI> api, std::shared_ptr<Elevator> elevator) {
    if (!taskPt.contains("ext") || !taskPt["ext"].contains("poi")) {
        std::cerr << "Invalid taskPt format: missing ext.poi\n";
        return;
    }

    auto poi = taskPt["ext"]["poi"];
    std::vector<double> coords = { poi["x"], poi["y"] };
    double ori = poi["ori"];

    bool useElevator = poi.value("in_elevator", false);

    std::cout << "Task: " << taskPt["ext"]["id"] << " at (" << coords[0] << ", " << coords[1] << "), ori=" << ori << "\n";

    if (useElevator) {
        std::cout << "Calling elevator...\n";
        auto current = elevator->currentFloor();
        if (current) {
            elevator->call(current);
            std::cout << "Elevator arrived at: " << *current << "\n";
        } else {
            std::cerr << "Could not get current floor\n";
        }

        std::cout << "Robot entering elevator...\n";
        api->enterElevator(coords, ori);
    } else {
        std::cout << "Moving to POI directly...\n";
        api->moveTo(coords, ori);
    }
}