#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstdio>

#include <QProgressDialog>
#include <QDir>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoplayer.h"

#include "transvalue.h"
#include "edgex.h"
#include "edgey.h"
#include "convect.h"
#include "dif3.h"
#include "sden.cpp"
#include "sw.cpp"
#include "sve.h"
#include "Poisson.cpp"

const double PI = 3.1415926535897;

extern double alx;//x方向物理长度
extern double aly;//y方向物理长度
extern double tau;//时间间隔
extern double dif;//kT
extern double arho;//归一化常数
extern double pert;//扰动量
extern int ntp;//多少时间间隔出一张
extern int nts;//出多少张图
extern double alpha0;
extern int number;//可改变变量,定义波长设置
extern double ky;
extern double dx;
extern double dy;
extern double dxt1p5;
extern double dyt1p5;
extern double dx1p5;
extern double dy1p5;
extern double dtx;
extern double dty;

extern double wi[194][258];
extern double w[194][258];
extern double phi[194][258];
extern double nei[194][258];
extern double ne[194][258];
extern double vx[194][258];
extern double vy[194][258];
extern double delta_phi[194][258]; //设置电势扰动量
extern double delta_ne[194][258]; //设置密度扰动量

static int t = 1; //已出图片数

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Plasma Calculation");
    QDir("/Applications").mkdir(".PlasmaCalc"); //新建临时文件夹用于存放图片与视频
}

MainWindow::~MainWindow()
{
    delete ui;
    QDir("/Applications/.PlasmaCalc").removeRecursively(); //删除临时文件夹
}

void MainWindow::on_runButton_clicked()
{
    //读取输入值，不输入时采用默认值
    if(ui->getAlpha->text()!="") {alpha0=ui->getAlpha->text().toDouble();}
    if(ui->getPert->text()!="") {pert=ui->getPert->text().toDouble();}
    if(ui->getDif->text()!="") {dif=ui->getDif->text().toDouble();}
    if(ui->getNtp->text()!="") {ntp=ui->getNtp->text().toInt();}
    if(ui->getNts->text()!="") {nts=ui->getNts->text().toInt()/ntp;}

    //用QProgressDialog类显示计算进度
    QProgressDialog progress("Calculating...", "Cancel", 0, nts*ntp, this);
    progress.setWindowModality(Qt::WindowModal);

    setne();
    transvalue(nei,ne);

    //初始化绘图类对象
    QCustomPlot* customPlot1 = new QCustomPlot;
    QCustomPlot* customPlot2 = new QCustomPlot;
    QCustomPlot* customPlot3 = new QCustomPlot;
    QCustomPlot* customPlot4 = new QCustomPlot;
    QCustomPlot* customPlot5 = new QCustomPlot;
    QCustomPlot* customPlot6 = new QCustomPlot;

    //初始化QCPColorMap，即色图
    QCPColorMap* colorMap1 = new QCPColorMap(customPlot1->xAxis, customPlot1->yAxis);
    QCPColorMap* colorMap2 = new QCPColorMap(customPlot2->xAxis, customPlot2->yAxis);
    QCPColorMap* colorMap3 = new QCPColorMap(customPlot3->xAxis, customPlot3->yAxis);
    QCPColorMap* colorMap4 = new QCPColorMap(customPlot4->xAxis, customPlot4->yAxis);
    QCPColorMap* colorMap5 = new QCPColorMap(customPlot5->xAxis, customPlot5->yAxis);
    QCPColorMap* colorMap6 = new QCPColorMap(customPlot6->xAxis, customPlot6->yAxis);

    //初始化QCPColorScale，即色图标度
    QCPColorScale* colorScale1 = new QCPColorScale(customPlot1);
    QCPColorScale* colorScale2 = new QCPColorScale(customPlot2);
    QCPColorScale* colorScale3 = new QCPColorScale(customPlot3);
    QCPColorScale* colorScale4 = new QCPColorScale(customPlot4);
    QCPColorScale* colorScale5 = new QCPColorScale(customPlot5);
    QCPColorScale* colorScale6 = new QCPColorScale(customPlot6);

    //绘图类对象的初始设定
    iniplot(customPlot1, colorMap1, colorScale1);
    iniplot(customPlot2, colorMap2, colorScale2);
    iniplot(customPlot3, colorMap3, colorScale3);
    iniplot(customPlot4, colorMap4, colorScale4);
    iniplot(customPlot5, colorMap5, colorScale5);
    iniplot(customPlot6, colorMap6, colorScale6);

    for( ;t<=nts;t++)
    {
        for(int tt=1;tt<=ntp;tt++)
        {
            sve();
            double f=0.5;
            double fi=0.5;
            sw(f,fi);
            sden(f,fi);
            Poisson();
            sve();
            f=1.0;
            fi=0.0;
            sw(f,fi);
            sden(f,fi);
            Poisson();
            progress.setValue(t*ntp-ntp+tt);
            if(progress.wasCanceled())
            {
                t=1;
                return;
            }
        }

        plot(phi, "phi", customPlot1, colorMap1, colorScale1);
        plot(ne, "ne", customPlot2, colorMap2, colorScale2);
        plot(delta_ne, "delta ne", customPlot3, colorMap3, colorScale3);
        plot(wi, "wi", customPlot4, colorMap4, colorScale4);
        plot(vx, "vx", customPlot5, colorMap5, colorScale5);
        plot(vy, "vy", customPlot6, colorMap6, colorScale6);
    }

    customPlot1->~QCustomPlot();
    customPlot2->~QCustomPlot();
    customPlot3->~QCustomPlot();
    customPlot4->~QCustomPlot();
    customPlot5->~QCustomPlot();
    customPlot6->~QCustomPlot();

    Videoplayer videoplayer;
    videoplayer.exec();
}

