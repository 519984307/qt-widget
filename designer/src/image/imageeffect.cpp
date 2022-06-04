#pragma execution_character_set("utf-8")

#include "imageeffect.h"
#include "qdebug.h"

QImage ImageEffect::effect(QImage image, int type, int value)
{
    //获取图像的宽和高
    int w = image.width();
    int h = image.height();

    //遍历图像的每一个像素
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            //获取像素的 RGBA 颜色分量, Qt5.6以后有pixelColor方法
#if 1
            QRgb color = image.pixel(x, y);
            int r = qRed(color);
            int g = qGreen(color);
            int b = qBlue(color);
            int a = qAlpha(color);
#else
            QColor color = image.pixelColor(x, y);
            int r = color.red();
            int g = color.green();
            int b = color.blue();
            int a = color.alpha();
#endif

            //重新设置每个颜色分量的值
            int rr, rg, rb;
            if (type == 1) {
                rr = (r + g + b) / 3;
                rg = rr;
                rb = rr;
            } else if (type == 2) {
                rr = (r * 0.393) + (g * 0.769) + (b * 0.189);
                rg = (r * 0.349) + (g * 0.686) + (b * 0.168);
                rb = (r * 0.272) + (g * 0.534) + (b * 0.131);
            } else if (type == 3) {
                rr = (r + g + b) / 3;
                rg = 0;
                rb = 0;
            } else if (type == 4) {
                rr = 255 - r;
                rg = 255 - g;
                rb = 255 - b;
            } else if (type == 5) {
                rr = qMax(0, qMin(255, r + value));
                rg = qMax(0, qMin(255, g + value));
                rb = qMax(0, qMin(255, b + value));
            } else {
                rr = r;
                rg = g;
                rb = b;
            }

            //设置图像的像素
            image.setPixel(x, y, qRgba(rr, rg, rb, a));
        }
    }

    return image;
}

QImage ImageEffect::gray(QImage image)
{
    return effect(image, 1, 0);
}

QImage ImageEffect::old(QImage image)
{
    return effect(image, 2, 0);
}

QImage ImageEffect::red(QImage image)
{
    return effect(image, 3, 0);
}

QImage ImageEffect::invert(QImage image)
{
    return effect(image, 4, 0);
}

QImage ImageEffect::brightness(QImage image, int value)
{
    return effect(image, 5, value);
}
