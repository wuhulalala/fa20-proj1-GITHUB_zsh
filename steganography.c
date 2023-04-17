/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
#define LSB(x) (x & 1)
//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	int position = row * image -> cols + col;
	Color** p = image -> image;
	p = p + position;
	Color* cell = (Color*) malloc(sizeof(Color));
	if (cell == NULL) {
		printf("allocate fail\n");
		return NULL;
	}
	cell -> R = (*p) -> R;
	cell -> G = (*p) -> G;
	cell -> B = (*p) -> B;
	return cell;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	if (image == NULL) {
		printf("NULL pointer\n");
		return NULL;
	}
	Image * new_image = (Image *) malloc(sizeof(Image));
	int totpixels = image -> rows * image -> cols;
	new_image -> image = (Color **) malloc(totpixels * sizeof(Color *));
	new_image -> rows = image -> rows;
	new_image -> cols = image -> cols;
	Color** p = image -> image;
	for (int i = 0; i < totpixels; i += 1) {
		new_image -> image[i] = (Color *) malloc(sizeof(Color));
		uint8_t temp = (*(p + i)) -> B;
		temp = LSB(temp);
		if (temp == 1) {
			temp = 255;	
		}
		new_image -> image[i] -> R = temp;
		new_image -> image[i] -> G = temp;
		new_image -> image[i] -> B = temp;
	}

	return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	char * filename = argv[1];
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	Image * image1, *image2;
	image1 = readData(filename);
	image2 = steganography(image1);
	writeData(image2);
	freeImage(image1);
	freeImage(image2);
	return 0;
}
