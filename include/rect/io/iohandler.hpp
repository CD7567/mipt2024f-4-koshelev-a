#ifndef MIPT2024F_4_KOSHELEV_A_IOHANDLER_HPP
#define MIPT2024F_4_KOSHELEV_A_IOHANDLER_HPP

#include <spdlog/spdlog.h>

#include <filesystem>

#include "config_manager.hpp"
#include "rect/model/task.hpp"

namespace rect {

    /**
     * IO handler is an abstraction layer between internal interfaces and external API
     */
    class IOHandler {
    private:
        using path = std::filesystem::path;

        path dataDir;
        path outDir;
        path tasksJson;

        IOHandler(const ConfigManager &);

        IOHandler(const IOHandler &) = delete;

        IOHandler &operator=(const IOHandler &) = delete;

    public:
        /**
         * Singleton-style getter of IOHandler
         * @return IOHandler instance
         */
        static IOHandler &getInstance();

        /**
         * Deserialize tasks from input json
         * @param dest vector to store deserialized tasks
         */
        void deserializeTasks(std::vector<Task> &dest);

        /**
         * Read input image
         * @param fileName name of a file to read
         * @return image in OpenCV format
         */
        cv::Mat readInput(const std::string &fileName);

        /**
         * Write processed image
         * @param img image source
         * @param fileName name of a file to store image
         */
        void writeOutput(const cv::Mat &img, const std::string &fileName);
    };

}  // namespace rect

#endif //MIPT2024F_4_KOSHELEV_A_IOHANDLER_HPP
