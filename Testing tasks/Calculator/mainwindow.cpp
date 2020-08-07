#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup* digits = new QButtonGroup(this);
    digits->addButton(ui->button_0);
    digits->addButton(ui->button_1);
    digits->addButton(ui->button_2);
    digits->addButton(ui->button_3);
    digits->addButton(ui->button_4);
    digits->addButton(ui->button_5);
    digits->addButton(ui->button_6);
    digits->addButton(ui->button_7);
    digits->addButton(ui->button_8);
    digits->addButton(ui->button_9);
    digits->addButton(ui->button_dot);

    QButtonGroup* binaryOperators = new QButtonGroup(this);
    binaryOperators->addButton(ui->button_add);
    binaryOperators->addButton(ui->button_sub);
    binaryOperators->addButton(ui->button_div);
    binaryOperators->addButton(ui->button_mul);

    QButtonGroup* unaryOperators = new QButtonGroup(this);
    unaryOperators->addButton(ui->button_pow);
    unaryOperators->addButton(ui->button_sqrt);

    foreach(QAbstractButton *button, digits->buttons()) {
        connect(button, &QPushButton::clicked, this, &MainWindow::digit_clicked);
    }

    foreach(QAbstractButton *button, binaryOperators->buttons()) {
        connect(button, &QPushButton::clicked, this, &MainWindow::binary_clicked);
    }

    foreach(QAbstractButton *button, unaryOperators->buttons()) {
        connect(button, &QPushButton::clicked, this, &MainWindow::unary_clicked);
    }

    connect(ui->button_res, &QPushButton::clicked, this, &MainWindow::res_clicked);
    connect(ui->button_prev, &QPushButton::clicked, this, &MainWindow::prev_clicked);
    connect(ui->button_c, &QPushButton::clicked, this, &MainWindow::clear_clicked);
    connect(ui->button_ac, &QPushButton::clicked, this, &MainWindow::all_clear_clicked);

    setWindowTitle("Calculator");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear_text()
{
    ui->textEdit->clear();
    clear_input = false;
    decimal_placed = false;
}

void MainWindow::clear_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::all_clear_clicked()
{
    ui->textEdit->clear();
    result = 0;
    operand = 0;
    clear_input = true;
    decimal_placed = false;
    result_pressed = false;
    operator_pressed = false;;
    lastOperation = '+';
    results.clear();
    results_iterator = results.begin();
}

void MainWindow::compute_res()
{
    if (lastOperation == '+') result = result + operand;
    else if (lastOperation == '-') result = result - operand;
    else if (lastOperation == '*') result = result * operand;
    else if (lastOperation == '/') result = result / operand;
    ui->textEdit->setText(QString::number(result));
    results.push_back(result);
    results_iterator = results.end() - 1;
}

void MainWindow::digit_clicked()
{
    if (clear_input) clear_text();
    QPushButton *sourceButton = qobject_cast<QPushButton *>(sender());
    QString value = sourceButton->text();
    if (value == QString("."))
    {
        if (decimal_placed == false) decimal_placed = true;
        else return;
    }
    operator_pressed = false;
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->insertPlainText (value);
    ui->textEdit->moveCursor (QTextCursor::End);
}

void MainWindow::binary_clicked()
{
    if (!operator_pressed)
    {
        clear_input = true;
        if (!result_pressed)
        {
            operand = ui->textEdit->toPlainText().toDouble();
            compute_res();
        } else
        {
            result = ui->textEdit->toPlainText().toDouble();
        }
    }
    lastOperation = qobject_cast<QPushButton *>(sender())->text().back();
    result_pressed = false;
    operator_pressed = true;
}

void MainWindow::unary_clicked()
{
    clear_input = true;
    QString operation = qobject_cast<QPushButton *>(sender())->text();
    double value = ui->textEdit->toPlainText().toDouble();
    if (operation == "pow")
    {
        value = qPow(value, 2);
        ui->textEdit->setText(QString::number(value));
    }
    else
    {
        value = qSqrt(value);
        ui->textEdit->setText(QString::number(value));
    }
    results.push_back(value);
    results_iterator = results.end() - 1;
}

void MainWindow::prev_clicked()
{
    if (results_iterator != results.begin())
    {
        --results_iterator;
        result = *results_iterator;
        ui->textEdit->setText(QString::number(result));
    }
}

void MainWindow::res_clicked()
{
    if (!operator_pressed)
    {
        if (!result_pressed) operand = ui->textEdit->toPlainText().toDouble();
        compute_res();
        result_pressed = true;
        clear_input = true;
    }
}
