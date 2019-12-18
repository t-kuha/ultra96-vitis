#include "hw-resize.h"

 #include <stdint.h>
#include "common/xf_params.hpp"
#include "imgproc/xf_resize.hpp"

#define	_NPC					XF_NPPC1
#define _TYPE					XF_8UC3


void data2mat(data_t* img_in, xf::cv::Mat<_TYPE, _SRC_ROWS, _SRC_COLS, XF_NPPC1>& _src){
//	XF_TNAME(_TYPE, _NPC) val;	// Pixel data
	ap_uint<24> val;

	for(unsigned int r = 0; r < _SRC_ROWS; r++){
		for(unsigned int c = 0; c < _SRC_COLS; c++){
#pragma HLS PIPELINE
			// val =
			// 		(img_in[(r*_SRC_COLS + c)*3 + 0]) + 		// B
			// 		(img_in[(r*_SRC_COLS + c)*3 + 1] << 8) +	// G
			// 		(img_in[(r*_SRC_COLS + c)*3 + 2] << 16);	// G
			_src.write(r*_SRC_COLS + c, img_in[r*_SRC_COLS + c] & 0xFFFFFF);
		}
	}
}

void mat2data(xf::cv::Mat<_TYPE, _DST_ROWS, _DST_COLS, XF_NPPC1>& _dst, data_t* img_out){
//	XF_TNAME(_TYPE, _NPC) val;	// Pixel data
	// ap_uint<24> val;

	for(unsigned int r = 0; r < _DST_ROWS; r++){
		for(unsigned int c = 0; c < _DST_COLS; c++){
#pragma HLS PIPELINE
			img_out[r*_DST_COLS + c] = _dst.read(r*_DST_COLS + c);
			// img_out[(r*_DST_COLS + c)*3 + 0] = (val      ) & 0xFF;
			// img_out[(r*_DST_COLS + c)*3 + 1] = (val >>  8) & 0xFF;
			// img_out[(r*_DST_COLS + c)*3 + 2] = (val >> 16) & 0xFF;
		}
	}
}


void resize(data_t* img_in, data_t* img_out)
{
#pragma HLS INTERFACE m_axi     port=img_in  offset=slave  depth=2 bundle=gmem1
#pragma HLS INTERFACE m_axi depth=2 port=img_out offset=slave bundle=gmem2
#pragma HLS INTERFACE s_axilite port=return

	xf::cv::Mat<_TYPE, _SRC_ROWS, _SRC_COLS, XF_NPPC1> _src;
	xf::cv::Mat<_TYPE, _DST_ROWS, _DST_COLS, XF_NPPC1> _dst;
#pragma HLS stream variable=_src.data depth=2
#pragma HLS stream variable=_dst.data depth=2

#pragma HLS DATAFLOW
	data2mat(img_in, _src);
	xf::cv::resize<XF_INTERPOLATION_BILINEAR, _TYPE, _SRC_ROWS, _SRC_COLS, _DST_ROWS, _DST_COLS, _NPC, _MAX_DOWN_SCALE>(_src, _dst);
	mat2data(_dst, img_out);
}

