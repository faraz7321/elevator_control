#pragma once
#include <string>
#include <vector>
#include <optional>

using Position = std::pair<double, double>;

struct BaseMessage {
    std::string topic;
};

struct TrackedPose : BaseMessage {
    Position pos;
    double ori;
};

struct PlanningState : BaseMessage {
    std::string map_uid;
    int action_id;
    std::string action_type;
    std::string move_state;
    std::optional<int> fail_reason;
    std::optional<std::string> fail_reason_str;
    double remaining_distance;
    std::vector<std::pair<Position, double>> target_poses;
    bool in_elevator;
};

struct Trajectory : BaseMessage {
    std::vector<Position> points;
};

struct Door {
    std::string name;
    std::string mac;
    std::string state;
    std::vector<Position> polygon;
};

struct AutoDoors : BaseMessage {
    std::vector<Door> doors;
};

struct GlobalPath : BaseMessage {
    int64_t stamp;
    std::vector<Position> positions;
};

std::string createEnableTopicMessage(const std::vector<std::string>& topics);

BaseMessage parseMessage(const std::string& jsonData);
