#include "renderthread.h"

RenderThread::RenderThread(QObject *parent)
    : QThread(parent)
{

}

RenderThread::~RenderThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void RenderThread::render(double centerX, double centerY, double scaleFactor,
                          QSize resultSize, QString paletteName)
{
    QMutexLocker locker(&mutex);

    this->centerX = centerX;
    this->centerY = centerY;
    this->scaleFactor = scaleFactor;
    this->resultSize = resultSize;
    palette = paletteLoader.loadPalette(paletteName);

    if (!isRunning())
    {
        start(LowPriority);
    } else
    {
        restart = true;
        condition.wakeOne();
    }
}

void RenderThread::run()
{
    forever {
        mutex.lock();
        const QSize resultSize = this->resultSize;
        const double scaleFactor = this->scaleFactor;
        const double centerX = this->centerX;
        const double centerY = this->centerY;
        mutex.unlock();

        int halfWidth = resultSize.width() / 2;
        int halfHeight = resultSize.height() / 2;
        QImage image(resultSize, QImage::Format_Indexed8);
        image.setColorTable(palette);

        const int numPasses = 8;
        int pass = 0;
        while (pass < numPasses)
        {
            const int maxIterations = (1 << (2 * pass + 6)) + 32;
            const int limit = 4;
            bool allBlack = true;

            for (int y = -halfHeight; y < halfHeight; ++y)
            {
                if (restart) break;
                if (abort) return;
                const double ay = centerY + (y * scaleFactor);

                for (int x = -halfWidth; x < halfWidth; ++x)
                {
                    const double ax = centerX + (x * scaleFactor);
                    double a1 = ax;
                    double b1 = ay;
                    int numIterations = 0;
                    do {
                        ++numIterations;
                        const double a2 = (a1 * a1) - (b1 * b1) + ax;
                        const double b2 = (2 * a1 * b1) + ay;
                        if ((a2 * a2) + (b2 * b2) > limit) break;
                        ++numIterations;
                        a1 = (a2 * a2) - (b2 * b2) + ax;
                        b1 = (2 * a2 * b2) + ay;
                        if ((a1 * a1) + (b1 * b1) > limit) break;
                    } while (numIterations < maxIterations);

                    if (numIterations < maxIterations)
                    {
                        double ratio = double(numIterations) / double(maxIterations);
                        int index = ratio * 256;
                        image.setPixel(x + halfWidth, y + halfHeight, index);
                        allBlack = false;
                    } else
                    {
                        image.setPixel(x + halfWidth, y + halfHeight, 0);
                    }
                }
            }
            if (allBlack && pass == 0)
            {
                pass = 4;
            } else
            {
                if (!restart) emit renderedImage(image, scaleFactor);
                ++pass;
            }
        }
        mutex.lock();
        if (!restart) condition.wait(&mutex);
        restart = false;
        mutex.unlock();
    }
}
