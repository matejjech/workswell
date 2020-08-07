#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QString>
#include <QDir>
#include <QStringList>
#include <QFile>
#include <QVector>
#include <QRgb>
#include <QTextStream>

class ColorPalette
{
public:
    ColorPalette();
    QVector<QRgb> loadPalette(QString fileName);
};

#endif // COLORPALETTE_H
