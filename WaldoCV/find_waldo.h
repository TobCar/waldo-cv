#ifndef find_waldo_h
#define find_waldo_h

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

std::string queryUser(std::string prompt, std::string defaultInput);
cv::Mat loadImage(std::string);
cv::Point findWaldoWithTemplateMatching(cv::Mat img, cv::Mat templ);
cv::Mat emphasiseWaldo(cv::Mat img, cv::Mat templ, cv::Point matchLoc);

#endif
