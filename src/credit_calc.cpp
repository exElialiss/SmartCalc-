#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_calc_credit_clicked() {
  ui->pay_month->clear();
  ui->overpay->clear();
  ui->result_sum->clear();

  double loan_amount = ui->loan_amount->text().toDouble();
  int loan_term = ui->loan_term->text().toInt();
  double interest_rate = ui->interest_rate->text().toDouble();
  double pay_month = 0.0, overpay = 0.0, result_sum = 0.0;
  if (loan_amount != 0 && loan_term != 0 && interest_rate != 0) {
    int term = ui->set_period->currentIndex();
    if (term == 0) {
      loan_term *= 12;
    }
    interest_rate /= 100;
    bool set_pay = ui->differentiated->isChecked();
    if (set_pay) {
      differentiated_calc(loan_amount, loan_term, interest_rate);
    } else {
      annutiet_calc(loan_amount, loan_term, interest_rate, &pay_month, &overpay,
                    &result_sum);
      set_annutiet_result(pay_month, overpay, result_sum);
    }
  } else {
    ui->overpay->setText("Ошибка");
    ui->pay_month->setText("Ошибка");
    ui->result_sum->setText("Ошибка");
  }
}

void MainWindow::set_annutiet_result(const double pay_month,
                                     const double overpay,
                                     const double result_sum) {
  QString payment_str = QString::number(pay_month, 'f', 2);
  ui->pay_month->setText(payment_str);

  QString overpayment_str = QString::number(overpay, 'f', 2);
  ui->overpay->setText(overpayment_str);

  QString payment_total_str = QString::number(result_sum, 'f', 2);
  ui->result_sum->setText(payment_total_str);
}

void MainWindow::differentiated_calc(double loan_amount, const int loan_term,
                                     const double interest_rate) {
  QDate date_start = QDate::currentDate();
  double principal_payment = loan_amount / loan_term;
  double procent_payment = 0.0;
  double payment = 0.0;
  double total_pay = 0.0;
  double start_pay = 0.0;
  double end_pay = 0.0;
  double overpay = -loan_amount;
  for (int i = 0; i < loan_term; ++i, loan_amount -= principal_payment,
           date_start = date_start.addMonths(1)) {
    procent_payment = loan_amount * interest_rate * date_start.daysInMonth() /
                      date_start.daysInYear();
    payment = principal_payment + procent_payment;
    if (i == 0) {
      start_pay = payment;
    } else if (i != 0 && i == loan_term - 1) {
      end_pay = payment;
    }
    total_pay += payment;
  }
  overpay += total_pay;
  if (loan_term == 1) {
    set_annutiet_result(start_pay, overpay, total_pay);
  } else {
    set_difference_result(start_pay, end_pay, overpay, total_pay);
  }
}

void MainWindow::set_difference_result(const double start_pay,
                                       const double end_pay,
                                       const double overpay,
                                       const double result_sum) {
  QString start_pay_str = QString::number(start_pay, 'f', 2);
  QString end_pay_str = QString::number(end_pay, 'f', 2);
  QString overpay_str = QString::number(overpay, 'f', 2);
  QString result_sum_str = QString::number(result_sum, 'f', 2);

  QString payment_range = start_pay_str + "..." + end_pay_str;

  ui->pay_month->setText(payment_range);
  ui->overpay->setText(overpay_str);
  ui->result_sum->setText(result_sum_str);
}
