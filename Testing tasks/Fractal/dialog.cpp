#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->closeBtn, &QPushButton::clicked, this, &Dialog::closeClick);
    connect(ui->applyBtn, &QPushButton::clicked, this, &Dialog::applyClick);

    setWindowTitle("Settings");
}

Dialog::~Dialog()
{
    delete ui;
}

QStringList Dialog::getSettings()
{
    QStringList output;
    output.append(QString::number(width));
    output.append(QString::number(height));
    output.append(paletteName);
    return output;
}

void Dialog::closeClick()
{
    close();
}

void Dialog::applyClick()
{
    bool isInt1, isInt2;
    width = ui->widthEdit->toPlainText().toInt(&isInt1);
    if (!isInt1) ui->widthEdit->setText("");
    height = ui->heightEdit->toPlainText().toInt(&isInt2);
    if (!isInt2) ui->heightEdit->setText("");
    if (!isInt1 || !isInt2) return;
    paletteName = ui->paletteEdit->toPlainText();
    emit sendSettings();
}
