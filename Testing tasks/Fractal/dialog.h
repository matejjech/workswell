#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    QStringList getSettings();
    ~Dialog();

signals:
    void sendSettings();

private slots:
    void closeClick();

    void applyClick();

private:
    Ui::Dialog *ui;
    int width;
    int height;
    QString paletteName;
};

#endif // DIALOG_H
