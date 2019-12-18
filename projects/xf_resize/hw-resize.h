#pragma once

#define 	_SRC_ROWS	        1216
#define 	_SRC_COLS	        1936
#define 	_DST_ROWS           (_SRC_ROWS/2)
#define 	_DST_COLS           (_SRC_COLS/2)
#define     _MAX_DOWN_SCALE     2


typedef	unsigned int		data_t;

extern "C" {
void resize(data_t* img_in, data_t* img_out);
}
