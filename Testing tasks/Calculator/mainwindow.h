#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTextEdit>
#include <QButtonGroup>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void digit_clicked();

    void binary_clicked();

    void unary_clicked();

    void prev_clicked();

    void res_clicked();

    void clear_clicked();

    void all_clear_clicked();

private:
    Ui::MainWindow *ui;
    bool clear_input = true;
    bool decimal_placed = false;
    bool result_pressed = false;
    bool operator_pressed = false;
    double result = 0.0;
    double operand = 0.0;
    QChar lastOperation = '+';
    QVector<double> results;
    QVector<double>::Iterator results_iterator = results.begin();

    void clear_text();
    void compute_res();

};
#endif // MAINWINDOW_H
