#include "file_io.h"
#include <stdio.h>

void read_bmp(const char *filename, int &out_width, int &out_height, char *out_pixels)
{
	FILE *f = fopen(filename, "rb");
	if(!f)
	{
		fprintf(stderr, "Failed to open BMP file\n");	
	}

	char file_header[14], info_header[40];
	fread(file_header, 1, 14, f);
	int pixel_array_offset, info_header_sz, compression_method, img_sz;
	short color_planes;
	if(file_header[0] != 'B' || file_header[1] != 'M')
	{
		fprintf(stderr, "Corrupt BMP file(1)\n");
		fclose(f);
	}
	pixel_array_offset = *(int*)(file_header + 10);
	
	fread(&info_header_sz, 4, 1, f);
	fseek(f, -4, SEEK_CUR);
	if(info_header_sz != 40 && info_header_sz != 124)
	{
		fprintf(stderr, "Unsupported BMP info header (header size: %d)\n", info_header_sz);
		fclose(f);
	}

	fread(info_header, 1, 40, f);
	out_width = *(int*)(info_header + 4);
	out_height = *(int*)(info_header + 8);
	color_planes = *(short*)(info_header + 12);
	
	if(color_planes != 1)
	{
		fprintf(stderr, "Corrupt BMP file(2)\n");
		fclose(f);
	}
	short bits_per_pixel = *(short*)(info_header + 14);
	compression_method = *(int*)(info_header + 16);
	img_sz = *(int*)(info_header + 20);
	if(img_sz == 0)
		img_sz = out_width * out_height * bits_per_pixel >> 3;
	if(compression_method != 0 && compression_method != 3)
	{
		fprintf(stderr, "Unsupported compression method (method: %d)\n", compression_method);
		fclose(f);
	}
	fseek(f, pixel_array_offset, SEEK_SET);
	fread(out_pixels, 1, img_sz, f);
	fclose(f);
}