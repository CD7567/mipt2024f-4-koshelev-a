#include "rect/io/iohandler.hpp"

#include <nlohmann/json.hpp>

#include <string>

#include "rect/io/config_manager.hpp"

namespace rect {

    IOHandler::IOHandler(const ConfigManager &config) {
        dataDir = config.getDataDir();
        outDir = dataDir / config.getOutDirSuffix();
        tasksJson = dataDir / config.getTasksJsonSuffix();

        if (!exists(outDir)) {
            create_directories(outDir);
        }
    }

    IOHandler &IOHandler::getInstance() {
        static IOHandler handler{ConfigManager::getInstance()};
        return handler;
    }

    void IOHandler::deserializeTasks(std::vector<Task> &dest) {
        std::ifstream tasksJsonStream(tasksJson);
        nlohmann::json tasksJson = nlohmann::json::parse(tasksJsonStream);

        for (auto &it: tasksJson["tasks"]) {
            std::vector<cv::Point> polygon;

            for (auto &point: it["polygon"]) {
                polygon.emplace_back(point["x"], point["y"]);
            }

            dest.emplace_back(it["fileName"], it["ratio"], it["dimension"], std::move(polygon));
        }
    }

    cv::Mat IOHandler::readInput(const std::string &fileName) {
        std::filesystem::path inFile = dataDir / fileName;

        spdlog::default_logger()->debug("Reading input file: {}", inFile.string());

        return cv::imread(inFile.string());
    }

    void IOHandler::writeOutput(const cv::Mat &img, const std::string &fileName) {
        std::filesystem::path imagePath = outDir / fileName;

        spdlog::default_logger()->info("Writing output file: {}", imagePath.string());

        cv::imwrite(imagePath.string(), img);
    }

}  // namespace rect
