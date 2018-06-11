
#ifndef IMAGEINTERPOLATION_H_
#define IMAGEINTERPOLATION_H_

#include <QString>
#include <QVector>
#include <QImage>

void sampleAndHold(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void bilinearInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void bicubicInterpolate(const uchar input[], int xSize, int ySize, uchar output[], int newXSize, int newYSize);

void imageTransform(const uchar input[], int xSize, int ySize, uchar output[], double k1, double k2);

void imageTransformBilinear(const uchar input[], int xSize, int ySize, uchar output[], double k1, double k2);

#endif // IMAGEINTERPOLATION_H_
