#include "plotwindow.h"
#include "ui_plotwindow.h"

#include "mainwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::get_str(QString str, char *input) {
  QByteArray array = str.toLocal8Bit();
  char *new_str = array.data();
  int i;
  for (i = 0; i < 255 && *new_str; i++) {
    input[i] = *new_str;
    new_str++;
  }
  input[i] = '\0';
}

void PlotWindow::get_input(QString str) {
  this->str = str;
    char input[256] = {0};
    get_str(str, input);
    drawGraph();
}

void PlotWindow::drawGraph() {
    char input[256] = {0};
    get_str(str, input);
    xBegin = ui->doubleSpinBox_min_x->value();
    xEnd = ui->doubleSpinBox_max_x->value();
    yBegin = ui->doubleSpinBox_min_y->value();
    yEnd = ui->doubleSpinBox_max_y->value();
    double step = (xEnd - xBegin) / 10000;
    double X = xBegin;
    while (X <= xEnd) {
      double res = get_result(X, input);
      x.push_back(X);
      y.push_back(res);
      X += step;
    }
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    ui->widget->replot();
}

void PlotWindow::on_pushButton_clicked()
{
        ui->widget->clearGraphs();
        drawGraph();
}

