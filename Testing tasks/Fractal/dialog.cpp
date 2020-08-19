#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->closeBtn, &QPushButton::clicked, this, &Dialog::closeClick);
    connect(ui->applyBtn, &QPushButton::clicked, this, &Dialog::applyClick);
    QDir paletteDir = QDir("./palettes");
    QStringList paletteNames = paletteDir.entryList();
    paletteNames.removeAll(".");
    paletteNames.removeAll("..");
    ui->paletteBox->addItems(paletteNames);
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
    height = ui->heightEdit->toPlainText().toInt(&isInt2);
    if (!isInt1 || !isInt2 || width < 100 || height < 100)
    {
        ui->widthEdit->setText("");
        ui->heightEdit->setText("");
        return;
    }
    paletteName = ui->paletteBox->currentText();
    emit sendSettings();
}
