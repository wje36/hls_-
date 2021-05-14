//imread转IplImage

#include "top.h"
#include "opencv_top.h"

using namespace std;
using namespace cv;

//高斯滤波
int main(int argc, char** argv)
{
    //mat的导入与创建
    //Mat src_mat = imread("lena.jpg");
	Mat src_mat = imread("quexian.png");
    Mat dst_mat;//存结果
    imshow("original,jpg",src_mat);

    dst_mat = cv::Mat::zeros(src_mat.rows, src_mat.cols, CV_8UC1);

    //HLS
    AXI_STREAM  src_axi, dst_axi;

    cvMat2AXIvideo(src_mat, src_axi);
    hlsfilter1(src_axi,dst_axi,src_mat.rows,src_mat.cols);
    //hls_gaussianblur(src_axi, dst_axi, src_mat.cols, src_mat.rows);

    AXIvideo2cvMat(dst_axi, dst_mat);
    cv::imshow("hls.jpg", dst_mat);


    waitKey(0);

}

