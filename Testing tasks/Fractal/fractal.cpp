#include "fractal.h"
#include "ui_fractal.h"

Fractal::Fractal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fractal)
{
    ui->setupUi(this);
    connect(ui->menu->actions()[0], SIGNAL(triggered()), this, SLOT(openSettings()));
    connect(ui->menu->actions()[1], SIGNAL(triggered()), this, SLOT(saveImage()));
    connect(&thread, &RenderThread::renderedImage, this, &Fractal::updatePixmap);
    connect(&settings, &Dialog::sendSettings, this, &Fractal::applySettings);

    setWindowTitle(tr("Mandelbrot"));
}

Fractal::~Fractal()
{
    delete ui;
}

void Fractal::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    thread.render(centerX, centerY, curScale, renderSize, paletteName);
    painter.drawPixmap(QPoint(), pixmap);
}

void Fractal::openSettings()
{
    settings.exec();
}

void Fractal::applySettings()
{
    QStringList newSettings = settings.getSettings();
    renderSize = QSize(newSettings[0].toInt(), newSettings[1].toInt());
    paletteName = newSettings[2];
    this->resize(renderSize);
    curScale = 2.8/renderSize.width(); // a scale that fits the fractal nicely along the x axis
    thread.render(centerX, centerY, curScale, renderSize, paletteName);
}

void Fractal::saveImage()
{
    QFile file("fractal.png");
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
}

void Fractal::updatePixmap(const QImage &image, double scaleFactor)
{
    pixmap = QPixmap::fromImage(image);
    pixmapScale = scaleFactor;
    update();
}
