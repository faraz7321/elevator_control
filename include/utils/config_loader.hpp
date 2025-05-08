#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class ConfigLoader {
public:
    ConfigLoader(const std::string& configFilePath);

    // General function to get any value from the config file
    std::string getConfig(const std::string& key);

private:
    nlohmann::json config;
    void loadConfig(const std::string& configFilePath);
};

// Constructor to load the configuration file
ConfigLoader::ConfigLoader(const std::string& configFilePath) {
    loadConfig(configFilePath);
}

// Load the configuration from the provided file
void ConfigLoader::loadConfig(const std::string& configFilePath) {
    std::ifstream file(configFilePath);
    if (file.is_open()) {
        file >> config;
        file.close();
    } else {
        std::cerr << "Could not open config file: " << configFilePath << std::endl;
    }
}

// General function to get any value from the config file
std::string ConfigLoader::getConfig(const std::string& key) {
    if (config.contains(key)) {
        return config[key];
    } else {
        std::cerr << "Key '" << key << "' not found in config." << std::endl;
        return "";
    }
}
