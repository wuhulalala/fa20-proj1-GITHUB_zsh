/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("fail to open file %s\n", filename);
		return NULL;
	}
	char buffer[3];
	uint32_t rows, cols;
	int rubbish;
	fscanf(fp, "%s %u %u", buffer, &rows, &cols);
	if (buffer[0] != 'P' || buffer[1] != '3') {
		printf("file format error\n");
		return NULL;
	}
	fscanf(fp, "%d", &rubbish);
	if (rubbish != 255 || rows < 0 || cols < 0) {
		printf("error\n");
		return NULL;
	}
	// Malloc space for Image
	Image * whole_image = (Image *) malloc(sizeof(Image));
	whole_image -> rows = rows;
	whole_image -> cols = cols;
	int totpixel = rows * cols;
	// Malloc space for Color
	whole_image -> image = (Color **) malloc(totpixel * sizeof(Color *));
	for (int count = 0; count < totpixel; count += 1) {
		Color * temp = (Color *) malloc(sizeof(Color));
		fscanf(fp, "%hhu %hhu %hhu", &temp -> R, &temp -> G, &temp -> B);
		whole_image -> image[count] = temp;

	}
	fclose(fp);

	return whole_image;

}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	if (image == NULL) {
		printf("NULL pointer\n");	
	}
	printf("P3\n%d %d\n255\n", image -> rows, image -> cols);
	Color ** p = image -> image;
	for (int i = 0; i < image -> rows; i += 1) {
		for (int j = 0; j < image -> cols - 1; j += 1) {
			printf("%3hhu %3hhu %3hhu   ", (*p) -> R, (*p) -> G, (*p) -> B);
			p++;
		}
		printf("%3hhu %3hhu %3hhu\n", (*p) -> R, (*p) -> G, (*p) -> B);
		p++;
	}	
}

//Frees an image
void freeImage(Image *image)
{
	if (image == NULL) {
		printf("NULL pointer\n");
	}
	uint32_t totpixel = image -> rows * image -> cols;
	for (int i = 0; i < totpixel; i += 1) {
		free(image -> image[i]);
		image -> image[i] = NULL;
	}
	free(image -> image);
	image -> image = NULL;
	free(image);
	image = NULL;
}