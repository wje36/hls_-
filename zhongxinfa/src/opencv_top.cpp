#include "opencv_top.h"
#include "top.h"

void opencv_image_guassianblur(cv::Mat src, cv::Mat dst)
{
    cv::GaussianBlur(src, dst, cv::Size(3, 3), 0);
}

