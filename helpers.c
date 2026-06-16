#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average pixel value
            BYTE average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set each color to the average value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate each new color value using the sepia formula
            int newRed = 
                round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int newGreen = 
                round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int newBlue = 
                round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Ensure the result is an integer between 0 and 255
            image[i][j].rgbtRed = newRed > 255 ? 255 : newRed;
            image[i][j].rgbtGreen = newGreen > 255 ? 255 : newGreen;
            image[i][j].rgbtBlue = newBlue > 255 ? 255 : newBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Get the current pixel and the pixel on the opposite side of the row
            RGBTRIPLE *originalPixel = &image[i][j];
            RGBTRIPLE *oppositePixel = &image[i][width - (j + 1)];

            // Make a temporary copy of current pixel
            RGBTRIPLE tmp = *originalPixel;

            // Swap the current pixel with the opposite one
            *originalPixel = *oppositePixel;
            *oppositePixel = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Blur pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;

            // Check surrounding pixels
            for (int di = -1; di < 2; di++)
            {
                for (int dj = -1; dj < 2; dj++)
                {
                    int row = i + di;
                    int col = j + dj;

                    // Check if the current pixel is on the edge or corner
                    if ((row < 0) || (row >= height) || (col < 0) || (col >= width))
                        continue;

                    // Sum values and count number of valid pixels surrounding the current one
                    sum_red += copy[row][col].rgbtRed;
                    sum_green += copy[row][col].rgbtGreen;
                    sum_blue += copy[row][col].rgbtBlue;

                    count++;
                }
            }
            // Calculate and assign average value
            image[i][j].rgbtRed = round(sum_red / (float) count);
            image[i][j].rgbtGreen = round(sum_green / (float) count);
            image[i][j].rgbtBlue = round(sum_blue / (float) count);
        }
    }
    return;
}
