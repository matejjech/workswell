#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H
#include <QThread>
#include <QRgb>
#include <QMutex>
#include <QWaitCondition>
#include <QSize>
#include <QImage>
#include <colorpalette.h>

class RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(QObject *parent = nullptr);
    ~RenderThread();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize, QString paletteName);

signals:
    void renderedImage(const QImage &image, double scaleFactor);

protected:
    void run() override;

private:
    QMutex mutex;
    QWaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart = false;
    bool abort = false;
    QVector<QRgb> palette;
    ColorPalette paletteLoader;

};

#endif // RENDERTHREAD_H
