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
    try {
        puzzleImage = loadPuzzleImage();
    } catch (const ImageNotFoundException& e) {
        std::cout << e.what();
        return -1;
    }
    
    // Display the image to test we loaded it properly
    namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Display window", puzzleImage);
    cv::waitKey(0);
    
    return 0;
}

cv::Mat loadPuzzleImage() {
    cv::Mat image = imread("puzzle.png", cv::IMREAD_COLOR);   // Read the file
    
    if (!image.data) {
        throw ImageNotFoundException();
    }
    
    return image;
}
