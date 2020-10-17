#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int capped_square_root(int a);

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
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0, half_width = width / 2; j < half_width; ++j)
        {
            rgb_swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Reflect image horizontally : Copying the line over the array : Ok
//void reflect(int height, int width, RGBTRIPLE image[height][width])
//{
//    for (int i = 0; i < height; ++i)
//    {
//        RGBTRIPLE line[width];
//        for (int j = 0; j < width; ++j)
//        {
//            line[width - 1 - j] = image[i][j];
//        }
//        RGBTRIPLE *p_image_line = image[i];
//        memcpy((void *) p_image_line, (void *) line, width * sizeof(RGBTRIPLE));
//    }
//}

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
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        total_green += image[i + k][j + l].rgbtGreen;
                        total_red += image[i + k][j + l].rgbtRed;
                        total_blue += image[i + k][j + l].rgbtBlue;
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

    RGBTRIPLE edge_image[height][width];
    // Gx and Gy definition
    int GX[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int GY[3][3] = {{-1, -2, -1},
                    {0,  0,  0},
                    {1,  2,  1}};

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // compute for this pixel
            int xRed, yRed, xGreen, yGreen, xBlue, yBlue;
            xRed = yRed = xGreen = yGreen = xBlue = yBlue = 0;
            for (int k = -1; k <= 1; ++k)
            {
                for (int l = -1; l <= 1; ++l)
                {
                    // if border -> Value = 0 -> same as not adding anything
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        xRed += image[i + k][j + l].rgbtRed * GX[k + 1][l + 1];
                        yRed += image[j + k][j + l].rgbtRed * GY[k + 1][l + 1];
                        xBlue += image[i + k][j + l].rgbtBlue * GX[k + 1][l + 1];
                        yBlue += image[j + k][j + l].rgbtBlue * GY[k + 1][l + 1];
                        xGreen += image[i + k][j + l].rgbtGreen * GX[k + 1][l + 1];
                        yGreen += image[j + k][j + l].rgbtGreen * GY[k + 1][l + 1];
                    }
                }
            }
            // define final value for RGB : square_root(x² + y²) capped at 255
            edge_image[i][j].rgbtRed = capped_square_root(xRed * xRed + yRed * yRed);
            edge_image[i][j].rgbtGreen = capped_square_root(yGreen * yGreen + yGreen * yGreen);
            edge_image[i][j].rgbtBlue = capped_square_root(yBlue * yBlue + yBlue * yBlue);
        }
    }
    memcpy((void *) image, (void *) edge_image, height * width * sizeof(RGBTRIPLE));
}

int capped_square_root(int a)
{
    int result = (int) round(sqrt(a));
    return result > 255 ? 255 : result;
}

void rgb_swap(RGBTRIPLE *rgbA, RGBTRIPLE *rgbB)
{
    RGBTRIPLE *swapper = malloc(sizeof(RGBTRIPLE));
    memcpy((void *) swapper, (void *) rgbA, sizeof(RGBTRIPLE));
    memcpy((void *) rgbA, (void *) rgbB, sizeof(RGBTRIPLE));
    memcpy((void *) rgbB, (void *) swapper, sizeof(RGBTRIPLE));
    free(swapper);
}
