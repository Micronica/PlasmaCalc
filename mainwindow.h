#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include "qcustomplot.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setne(); //设置初始电子分布
    void iniplot(QCustomPlot* customPlot, QCPColorMap *colorMap, QCPColorScale *colorScale); //绘图对象的初始设定
    void plot(double a[194][258], QString myString, QCustomPlot* customPlot, QCPColorMap* colorMap, QCPColorScale* colorScale); //绘图

private slots:
    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
