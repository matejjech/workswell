#include "colorpalette.h"

ColorPalette::ColorPalette()
{
    QDir::setCurrent("../Fractal");
}

QVector<QRgb> ColorPalette::loadPalette(QString fileName)
{
    QVector<QRgb> palette;
    QString path = "./palettes/" + fileName;
    QFile paletteFile(path);
    if (paletteFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&paletteFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList values = line.split(";");
            palette.append(qRgb(values[0].toInt(), values[1].toInt(), values[2].toInt()));
        }
    }
    return palette;
}
