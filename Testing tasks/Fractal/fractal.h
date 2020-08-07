#ifndef FRACTAL_H
#define FRACTAL_H

#include <QMainWindow>
#include <QImage>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <colorpalette.h>
#include <renderthread.h>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Fractal; }
QT_END_NAMESPACE

class Fractal : public QMainWindow
{
    Q_OBJECT

public:
    Fractal(QWidget *parent = nullptr);
    ~Fractal();

private slots:
    void updatePixmap(const QImage &image, double scaleFactor);
    void openSettings();
    void saveImage();
    void applySettings();

private:
    Ui::Fractal *ui;
    void paintEvent(QPaintEvent *event) override;
    QPixmap pixmap;
    ColorPalette palette;
    RenderThread thread;
    Dialog settings;
    QSize renderSize = QSize(700, 600);
    QString paletteName = "Iron1";
    double centerX = -0.7;
    double centerY = -0.04;
    double pixmapScale = 0.004;
    double curScale = 0.004;
};
#endif // FRACTAL_H
