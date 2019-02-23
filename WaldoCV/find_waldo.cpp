#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "find_waldo.h"

struct ImageNotFoundException : public std::exception {
    const char * what () const throw () {
        return "Could not find or load an image";
    }
};

int main(int argc, char** argv) {
    // Load in the puzzle image and the picture of Waldo we are looking for
    cv::Mat puzzleImage;
    cv::Mat waldoTemplateImage;
    try {
        puzzleImage = loadImage("puzzle.png");
        waldoTemplateImage = loadImage("waldo.png");
    } catch (const ImageNotFoundException& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    // Find Waldo and show the user where he is
    cv::Point matchLoc = findWaldoWithTemplateMatching(puzzleImage, waldoTemplateImage);
    cv::Mat resultImage = emphasiseWaldo(puzzleImage, waldoTemplateImage, matchLoc);
    cv::imshow("Window", resultImage);
    cv::waitKey(0);
    
    return 0;
}

cv::Mat loadImage(std::string imageName) {
    cv::Mat image = imread(imageName, cv::IMREAD_COLOR);
    
    if (!image.data) {
        throw ImageNotFoundException();
    }
    
    return image;
}

cv::Point findWaldoWithTemplateMatching(cv::Mat img, cv::Mat templ) {
    // Create the result matrix
    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    cv::Mat result(result_rows, result_cols, CV_32FC1);
    
    // Calculate the matches at each possible position
    cv::matchTemplate(img, templ, result, cv::TM_CCOEFF);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    
    // Locate the best match
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    cv::Point matchLoc = maxLoc;
    
    return matchLoc;
}

cv::Mat emphasiseWaldo(cv::Mat img, cv::Mat templ, cv::Point matchLoc) {
    // Darken the whole image. The black has an opacity of 75%
    cv::Mat allBlackImage(img.size(), img.type());
    allBlackImage.setTo(cv::Scalar::all(0));
    
    cv::Mat emphasisedImage;
    cv::addWeighted(img, 0.25, allBlackImage, 0.75, 0, emphasisedImage);
    
    // Set the region with Waldo back to its original values to emphasise it
    cv::Rect regionWithWaldo = cv::Rect(matchLoc.x, matchLoc.y, templ.cols, templ.rows);
    cv::Mat emphasisedImageROI = emphasisedImage(regionWithWaldo);
    img(regionWithWaldo).copyTo(emphasisedImageROI);
    
    return emphasisedImage;
}
