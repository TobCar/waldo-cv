#include <opencv2/opencv.hpp>
#include <iostream>
#include "find_waldo.h"

struct ImageNotFoundException : public std::exception {
    const char * what () const throw () {
        return "Could not find or load an image";
    }
};

int main(int argc, char** argv) {
    cv::Mat puzzleImage;
    cv::Mat waldoTemplateImage;
    try {
        puzzleImage = loadImage("puzzle.png");
        waldoTemplateImage = loadImage("waldo.png");
    } catch (const ImageNotFoundException& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    // Display the image to test we loaded it properly
    namedWindow("Puzzle Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Puzzle Image", puzzleImage);
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
