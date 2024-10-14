#ifndef MIPT2024F_4_KOSHELEV_A_CONFIG_MANAGER_HPP
#define MIPT2024F_4_KOSHELEV_A_CONFIG_MANAGER_HPP

#include <filesystem>
#include <toml++/toml.hpp>

namespace rect {

    /**
     * Toml config handler
     */
    class ConfigManager {
    private:
        using path = std::filesystem::path;

        toml::table config;

        ConfigManager() = default;

        ConfigManager(const ConfigManager &) = delete;

        ConfigManager &operator=(const ConfigManager &) = delete;

    public:
        /**
         * Singleton-style getter of ConfigManager
         * @return ConfigManager instance
         */
        static ConfigManager &getInstance();

        /**
         * Set config file location
         * @param filepath Config file location
         */
        void setConfig(const char *filepath);

        // Common settings

        /**
         * Get path of current data directory
         * @return path of current data directory
         */
        path getDataDir() const;

        /**
         * Get subpath of output directory
         * @return path of subdirectory
         */
        path getOutDirSuffix() const;

        /**
         * Get subpath of tasks json
         * @return path of tasks json
         */
        path getTasksJsonSuffix() const;
    };

}  // namespace rect

#endif  // MIPT2024F_4_KOSHELEV_A_CONFIG_MANAGER_HPP
