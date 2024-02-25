#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define BUFFER 255
#include <QMainWindow>


#include "qcustomplot.h"

extern "C" {
#include "calculate.h"
#include "reverse_polish_notation.h"
#include "stack.h"
#include "valid.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digit_numbers();
  void functions();
  char *get_input_array();
  void on_AC_clicked();
  void on_pushButton_equals_clicked();
  void on_pushButton_plmin_clicked();
  void on_del_clicked();
  void x_valid();
  void credit_valid();
  void interest_rate_valid();
  void on_pushButton_plot_graph_clicked();
  void set_default_definifion();
  void graph_settings(QCustomPlot *customPlot);
  void check_definifion_value();
  void set_definifion_value();
  lexem *copy_array(lexem *input_array, int number_lexem);
  void plot_graph(const QVector<double> x, const QVector<double> y);
  void set_annutiet_result(const double pay_month, const double overpay,
                           const double result_sum);
  void differentiated_calc(double loan_amount, const int loan_term,
                           const double interest_rate);
  void set_difference_result(const double start_payment,
                             const double end_payment, const double overpay,
                             const double result_sum);
  void on_calc_credit_clicked();

};
#endif  // MAINWINDOW_H
