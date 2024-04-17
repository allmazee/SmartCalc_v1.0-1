#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdio.h>

#include <QMainWindow>
#include <QMessageBox>

#include "plotwindow.h"
#include "creditwindow.h"

extern "C" {
#include "../smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PlotWindow *plot_window;
    CreditWindow *credit_window;


private slots:
 void digits();
 void operators();
 void functions();
 void on_pushButton_dot_clicked();
 void on_pushButton_del_clicked();
 void on_pushButton_clean_clicked();
 void on_pushButton_equals_clicked();
 double get_res();
 void on_pushButton_graph_clicked();
//  void on_pushButton_credit_clicked();

 void on_pushButton_credit_clicked();

signals:
 void plot_clicked(QString input);
};
#endif // MAINWINDOW_H