void MainWindow:: setne()//设置初始参数:包括密度与密度扰动
{
    srand(time(NULL));
    for(int j=0;j<258;j++)
    {
        for(int i=0;i<194;i++)
        {
            ne[i][j]=1.+pert*(rand()%10000)+exp(-(i/50.)*(i/50.));
            nei[i][j]=ne[i][j];
         }
    }
}

void MainWindow::iniplot(QCustomPlot *customPlot, QCPColorMap* colorMap, QCPColorScale* colorScale)
{
    //坐标轴设定
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("y");
    customPlot->yAxis->setLabel("x");

    //设置colorScale并添加到customPlot中
    colorScale->setType(QCPAxis::atBottom);
    colorScale->axis()->setNumberPrecision(2);
    customPlot->plotLayout()->addElement(1, 0, colorScale);

    //colorMap的初始设定
    colorMap->data()->setSize(258, 194);
    colorMap->data()->setRange(QCPRange(0, 30.), QCPRange(0, 20.));
    colorMap->setColorScale(colorScale);
    colorMap->setGradient(QCPColorGradient::gpJet);
}

void MainWindow::plot(double a[194][258], QString myString, QCustomPlot* customPlot, QCPColorMap* colorMap, QCPColorScale* colorScale)
{
    //设置colorMap数值
    double x, y, z;
    for (int xIndex=0; xIndex<194; ++xIndex)
    {
      for (int yIndex=0; yIndex<258; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        z=a[xIndex][yIndex];
        colorMap->data()->setCell(yIndex, xIndex, z);
      }
    }
    colorMap->rescaleDataRange(); //更新数据范围
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot); //设置边沿
    customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, marginGroup);
    colorScale->setMarginGroup(QCP::msLeft|QCP::msRight, marginGroup);
    customPlot->rescaleAxes(); //更新坐标轴以适应新的数据
    customPlot->savePng("/Applications/.PlasmaCalc/"+myString+QString::number(t)+".png", 300, 300, 1.0, 100);
}
