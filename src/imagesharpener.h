#ifndef IMAGESHARPENER_H
#define IMAGESHARPENER_H

#include <QPixmap>

class ImageSharpener
{
public:
    ImageSharpener();
    static QPixmap filterImage(const QPixmap *image);
    static void setFilterArray(float x0_y0, float x1_y0, float x2_y0,
                               float x0_y1, float x1_y1, float x2_y1,
                               float x0_y2, float x1_y2, float x2_y2);
private:
    static float filterArray[3][3];
};

#endif // IMAGESHARPENER_H
