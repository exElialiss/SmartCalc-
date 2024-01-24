#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include "QDebug"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->null_2,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->one,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->two,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->three,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->four,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->five,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->six,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->seven,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->h8,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->nine,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->plus,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->dot,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->minus,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_pow,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_del,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_skob1, SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_skob2, SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()),this, SLOT(digit_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()),this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()),this, SLOT(functions()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_numbers() {
    QPushButton *button = (QPushButton *)sender();
    QString text_prev = ui->label->text();
    ui->label->setText(text_prev + button->text());
}

void MainWindow::functions() {
    QPushButton *button = (QPushButton *)sender();
    QString text_prev = ui->label->text();
    ui->label->setText(text_prev + button->text() + '(');
}

char* MainWindow::getInputArray() {
    QString text = ui->label->text();
    size_t size = text.size();
    char *input_array = nullptr;
    if (size > 0) {
        input_array = (char *)calloc(size + 1, sizeof(char));
        std::string convert = text.toStdString();
        for (size_t i = 0; i < size; i++) {
            input_array[i] = convert[i];
        }
        input_array[size] = '\0';
    }
    return input_array;
}

void MainWindow::on_AC_clicked() {
    ui->label->clear();
}

void MainWindow::on_pushButton_equals_clicked()
{
    char* input_array = getInputArray();

    // Добавим проверку на пустую строку перед валидацией
    if (input_array == nullptr || input_array[0] == '\0') {
        ui->label->setText("Ошибка: Пустая строка");
        free(input_array);
        return;
    }

    int output = input_array_validation(input_array);
    if (output == 0) {
        double result = calculate(input_array);

        ui->label->setText(QString::number(result, 'g', 25));
    } else {
        ui->label->setText("Ошибка: Некорректное выражение");
    }
    free(input_array);
}

