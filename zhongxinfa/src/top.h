#ifndef _TOP_H_
#define _TOP_H_

#include "hls_video.h"

// maximum image size
#define MAX_WIDTH  443
#define MAX_HEIGHT 783

// I/O Image Settings
#define INPUT_IMAGE           "lena.jpg"
#define OUTPUT_IMAGE          "result.jpg"

// typedef video library core structures
typedef hls::stream<ap_axiu<32, 1, 1, 1> >               AXI_STREAM;
typedef hls::Scalar<3, unsigned char>                 RGB_PIXEL;
typedef hls::Scalar<1, unsigned char>                 GRAY_PIXEL;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3>     	RGB_IMAGE;
typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC1>     	GRAY_IMAGE;

// top level function for HW synthesis

void hlsfilter1(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, int rows, int cols);
void hls_zhongxinfa(GRAY_IMAGE& INPUT_IMG,GRAY_IMAGE& OUTPUT_IMG, int rows, int cols);

#endif
