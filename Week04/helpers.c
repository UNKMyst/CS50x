#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go through row
    for (int i = 0; i < height; i++)
    {
        // Go through colum
        for (int j = 0; j < width; j++)
        {
            // Will convert to float
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;

            // Get average of all
            int average = round((Red + Blue + Green) / 3);
            // Assign average to all R G B
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Go Through row
    for (int i = 0; i < height; i++)
    {
        // Go Through colum
        for (int j = 0; j < width; j++)
        {
            // Convert to float
            float originRed = image[i][j].rgbtRed;
            float originBlue = image[i][j].rgbtBlue;
            float originGreen = image[i][j].rgbtGreen;

            // Apply given Algorithm
            int sepiaRed = round(0.393 * originRed + 0.769 * originGreen + 0.189 * originBlue);
            int sepiaGreen = round(0.349 * originRed+ 0.686 * originGreen+ 0.168 * originBlue);
            int sepiaBlue = round(0.272 * originRed+ 0.534 * originGreen+ 0.131 * originBlue);

            // if exceed max then put 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update Each Pixel to current values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Will go through each row
    for (int i = 0; i < height; i++)
    {
        // Will go through each colum
        for (int j = 0; j < width / 2; j++)
        {
            // Create temporary placer
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a Copy of the image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed, totalBlue, totalGreen;
            totalRed = totalBlue = totalGreen = 0;
            float count = 0.00;

            // Will get near pixels
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int currentK = i + k;
                    int currentL = j + l;

                    // Will check if near pixels are valid
                    if (currentK < 0 || currentK > (height - 1) || currentL < 0 || currentL > (width - 1))
                    {
                        continue;
                    }

                    // Get image value
                    totalRed += image[currentK][currentL].rgbtRed;
                    totalGreen += image[currentK][currentL].rgbtGreen;
                    totalBlue += image[currentK][currentL].rgbtBlue;

                    count++;
                }

                // Get Average of near pixels
                temp[i][j].rgbtRed = round(totalRed / count);
                temp[i][j].rgbtGreen = round(totalGreen / count);
                temp[i][j].rgbtBlue = round(totalBlue / count);
            }
        }
    }

    // Copy to Original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
