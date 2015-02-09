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
#include <sstream>
#include <png++/png.hpp>
#include <png++/types.hpp>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int main()
{
	ifstream train_images_file_stream("train-images.idx3-ubyte", ios_base::in | ios_base::binary);
	ifstream train_labels_file_stream("train-labels.idx1-ubyte", ios_base::in | ios_base::binary);
	if( false == train_images_file_stream.is_open() || false == train_labels_file_stream.is_open() )
	{
		return 0;
	}
	int magic = 0;
	int images_count = 0;
	int rows_count = 0;
	int columns_count = 0;

	int labels_count = 0;

	for( int folder_i = 0 ; folder_i < 10 ; folder_i++ )
	{
		char label_name[PATH_MAX] = { '\0' };
		sprintf( label_name, "./%d", folder_i );
		mkdir( label_name, 0777 );
	}

	{
		train_images_file_stream.read( ((char*)&magic) + 3, 1 );
		train_images_file_stream.read( ((char*)&magic) + 2, 1 );
		train_images_file_stream.read( ((char*)&magic) + 1, 1 );
		train_images_file_stream.read( ((char*)&magic) + 0, 1 );

		train_images_file_stream.read( ((char*)&images_count) + 3, 1 );
		train_images_file_stream.read( ((char*)&images_count) + 2, 1 );
		train_images_file_stream.read( ((char*)&images_count) + 1, 1 );
		train_images_file_stream.read( ((char*)&images_count) + 0, 1 );

		train_images_file_stream.read( ((char*)&rows_count) + 3, 1 );
		train_images_file_stream.read( ((char*)&rows_count) + 2, 1 );
		train_images_file_stream.read( ((char*)&rows_count) + 1, 1 );
		train_images_file_stream.read( ((char*)&rows_count) + 0, 1 );

		train_images_file_stream.read( ((char*)&columns_count) + 3, 1 );
		train_images_file_stream.read( ((char*)&columns_count) + 2, 1 );
		train_images_file_stream.read( ((char*)&columns_count) + 1, 1 );
		train_images_file_stream.read( ((char*)&columns_count) + 0, 1 );
	}
	{
		train_labels_file_stream.read( ((char*)&magic) + 3, 1 );
		train_labels_file_stream.read( ((char*)&magic) + 2, 1 );
		train_labels_file_stream.read( ((char*)&magic) + 1, 1 );
		train_labels_file_stream.read( ((char*)&magic) + 0, 1 );

		train_labels_file_stream.read( ((char*)&labels_count) + 3, 1 );
		train_labels_file_stream.read( ((char*)&labels_count) + 2, 1 );
		train_labels_file_stream.read( ((char*)&labels_count) + 1, 1 );
		train_labels_file_stream.read( ((char*)&labels_count) + 0, 1 );
	}

	stringstream file_name_str_stream;

	for( int image_i = 0 ; image_i < images_count ; image_i++ )
	{
		char label = '\0';
		train_labels_file_stream.read( &label, 1 );

		file_name_str_stream.clear();
		file_name_str_stream.str( std::string() );

		file_name_str_stream << "./" << (char)( 48 + label ) << "/image_" << image_i << ".png" << flush;

		string file_name = file_name_str_stream.str();

		ofstream png_file_stream( file_name.c_str() );
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

		unsigned char * row = (unsigned char*)alloca( columns_count );
		for( int row_i = 0 ; row_i < rows_count ; row_i++ )
		{
			for( int column_i = 0 ; column_i < columns_count ; column_i++ )
			{
				char pixel = '\0';
				train_images_file_stream.read( &pixel, 1 );

				row[column_i] = pixel;
			}
			writer.write_row( row );
		}
	}

	return 0;
}
