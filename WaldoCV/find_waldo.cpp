#include <opencv2/core/mat.hpp>
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
    
    cv::rectangle(puzzleImage, matchLoc, cv::Point(matchLoc.x + waldoTemplateImage.cols , matchLoc.y + waldoTemplateImage.rows), cv::Scalar::all(0), 2, 8, 0);
    
    cv::imshow("Window", puzzleImage);
    cv::imshow("Window", puzzleImage );
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

    cv::Mat result;
    result.create( result_rows, result_cols, CV_32FC1 );
    
    // Calculate the matches at each possible position
    cv::matchTemplate(img, templ, result, cv::TM_CCOEFF);
    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    
    // Locate the best match
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    cv::Point matchLoc = maxLoc;
    
    return matchLoc;
}
