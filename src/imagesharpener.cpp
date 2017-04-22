#include "imagesharpener.h"

ImageSharpener::ImageSharpener() {}

float ImageSharpener::filterArray[3][3];

void ImageSharpener::setFilterArray(float x0_y0, float x1_y0, float x2_y0,
                                    float x0_y1, float x1_y1, float x2_y1,
                                    float x0_y2, float x1_y2, float x2_y2) {
    filterArray[0][0] = x0_y0;
    filterArray[0][1] = x1_y0;
    filterArray[0][2] = x2_y0;
    filterArray[1][0] = x0_y1;
    filterArray[1][1] = x1_y1;
    filterArray[1][2] = x2_y1;
    filterArray[2][0] = x0_y2;
    filterArray[2][1] = x1_y2;
    filterArray[2][2] = x2_y2;
}

//This function applies the filter matrix to each pixel of the loaded image
QPixmap ImageSharpener::filterImage(const QPixmap *pImage) {
    QImage convertedImage = pImage->toImage();
    if(convertedImage != QImage()) {
        QImage temp(convertedImage);
        int w = convertedImage.width();
        int h = convertedImage.height();
        int columnOffset = 0, rowOffset = 0;
        for(int hC = 1; hC < h-1; hC++) {
            for(int wC = 1; wC < w-1; wC++) {
                float newRed = 0.0, newGreen = 0.0, newBlue = 0.0;
                for(int filterRow = 0; filterRow < 3; filterRow++) {
                    for(int filterColumn = 0; filterColumn < 3; filterColumn++) {
                        newRed += filterArray[filterRow][filterColumn] * QColor(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset)).redF();
                        newGreen += filterArray[filterRow][filterColumn] * QColor(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset)).greenF();
                        newBlue += filterArray[filterRow][filterColumn] * QColor(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset)).blueF();
                    }
                }
                (newRed < 0.0) ? newRed = 0.0 : (newRed > 1.0) ? newRed = 1.0 : newRed = newRed;
                (newGreen < 0.0) ? newGreen = 0.0 : (newGreen > 1.0) ? newGreen = 1.0 : newGreen = newGreen;
                (newBlue < 0.0) ? newBlue = 0.0 : (newBlue > 1.0) ? newBlue = 1.0 : newBlue = newBlue;
                temp.setPixel(wC, hC, QColor::fromRgbF(newRed, newGreen, newBlue).rgb());
                columnOffset++;
            }
            columnOffset = 0;
            rowOffset++;
        }

        return QPixmap::fromImage(temp);
    }
    else {
        qErrnoWarning("Could not convert image from QPixmap to QImage!");
    }
    return QPixmap::fromImage(convertedImage);
}
