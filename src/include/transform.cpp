#include "rect/transform.hpp"

#include <vector>

namespace rect {

    cv::Mat getProjectionMatrix(
            cv::Point leftBottom,
            cv::Point rightBottom,
            cv::Point rightTop,
            cv::Point leftTop,
            cv::Rect dest
    ) {
        std::vector<cv::Point> sourcePoints{leftBottom, rightBottom, rightTop, leftTop};
        std::vector<cv::Point> destPoints{
            dest.tl() + cv::Point(0, dest.height),
            dest.br(),
            dest.br() + cv::Point(0, -dest.height),
            dest.tl()
        };

        return cv::findHomography(sourcePoints, destPoints, cv::RANSAC);
    }

}