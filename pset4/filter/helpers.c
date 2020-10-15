#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_RGBA_to_RGBB(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB);

void rgb_swap(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB);

// Convert image to grayscale : Ok
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

//// Reflect image horizontally : swapping method : Ok
//void reflect(int height, int width, RGBTRIPLE image[height][width])
//{
//    for (int i = 0; i < height; ++i)
//    {
//        for (int j = 0, half_width = width / 2; j < half_width; ++j)
//        {
//            rgb_swap(&image[i][j], &image[i][width - 1 - j]);
//        }
//    }
//}

// Reflect image horizontally : Copying the line over the array : Ok
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        RGBTRIPLE line[width];
        for (int j = 0; j < width; ++j)
        {
            line[width - 1 - j] = image[i][j];
        }
        RGBTRIPLE *p_image_line = image[i];
        memcpy((void *) p_image_line, (void *) line, width * sizeof(RGBTRIPLE));
    }
}

//// Blur image : simple method : Ok
//void blur(int height, int width, RGBTRIPLE image[height][width])
//{
//    RGBTRIPLE blured_image[height][width];
//    for (int i = 0; i < height; ++i)
//    {
//        for (int j = 0; j < width; ++j)
//        {
//            int total_green = image[i][j].rgbtGreen;
//            int total_blue = image[i][j].rgbtBlue;
//            int total_red = image[i][j].rgbtRed;
//            int n = 1;
//            // left
//            if (j > 0)
//            {
//                total_green += image[i][j - 1].rgbtGreen;
//                total_red += image[i][j - 1].rgbtRed;
//                total_blue += image[i][j - 1].rgbtBlue;
//                n++;
//            }
//            // top
//            if (i > 0)
//            {
//                total_green += image[i - 1][j].rgbtGreen;
//                total_red += image[i - 1][j].rgbtRed;
//                total_blue += image[i - 1][j].rgbtBlue;
//                n++;
//            }
//            // right
//            if (j < width - 1)
//            {
//                total_green += image[i][j + 1].rgbtGreen;
//                total_red += image[i][j + 1].rgbtRed;
//                total_blue += image[i][j + 1].rgbtBlue;
//                n++;
//            }
//            // bottom
//            if (i < height - 1)
//            {
//                total_green += image[i + 1][j].rgbtGreen;
//                total_red += image[i + 1][j].rgbtRed;
//                total_blue += image[i + 1][j].rgbtBlue;
//                n++;
//            }
//            // top-left
//            if (i > 0 && j > 0)
//            {
//                total_green += image[i - 1][j - 1].rgbtGreen;
//                total_red += image[i - 1][j - 1].rgbtRed;
//                total_blue += image[i - 1][j - 1].rgbtBlue;
//                n++;
//            }
//            // top-right
//            if (i > 0 && j < width - 1)
//            {
//                total_green += image[i - 1][j + 1].rgbtGreen;
//                total_red += image[i - 1][j + 1].rgbtRed;
//                total_blue += image[i - 1][j + 1].rgbtBlue;
//                n++;
//            }
//            // bottom-right
//            if (i < height - 1 && j < width - 1)
//            {
//                total_green += image[i + 1][j + 1].rgbtGreen;
//                total_red += image[i + 1][j + 1].rgbtRed;
//                total_blue += image[i + 1][j + 1].rgbtBlue;
//                n++;
//            }
//            // bottom-left
//            if (i < height - 1 && j > 0)
//            {
//                total_green += image[i + 1][j - 1].rgbtGreen;
//                total_red += image[i + 1][j - 1].rgbtRed;
//                total_blue += image[i + 1][j - 1].rgbtBlue;
//                n++;
//            }
//            blured_image[i][j].rgbtBlue = round(total_blue / (double) n);
//            blured_image[i][j].rgbtGreen = round(total_green / (double) n);
//            blured_image[i][j].rgbtRed = round(total_red / (double) n);
//        }
//    }
//    memcpy((void *) image, (void *) blured_image, height * width * sizeof(RGBTRIPLE));
//}

// Blur image : simple method : Ok
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured_image[height][width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int total_green = 0;
            int total_blue = 0;
            int total_red = 0;
            int n = 0;
            for (int l = -1; l <= 1; ++l)
            {
                for (int m = -1; m <= 1; ++m)
                {
                    if (i + l >= 0 && i + l < height && j + m >= 0 && j + m < width)
                    {
                        total_green += image[i + l][j + m].rgbtGreen;
                        total_red += image[i + l][j + m].rgbtRed;
                        total_blue += image[i + l][j + m].rgbtBlue;
                        n++;
                    }
                }
            }
            blured_image[i][j].rgbtBlue = round(total_blue / (double) n);
            blured_image[i][j].rgbtGreen = round(total_green / (double) n);
            blured_image[i][j].rgbtRed = round(total_red / (double) n);
        }
    }
    memcpy((void *) image, (void *) blured_image, height * width * sizeof(RGBTRIPLE));
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