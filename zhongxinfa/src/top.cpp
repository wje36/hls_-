#include "top.h"


void hlsfilter1(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, int rows, int cols)
{

#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

#pragma HLS RESOURCE core=AXI_SLAVE variable=rows metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=cols metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

#pragma HLS INTERFACE ap_stable port=rows
#pragma HLS INTERFACE ap_stable port=cols

	RGB_IMAGE img_0;
	GRAY_IMAGE img_1;
	GRAY_IMAGE img_2;
	GRAY_IMAGE img_gaussian;

	RGB_PIXEL pix(10, 10, 10);

#pragma HLS dataflow
	hls::AXIvideo2Mat(INPUT_STREAM, img_0);
	hls::CvtColor<HLS_RGB2GRAY>(img_0, img_1);

	hls_zhongxinfa(img_1, img_gaussian,rows,cols);

	hls::Mat2AXIvideo(img_gaussian, OUTPUT_STREAM);
}



void hls_zhongxinfa(GRAY_IMAGE& INPUT_IMG,GRAY_IMAGE& OUTPUT_IMG, int rows, int cols)
{

	GRAY_IMAGE img_0;
	GRAY_IMAGE img_1;
	GRAY_PIXEL INPUT_IMG_DATA;
	GRAY_PIXEL OUTPUT_IMG_DATA;
	int record[MAX_HEIGHT];
	int re=0;
	float x0=0;
#pragma HLS dataflow
	hls::Duplicate(INPUT_IMG, img_0, img_1);
	for(int i=0;i<img_0.rows;i++)
	{
		float sum_value=0;
		float sum_valuecoor=0;

		float current_value[783];
		float current_coordinat[783];
		int vector_num=0;

		for(int j=0;j<img_0.cols;j++)
		{
			img_0>>INPUT_IMG_DATA;
			float current=INPUT_IMG_DATA.val[0];//pix用完后也消失

			if(current>30)
			{
				current_value[vector_num]= current;
				current_coordinat[vector_num]= j;
				vector_num++;
			}
		}
		for (int k = 0; k < vector_num; k++) {
			sum_valuecoor += current_value[k] * current_coordinat[k];
			sum_value += current_value[k];
		}
		int x=sum_valuecoor/sum_value;
		record[re]=x;
		re++;
	}

	hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC1>    _mask(rows,cols);
	hls::Scalar<HLS_MAT_CN(HLS_8UC1),HLS_TNAME(HLS_8UC1)>       d;
	int re1=0;
	for(int i=0;i<img_1.rows;i++)
	{
		for(int j=0;j<img_1.cols;j++)
		{
			img_1>>INPUT_IMG_DATA;

			if((record[re1]+re1*cols)==i*cols+j)
			{
				d.val[0]=255;

			}else
				d.val[0]=0;

			_mask<<d;
		}
		re1++;
	}
	hls::Scalar<1,unsigned char> color(200);
	GRAY_IMAGE OUTPUT_IMG2;
	hls::Duplicate(_mask, OUTPUT_IMG, OUTPUT_IMG2);

}


















