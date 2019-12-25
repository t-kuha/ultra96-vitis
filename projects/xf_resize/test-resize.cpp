#include <iostream>
#include <memory>	// std::unique_ptr
#include <string.h>

#include "hw-resize.h"

#include "FreeImage.h"


int load_image(
		std::string& path,
		std::unique_ptr<unsigned char[]>& img,
		unsigned int* width, unsigned int* height, unsigned int* bpp)
{
    // Start FreeImage
    FreeImage_Initialise();

    // Image type
    FREE_IMAGE_FORMAT fmt = FreeImage_GetFileType(path.c_str());
    if(fmt == FIF_UNKNOWN){
    	std::cerr << "[ERROR] FreeImage_GetFileType()..." << std::endl;
    	return -1;
    }

    FIBITMAP* dib = FreeImage_Load(fmt, path.c_str(), JPEG_ACCURATE);
    if(!dib){
    	std::cerr << "[ERROR] FreeImage_Load(" << path << ")..." << std::endl;
    	return -1;
    }

    if(!FreeImage_HasPixels(dib)){
    	std::cerr << "[ERROR] Image does not have pixels..." << std::endl;
    	return -1;
    }

	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	*bpp = FreeImage_GetBPP(dib);
	unsigned int sz = (*width)*(*height)*(*bpp/8);

	img = std::unique_ptr<BYTE[]>{ new BYTE[sz] };
	memcpy(img.get(), FreeImage_GetBits(dib), sz);

#if 0
	for(unsigned int r = 0; r < 10; r++){
		for(unsigned int c = 0; c < 10; c++){
			std::cout << (int)data[ (r*width + c)*3 + 0 ] << " ";
		}
		std::cout << std::endl;
	}
#endif


	FreeImage_Unload(dib);

    FreeImage_DeInitialise();

	return 0;
}

int save_image(
	std::string& path,
	std::unique_ptr<unsigned char[]>& img, 
	unsigned int width, unsigned int height, unsigned int bpp
)
{
	// Start FreeImage
    FreeImage_Initialise();

	// Allocate bitmap
	FIBITMAP* dib = FreeImage_Allocate(width, height, bpp/*, red_mask, green_mask , blue_mask*/);

	memcpy(FreeImage_GetBits(dib), img.get(), width*height*(bpp/8));

	if( !FreeImage_Save(FIF_JPEG, dib, path.c_str(), JPEG_QUALITYGOOD) ){
		std::cerr << "[ERROR] FreeImage_Save()" << std::endl;
		return -1;		
	}

	FreeImage_Unload(dib);

    FreeImage_DeInitialise();

	return 0;
}


int main(int argc, const char * argv[])
{
	std::cout << ".... Vitis Vision Library ...." << std::endl;

	int ret = 0;

	// Load image
	std::string path = "train_00005.jpg";

	std::unique_ptr<unsigned char[]> img_in;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int bpp = 0;

	ret = load_image(path, img_in, &width, &height, &bpp);
	if(ret != 0){
		std::cerr << "[ERROR] load_image()" << std::endl;
		return -1;
	}

	// Queue buffer
	std::unique_ptr<data_t[]> buf_in{ new data_t[width*height] };
	
	// Copy to queue buffer
	for(unsigned int r = 0; r < height; r++){
		for(unsigned int c = 0; c < width; c++){
			buf_in[r*width + c] = 
				(img_in[(r*width + c)*3 + 0]      ) +
				(img_in[(r*width + c)*3 + 1] <<  8) +
				(img_in[(r*width + c)*3 + 2] << 16);
		}
	}

	// Output buffer
	std::unique_ptr<data_t[]> buf_out{ new data_t[_DST_ROWS*_DST_COLS] };
	std::unique_ptr<unsigned char[]> img_out{ new unsigned char[_DST_ROWS*_DST_COLS*3] };

	resize(buf_in.get(), buf_out.get());

	// Copy from queue buffer
	for(unsigned int r = 0; r < _DST_ROWS; r++){
		for(unsigned int c = 0; c < _DST_COLS; c++){
			unsigned int val = buf_out[r*_DST_COLS + c];
			img_out[(r*_DST_COLS + c)*3 + 0] = (val      ) & 0xFF;
			img_out[(r*_DST_COLS + c)*3 + 1] = (val >>  8) & 0xFF;
			img_out[(r*_DST_COLS + c)*3 + 2] = (val >> 16) & 0xFF;
		}
	}

	// Save output image
	std::string path_out = "out.jpg";
	save_image(path_out, img_out, _DST_COLS, _DST_ROWS, 24);

	return 0;
}
