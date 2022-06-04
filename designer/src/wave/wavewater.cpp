#pragma execution_character_set("utf-8")

#include "wavewater.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

WaveWater::WaveWater(QWidget *parent) : QWidget(parent)
{
    damping = 5;
    refractive = 3;
    stoneSize = 10;
    stoneWeight = 100;
    image = QPixmap(":/image/head.jpg");

    imageWidth = 0;
    imageHeight = 0;
    waveBuffer1 = 0;
    waveBuffer2 = 0;

    isStoped = true;
    isPressed = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawImage()));
    timer->setInterval(20);

    setImage(image);
}

WaveWater::~WaveWater()
{
    if (timer->isActive()) {
        timer->stop();
    }

    //释放波纹数据二维表,先释放一维,再释放二维
    if (waveBuffer1) {
        for (int i = 0; i < imageWidth; i++) {
            if (waveBuffer1[i]) {
                delete []waveBuffer1[i];
            }
        }
        delete []waveBuffer1;
    }

    if (waveBuffer2) {
        for (int i = 0; i < imageWidth; i++) {
            if (waveBuffer2[i]) {
                delete []waveBuffer2[i];
            }
        }
        delete []waveBuffer2;
    }
}

void WaveWater::mousePressEvent(QMouseEvent *e)
{
    if (image.isNull()) {
        return;
    }

    isPressed = true;
    lastPoint = e->pos();
}

void WaveWater::mouseMoveEvent(QMouseEvent *e)
{

}

void WaveWater::mouseReleaseEvent(QMouseEvent *)
{
    if (!isPressed) {
        return;
    }

    this->dropStone(lastPoint.x(), lastPoint.y(), stoneSize, stoneWeight);
    isPressed = false;
    if (!timer->isActive()) {
        timer->start();
    }
}

void WaveWater::paintEvent(QPaintEvent *)
{
    if (image.isNull()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);

    //如果停止阶段则绘制原图,否则绘制渲染图
    if (isStoped) {
        painter.drawPixmap(0, 0, image);
    } else {
        painter.drawPixmap(0, 0, pixmap);
    }
}

void WaveWater::drawImage()
{
    if (isStoped) {
        timer->stop();
    } else {
        this->waveRender();
        this->update();
    }
}

void WaveWater::waveSpread()
{
    quint32 counter = 0;
    // 波能渐变
    for (int h = 1; h < imageHeight - 1; h++) {
        for (int w = 1; w < imageWidth - 1; w++) {
            //波能扩散
            waveBuffer2[w][h] = ((waveBuffer1[w - 1][h] + waveBuffer1[w + 1][h] + waveBuffer1[w][h - 1] + waveBuffer1[w][ h + 1]) >> 1) - waveBuffer2[w][h];
            //波能衰减
            waveBuffer2[w][h] -= (waveBuffer2[w][h] >> damping);
            //判断波动释放结束
            if (waveBuffer1[w][h] - waveBuffer2[w][h]) {
                counter++;
            }
        }
    }

    //交换缓冲区
    int **temp = waveBuffer1;
    waveBuffer1 = waveBuffer2;
    waveBuffer2 = temp;

    //设置释放完成
    isStoped = counter ? false : true;
}

void WaveWater::waveRender()
{
    //先改变波纹振幅
    waveSpread();
    if (isStoped) {
        return;
    }

    int offsetX = 0;
    int offsetY = 0;

    //扫描位图
    for (int y = 1; y < imageHeight - 1; y++) {
        for (int x = 1; x < imageWidth - 1; x++) {
            //根据波幅计算位图数据偏移值,渲染点(x,y)对应原始图片(offsetX,offsetY)
            offsetX = x + ((waveBuffer1[x - 1][y] - waveBuffer1[x + 1][y]) >> refractive);
            offsetY = y + ((waveBuffer1[x][y - 1] - waveBuffer1[x][y + 1]) >> refractive);
            //复制象素
            if (0 <= offsetX && offsetX < imageWidth - 1 && 0 <= offsetY && offsetY < imageHeight - 1) {
                QRgb color = imageOrigin.pixel(offsetX, offsetY);
                imageRender.setPixel(x, y, color);
            }
        }
    }

    pixmap = QPixmap::fromImage(imageRender);
    //pixmap.convertFromImage(imageRender);
}

void WaveWater::dropStone(int x, int y, int stoneSize, int stoneWeight)
{
    isStoped = false;
    int posX = 0;
    int posY = 0;

    for (int h = -stoneSize; h < stoneSize; h++) {
        for (int w = -stoneSize; w < stoneSize; w++) {
            posX = x + w;
            posY = y + h;

            //控制范围,不能超出图片
            if (posX < 0 || posX >= imageWidth || posY < 0 || posY >= imageHeight) {
                continue;
            }

            //点(w,h)在一个圆形区域内,初始化波能缓冲区1
            if (h * h + w * w <= stoneSize * stoneSize) {
                waveBuffer1[posX][posY] = -stoneWeight;
            }
        }
    }
}

int WaveWater::getDamping() const
{
    return this->damping;
}

int WaveWater::getRefractive() const
{
    return this->refractive;
}

int WaveWater::getStoneSize() const
{
    return this->stoneSize;
}

int WaveWater::getStoneWeight() const
{
    return this->stoneWeight;
}

QPixmap WaveWater::getImage() const
{
    return this->image;
}

QSize WaveWater::sizeHint() const
{
    return QSize(500, 300);
}

QSize WaveWater::minimumSizeHint() const
{
    return QSize(50, 30);
}

void WaveWater::setDamping(int damping)
{
    if (this->damping != damping) {
        this->damping = damping;
        this->update();
    }
}

void WaveWater::setRefractive(int refractive)
{
    if (this->refractive != refractive) {
        this->refractive = refractive;
        this->update();
    }
}

void WaveWater::setStoneSize(int stoneSize)
{
    if (stoneSize >= 5 && this->stoneSize != stoneSize) {
        this->stoneSize = stoneSize;
        this->update();
    }
}

void WaveWater::setStoneWeight(int stoneWeight)
{
    if (stoneWeight >= 5 && stoneWeight <= 1024 && this->stoneWeight != stoneWeight) {
        this->stoneWeight = stoneWeight;
        this->update();
    }
}

void WaveWater::setImage(const QPixmap &pixmap)
{
    if (pixmap.isNull()) {
        return;
    }

    //设置对应的图像,用于后期运算
    this->image = pixmap;
    QImage img = image.toImage();
    imageOrigin = img;
    imageRender = img;
    imageWidth = img.width();
    imageHeight = img.height();

    //分配波能缓冲区
    waveBuffer1 = new int *[imageWidth];
    waveBuffer2 = new int *[imageWidth];
    memset(waveBuffer1, 0, sizeof(int) *imageWidth);
    memset(waveBuffer2, 0, sizeof(int) *imageWidth);
    for (int i = 0; i < imageWidth; i++) {
        waveBuffer1[i] = new int[imageHeight];
        waveBuffer2[i] = new int[imageHeight];

        //采用旧c++方法初始化二维数组
        for (int j = 0; j < imageHeight; j++) {
            waveBuffer1[i][j] = 0;
            waveBuffer2[i][j] = 0;
        }
    }
}
