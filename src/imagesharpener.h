#ifndef IMAGESHARPENER_H
#define IMAGESHARPENER_H

#include <QPixmap>

class ImageSharpener
{
public:
    ImageSharpener();
    static QPixmap filterImage(const QPixmap *image);
    static void setFilterArray(int x0_y0, int x1_y0, int x2_y0,
                               int x0_y1, int x1_y1, int x2_y1,
                               int x0_y2, int x1_y2, int x2_y2);
private:
    static int filterArray[3][3];
};

#endif // IMAGESHARPENER_H
