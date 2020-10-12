#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_RGBA_to_RGBB(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB);

void rgb_swap(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // average of each
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int average = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (double) 3);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue = image[i][j].rgbtRed = average;
        }
    }
}

//// Reflect image horizontally : swapping method
//void reflect(int height, int width, RGBTRIPLE image[height][width])
//{
//    for (int i = 0; i < height; ++i)
//    {
//        for (int j = 0, half_width = width / 2; j < half_width; ++j)
//        {
//            rgb_swap(&image[i][j], &image[i][width - 1 - j]);
//        }
//    }
//    return;
//}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        RGBTRIPLE line[width];
        for (int j = 0; j < width; ++j)
        {
            line[width -1 - j] = image[i][j];
        }
        RGBTRIPLE *p_image_line = image[i];
        memcpy((void *)p_image_line, (void *)line, width * sizeof(RGBTRIPLE));
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

void rgb_swap(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB)
{
    RGBTRIPLE *swapper = malloc(sizeof(RGBTRIPLE));
    copy_RGBA_to_RGBB(rgbA, swapper);
    copy_RGBA_to_RGBB(rgbB, rgbA);
    copy_RGBA_to_RGBB(swapper, rgbB);
    free(swapper);
}

// get reference b and change the value of B
void copy_RGBA_to_RGBB(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB)
{
    // rgb-> is the same than (*rgb).
    rgbB->rgbtRed = rgbA->rgbtRed;
    rgbB->rgbtBlue = rgbA->rgbtBlue;
    rgbB->rgbtGreen = rgbA->rgbtGreen;
}