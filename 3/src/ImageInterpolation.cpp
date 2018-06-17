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
			int I = floor((i - 1) * mX + 1);
			int J = floor((j - 1) * mY + 1);
			if (I >= xSize) {
				I = xSize - 1;
			}
			if (J >= ySize) {
				J = ySize - 1;
			}
			output[3 * i + j * newXSize * 3] = input[3 * I + J * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] = input[3 * I + 1 + J * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] = input[3 * I + 2 + J * xSize * 3];
		}
	}
}

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize)
{
	/* TO DO */
	double mX = ((double)xSize) / newXSize;
	double mY = ((double)ySize) / newYSize;
	for (int i = 0; i < newXSize; i++)
	{
		for (int j = 0; j < newYSize; j++)
		{
			int I = (i)* mX;
			int J = (j)* mY;
			double a = j * mY - floor(j / mY);
			double b = i * mX - floor(i / mX);

			output[3 * i + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I + J * xSize * 3] +
				(1 - a) * b * input[3 * (I + 1) + J * xSize * 3] +
				a * (1 - b) * input[3 * I + (J + 1) * xSize * 3] +
				a * b * input[3 * (I + 1) + (J + 1) * xSize * 3];
			output[3 * i + 1 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I + 1 + J * xSize * 3] +
				(1 - a) * b * input[3 * (I + 1) + 1 + J * xSize * 3] +
				a * (1 - b) * input[3 * I + 1 + (J + 1) * xSize * 3] +
				a * b * input[3 * (I + 1) + 1 + (J + 1) * xSize * 3];
			output[3 * i + 2 + j * newXSize * 3] =
				(1 - a) * (1 - b) * input[3 * I + 2 + J * xSize * 3] +
				(1 - a) * b * input[3 * (I + 1) + 2 + J * xSize * 3] +
				a * (1 - b) * input[3 * I + 2 + (J + 1) * xSize * 3] +
				a * b * input[3 * (I + 1) + 2 + (J + 1) * xSize * 3];
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
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{

			int J = j + k1 * xSize * sin(2 * 3.14* j / (ySize*k2));

			if (J >= 0 && J < xSize && i >= 0 && i < ySize) {

				output[3 * i + j * xSize * 3] = input[3 * i + J * xSize * 3];
				output[3 * i + 1 + j * xSize * 3] = input[3 * i + 1 + J * xSize * 3];
				output[3 * i + 2 + j * xSize * 3] = input[3 * i + 2 + J * xSize * 3];
			}
			else {
				output[3 * i + j * xSize * 3] = 0;
				output[3 * i + 1 + j * xSize * 3] = 0;
				output[3 * i + 2 + j * xSize * 3] = 0;
			}

		}
	}
}

void imageTransformBilinear(const uchar input[], int xSize, int ySize, uchar output[], double k1, double k2)
{
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{

			double pomI = i;
			double pomJ = j + k1 * xSize * sin(2 * 3.14* j / (ySize*k2));

			int pomI1 = floor(pomI);
			int pomJ2 = floor(pomJ);

			double a = pomJ - pomJ2;
			double b = pomI - pomI1; // 0

			if (pomI1 >= 0 && pomI1 + 1 < xSize && pomJ2 >= 0 && pomJ2 + 1 < ySize)
			{
				output[3 * i + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * pomI1 + pomJ2 * xSize * 3] +
					(1 - a) * b * input[3 * (pomI1 + 1) + pomJ2 * xSize * 3] +
					a * (1 - b) * input[3 * pomI1 + (pomJ2 + 1) * xSize * 3] +
					a * b * input[3 * (pomI1 + 1) + (pomJ2 + 1) * xSize * 3];
				output[3 * i + 1 + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * pomI1 + 1 + pomJ2 * xSize * 3] +
					(1 - a) * b * input[3 * (pomI1 + 1) + 1 + pomJ2 * xSize * 3] +
					a * (1 - b) * input[3 * pomI1 + 1 + (pomJ2 + 1) * xSize * 3] +
					a * b * input[3 * (pomI1 + 1) + 1 + (pomJ2 + 1) * xSize * 3];
				output[3 * i + 2 + j * xSize * 3] =
					(1 - a) * (1 - b) * input[3 * pomI1 + 2 + pomJ2 * xSize * 3] +
					(1 - a) * b * input[3 * (pomI1 + 1) + 2 + pomJ2 * xSize * 3] +
					a * (1 - b) * input[3 * pomI1 + 2 + (pomJ2 + 1) * xSize * 3] +
					a * b * input[3 * (pomI1 + 1) + 2 + (pomJ2 + 1) * xSize * 3];
			}
			else
			{
				output[3 * i + j * xSize * 3] = 0;
				output[3 * i + 1 + j * xSize * 3] = 0;
				output[3 * i + 2 + j * xSize * 3] = 0;
			}
		}
	}
}