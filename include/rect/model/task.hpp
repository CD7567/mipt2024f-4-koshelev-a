#ifndef MIPT2024S_3_KOSHELEV_A_TASK_HPP
#define MIPT2024S_3_KOSHELEV_A_TASK_HPP

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

namespace rect {

    /**
     * Data class deserialization of input json
     */
    struct Task {
        /**
         * Name of a file that shall be processed
         */
        std::string fileName;

        /**
         * Aspect ratio of output image:
         * ratio = width / height
         */
        double ratio;

        /**
         * Expected width of output image
         */
        int dimension;

        /**
         * Barcode location polygon
         */
        std::vector<cv::Point> polygon;
    };
}

#endif //MIPT2024S_3_KOSHELEV_A_TASK_HPP
