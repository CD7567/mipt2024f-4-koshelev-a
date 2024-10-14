#include "rect/io/config_manager.hpp"

namespace rect {

    ConfigManager &ConfigManager::getInstance() {
        static ConfigManager manager;
        return manager;
    }

    void ConfigManager::setConfig(const char *filepath) {
        config = toml::parse_file(filepath);
    }

    ConfigManager::path ConfigManager::getDataDir() const {
        return {config["io"]["dataDir"].value<std::string>().value()};
    }

    ConfigManager::path ConfigManager::getOutDirSuffix() const {
        return {config["io"]["outDirSuffix"].value<std::string>().value()};
    }

    ConfigManager::path ConfigManager::getTasksJsonSuffix() const {
        return {config["io"]["tasksJsonFileName"].value<std::string>().value()};

    }
}
