#ifndef MIPT2024F_4_KOSHELEV_A_TRANSFORM_HPP
#define MIPT2024F_4_KOSHELEV_A_TRANSFORM_HPP

#include <opencv2/opencv.hpp>

namespace rect {

    cv::Mat getProjectionMatrix(
            cv::Point leftBottom,
            cv::Point rightBottom,
            cv::Point rightTop,
            cv::Point leftTop,
            cv::Rect dest
    );

}

#endif //MIPT2024F_4_KOSHELEV_A_TRANSFORM_HPP
