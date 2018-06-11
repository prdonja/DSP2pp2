#include "ImageInterpolation.h"
#include "ColorSpaces.h"
#include <math.h>


void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double mX = ((double)xSize) / newXSize;
	double mY = ((double)ySize) / newYSize;
	for (int i = 0; i < newXSize; i++)
	{
		for (int j = 0; j < newYSize; j++)
		{
			int mI = floor((i - 1) * mX + 1);
			int mJ = floor((j - 1) * mY + 1);
			if (mI >= xSize) {
				mI = xSize - 1;
			}
			if (mJ >= ySize) {
				mJ = ySize - 1;
			}
			output[3 * i + j * newXSize * 3] = input[3 * mI + mJ * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] = input[3 * mI + 1 + mJ * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] = input[3 * mI + 2 + mJ * xSize * 3];
		}
	}
}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double scaleX = ((double)xSize) / newXSize;
	double scaleY = ((double)ySize) / newYSize;
	for (int i = 0; i < newXSize; i++)
	{
		for (int j = 0; j < newYSize; j++)
		{
			int newI = (i)* scaleX;
			int newJ = (j)* scaleY;
			double a = j / scaleY - floor(j / scaleY);
			double b = i / scaleX - floor(i / scaleX);

			output[3 * i + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * newI + newJ * xSize * 3] +
				(1 - a) * b * input[3 * (newI + 1) + newJ * xSize * 3] +
				a * (1 - b) * input[3 * newI + (newJ + 1) * xSize * 3] +
				a * b * input[3 * (newI + 1) + (newJ + 1) * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * newI + 1 + newJ * xSize * 3] +
				(1 - a) * b * input[3 * (newI + 1) + 1 + newJ * xSize * 3] +
				a * (1 - b) * input[3 * newI + 1 + (newJ + 1) * xSize * 3] +
				a * b * input[3 * (newI + 1) + 1 + (newJ + 1) * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * newI + 2 + newJ * xSize * 3] +
				(1 - a) * b * input[3 * (newI + 1) + 2 + newJ * xSize * 3] +
				a * (1 - b) * input[3 * newI + 2 + (newJ + 1) * xSize * 3] +
				a * b * input[3 * (newI + 1) + 2 + (newJ + 1) * xSize * 3];
		}
	}
}

void bicubicInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
}

void imageTransform(const uchar input[], int xSize, int ySize, uchar output[], double k1, double k2)
{
	/* TO DO */
}

void imageTransformBilinear(const uchar input[], int xSize, int ySize, uchar output[], double k1, double k2)
{
	/* TO DO */
}