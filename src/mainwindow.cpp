#include "mainwindow.h"

#include <cstring>

#include "QDebug"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->null_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->h8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_skob1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_skob2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));

  x_valid();
  credit_valid();
  interest_rate_valid();
}

MainWindow::~MainWindow() { delete ui; }

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

char *MainWindow::get_input_array() {
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

void MainWindow::on_AC_clicked() { ui->label->clear(); }

void MainWindow::on_pushButton_equals_clicked() {
  char *input_array = get_input_array();
  if (input_array == nullptr || input_array[0] == '\0') {
    ui->label->setText("Ошибка: Пустая строка");
    free(input_array);
    return;
  }

  int output = validation_array(input_array);
  if (output == 0) {
    int number_lexem = 0;
    lexem *rpn_array = reverse_polish_notation(input_array, &number_lexem);
    double result = 0.0;
    double x_val = ui->x_val->text().toDouble();
    output = calculate(rpn_array, number_lexem, &result, x_val);
    if (output == 0) {
      if (isinf(result) || isnan(result) == OK) {
        char result_str[255] = {'\0'};
        sprintf(result_str, "%.10g", result);
        ui->label->setText(result_str);
      } else {
        ui->label->setText("INVALID_DATA_LINE");
      }
    }
    free(rpn_array);
    rpn_array = nullptr;
  } else {
    ui->label->setText("Ошибка: Некорректное выражение");
  }
  free(input_array);
}

void MainWindow::on_pushButton_plmin_clicked() {
  QPushButton *button = (QPushButton *)sender();
  double all_numbers;

  if (button->text() == "+/-") {
    all_numbers = (ui->label->text()).toDouble();
    all_numbers = -all_numbers;
    ui->label->setText(QString::number(all_numbers, 'g', 15));
  }
}

void MainWindow::on_del_clicked() {
  QString prev_text = ui->label->text();
  prev_text.remove(prev_text.size() - 1, 1);
  ui->label->setText(prev_text);
}

void MainWindow::x_valid() {
  QRegularExpression regx("[-]?([0-9]*)[.]?[0-9]*");
  QValidator *validator = new QRegularExpressionValidator(regx, this);
  ui->x_val->setValidator(validator);
}

void MainWindow::credit_valid() {
  QRegularExpression regx("[0-9]*");
  QValidator *validator = new QRegularExpressionValidator(regx, this);
  ui->loan_amount->setValidator(validator);
  ui->loan_term->setValidator(validator);
}

void MainWindow::interest_rate_valid() {
  QRegularExpression regx("([0-9]*)[.]?[0-9]*");
  QValidator *validator = new QRegularExpressionValidator(regx, this);
  ui->interest_rate->setValidator(validator);
}
