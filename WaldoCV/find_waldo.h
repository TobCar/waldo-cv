#ifndef find_waldo_h
#define find_waldo_h

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

cv::Mat loadImage(std::string);
cv::Point findWaldoWithTemplateMatching(cv::Mat img, cv::Mat templ);

#endif
