//============================================================================
// Name        : extractor_train-images-idx3-ubyte.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <png++/png.hpp>
#include <png++/types.hpp>
using namespace std;

int main()
{
	ifstream file("train-images.idx3-ubyte", ios_base::in | ios_base::binary);
	if( false == file.is_open() )
	{
		return 0;
	}
	int magic = 0;
	int images_count = 0;
	int rows_count = 0;
	int columns_count = 0;
	file.read( ((char*)&magic) + 3, 1 );
	file.read( ((char*)&magic) + 2, 1 );
	file.read( ((char*)&magic) + 1, 1 );
	file.read( ((char*)&magic) + 0, 1 );

	file.read( ((char*)&images_count) + 3, 1 );
	file.read( ((char*)&images_count) + 2, 1 );
	file.read( ((char*)&images_count) + 1, 1 );
	file.read( ((char*)&images_count) + 0, 1 );

	file.read( ((char*)&rows_count) + 3, 1 );
	file.read( ((char*)&rows_count) + 2, 1 );
	file.read( ((char*)&rows_count) + 1, 1 );
	file.read( ((char*)&rows_count) + 0, 1 );

	file.read( ((char*)&columns_count) + 3, 1 );
	file.read( ((char*)&columns_count) + 2, 1 );
	file.read( ((char*)&columns_count) + 1, 1 );
	file.read( ((char*)&columns_count) + 0, 1 );
//	file >> magic;
//	file >> images_count;
//	file >> rows_count;
//	file >> columns_count;

	for( int image_i = 0 ; image_i < images_count ; image_i++ )
	{
		char file_name[PATH_MAX] = { '\0' };
		sprintf( file_name, "./image_%d.png", image_i );
		ofstream png_file_stream( file_name );
		if( false == png_file_stream.is_open() )
		{
			return 0;
		}
		png::writer<ofstream> writer( png_file_stream );

		writer.set_height( rows_count );
		writer.set_width( columns_count );
		writer.set_color_type( png::color_type_gray );
		writer.set_bit_depth( 8 );
		writer.write_info();

		for( int row_i = 0 ; row_i < rows_count ; row_i++ )
		{
			unsigned char * row = (unsigned char*)alloca( rows_count );
			for( int column_i = 0 ; column_i < columns_count ; column_i++ )
			{
				char pixel = '\0';
				file.read( &pixel, 1 );
//				file >> pixel;
				row[column_i] = pixel;
			}
			writer.write_row( row );
		}
	}

	return 0;
}
