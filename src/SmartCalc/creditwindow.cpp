#include "creditwindow.h"
#include "ui_creditwindow.h"
#include "mainwindow.h"

CreditWindow::CreditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditWindow)
{
    ui->setupUi(this);
    ui->radioButton_annuity->setChecked(true);
}

CreditWindow::~CreditWindow()
{
    delete ui;
}

double CreditWindow::annuity_payment(double sum, double percent, int term) {
    double monthly_rate = percent / 12 / 100;
    double factor = pow(1 + monthly_rate, term);
    return sum * (monthly_rate * factor) / (factor - 1);
}

double CreditWindow::diff_payment(double sum, double percent, int term, int month) {
    double monthly_rate = percent / 12 / 100;
    return (sum / term) + (sum - (sum * (month - 1) / term)) * monthly_rate;
}

void CreditWindow::on_pushButton_calculate_clicked()
{
    QString per_month_result;
    double sum = ui->doubleSpinBox_sum->value();
    int term = ui->spinBox_term->value();
    int percent = ui->spinBox_percent->value();
    double monthly_payment = 0, total_payment = 0, overpayment = 0, first_payment = 0;
    if (ui->radioButton_annuity->isChecked()) {
        monthly_payment = annuity_payment(sum, percent, term);
        total_payment = monthly_payment * term;
        overpayment = total_payment - sum;
        per_month_result = QString::number(monthly_payment, 'f', 2) + " ₽";
    } else if (ui->radioButton_diff->isChecked()) {
        monthly_payment = diff_payment(sum, percent, term, 1);
        first_payment = monthly_payment;
        for (int i = 0; i < term; i++) {
            total_payment += monthly_payment;
            overpayment = total_payment - sum;
            monthly_payment = diff_payment(sum, percent, term, i + 1);
        }
        per_month_result = QString::number(first_payment, 'f', 2) + " ₽ ... " + QString::number(monthly_payment, 'f', 2) + " ₽";
    }
    ui->label_permonth_value->setText(per_month_result);
    ui->label_charges_value->setText(QString::number(overpayment, 'f', 2) + " ₽");
    ui->label_fullsum_value->setText(QString::number(total_payment, 'f', 2) + " ₽");
}

