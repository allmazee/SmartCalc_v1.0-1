#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_open, SIGNAL(clicked()), this,
            SLOT(operators()));
    connect(ui->pushButton_close, SIGNAL(clicked()), this,
            SLOT(operators()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(operators()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits() {
    QPushButton *button = (QPushButton *)sender();

    ui->label_input->setText(ui->label_input->text() + button->text());
  }

void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();

  ui->label_input->setText(ui->label_input->text() + button->text());
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();

  ui->label_input->setText(ui->label_input->text() + button->text() + '(');
}

void MainWindow::on_pushButton_dot_clicked() {
  ui->label_input->setText(ui->label_input->text() + '.');
}

void MainWindow::on_pushButton_del_clicked() {
  QString str = ui->label_input->text();
  str.chop(1);
  ui->label_input->setText(str);
  ui->label_result->clear();
}

void MainWindow::on_pushButton_clean_clicked() {
  ui->label_input->clear();
  ui->label_result->clear();
}

void MainWindow::on_pushButton_equals_clicked() {
  double res = get_res();
  if (isnan(res)) {
    ui->label_result->setText("ERROR");
    ui->label_input->clear();
  } else {
    ui->label_result->setText(QString::number(res, 'g', 8));
  }
}

double MainWindow::get_res() {
  QByteArray array = ui->label_input->text().toLocal8Bit();
  char *str = array.data();
  char input[256] = {0};
  int i;
  for (i = 0; i < 255 && *str; i++) {
    input[i] = *str;
    str++;
  }
  input[i] = '\0';
  double x = 0;
  if (ui->label_input->text().contains("x")) {
    x = ui->lineEdit_x->text().toDouble();
  }
  double res = get_result(x, input);
  return res;
}

//TODO: PLOTWINDOW переход



void MainWindow::on_pushButton_graph_clicked()
{
      QString labelText = ui->label_input->text();
      double res = get_res();
      if (labelText.isEmpty()) {
          ui->label_result->setText("Empty input");
          ui->label_input->clear();
      } else if (isnan(res)) {
          ui->label_result->setText("ERROR");
          ui->label_input->clear();
      } else {
        plot_window = new PlotWindow;
        plot_window->show();
        connect(this, &MainWindow::plot_clicked, plot_window,
                &PlotWindow::get_input);
        emit plot_clicked(labelText);
    }
}


void MainWindow::on_pushButton_credit_clicked()
{
    credit_window = new CreditWindow;
    credit_window->show();

}

