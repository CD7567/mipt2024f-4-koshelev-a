#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <opencv2/opencv.hpp>

#include "rect/io/config_manager.hpp"
#include "rect/io/iohandler.hpp"

#include "rect/transform.hpp"

using namespace rect;

int main(int argc, const char **argv) {
    // Setup sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/main.log", 1024 * 1024 * 10, 3);
    file_sink->set_level(spdlog::level::debug);

    // Setup logger
    spdlog::logger logger("rect/main", {console_sink, file_sink});

#ifndef NDEBUG
    logger.set_level(spdlog::level::debug);
#else
    logger.set_level(spdlog::level::info);
#endif

    spdlog::set_default_logger(std::make_unique<spdlog::logger>(logger));

    logger.info("===== [Starting new run] =====");

    // Setup config manager
    auto &config = ConfigManager::getInstance();
    config.setConfig("config.toml");

    // Setup io handler
    auto &io = IOHandler::getInstance();

    logger.debug("Successfully initialized input handler");

    std::vector<Task> tasks;
    try {
        io.deserializeTasks(tasks);
    } catch (std::exception &e) {
        logger.error("Failed to deserialize tasks: {}", e.what());
        return 1;
    }

    logger.info("Found {} tasks", tasks.size());

    for (auto &task: tasks) {
        logger.info("Processing {}", task.fileName);

        cv::Mat input = io.readInput(task.fileName);

        auto &polygon = task.polygon;
        auto matrix = getProjectionMatrix(
                polygon[0], polygon[1], polygon[2], polygon[3],
                cv::Rect(0, 0, task.dimension, task.dimension / task.ratio)
        );

        logger.debug("Matrix: {} {}x{}", matrix.type(), matrix.cols, matrix.rows);
        logger.debug("Source: [({},{}), ({},{}), ({},{}), ({},{})]", polygon[0].x, polygon[0].y, polygon[1].x, polygon[1].y, polygon[2].x, polygon[2].y, polygon[3].x, polygon[3].y);


        cv::Mat warped;
        cv::warpPerspective(input, warped, matrix, cv::Size(task.dimension, task.dimension / task.ratio));

        io.writeOutput(warped, task.fileName);
    }
}
