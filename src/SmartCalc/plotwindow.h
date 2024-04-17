#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include <QVector>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

private:
    Ui::PlotWindow *ui;
    double xBegin, xEnd, yBegin, yEnd, X, h;
    int N;
    QVector<double> x, y;
    QString str;

public slots:
    void get_input(QString str);

private slots:
    void get_str(QString str, char *input);
    void drawGraph();
    void on_pushButton_clicked();
};

#endif // PLOTWINDOW_H
