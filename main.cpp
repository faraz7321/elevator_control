#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

int main() {
    auto response = cpr::Get(cpr::Url{"https://api.github.com"});
    nlohmann::json json_response = nlohmann::json::parse(response.text);

    std::cout << "GitHub API response:\n" << json_response.dump(2) << std::endl;
    return 0;
}
