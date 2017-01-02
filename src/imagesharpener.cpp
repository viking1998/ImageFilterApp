#include "imagesharpener.h"

ImageSharpener::ImageSharpener() {}

int ImageSharpener::filterArray[3][3];

void ImageSharpener::setFilterArray(int x0_y0, int x1_y0, int x2_y0,
                                    int x0_y1, int x1_y1, int x2_y1,
                                    int x0_y2, int x1_y2, int x2_y2) {
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
                int newRed = 0, newGreen = 0, newBlue = 0;
                for(int filterRow = 0; filterRow < 3; filterRow++) {
                    for(int filterColumn = 0; filterColumn < 3; filterColumn++) {
                        newRed += filterArray[filterRow][filterColumn] * qRed(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset));
                        newGreen += filterArray[filterRow][filterColumn] * qGreen(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset));
                        newBlue += filterArray[filterRow][filterColumn] * qBlue(convertedImage.pixel(filterColumn+columnOffset, filterRow+rowOffset));
                    }
                }
                (newRed < 0) ? newRed = 0 : (newRed > 255) ? newRed = 255 : newRed = newRed;
                (newGreen < 0) ? newGreen = 0 : (newGreen > 255) ? newGreen = 255 : newGreen = newGreen;
                (newBlue < 0) ? newBlue = 0 : (newBlue > 255) ? newBlue = 255 : newBlue = newBlue;
                temp.setPixel(wC, hC, qRgb(newRed, newGreen, newBlue));
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
