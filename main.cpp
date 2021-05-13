#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

double alx=20.;//x方向物理长度
double aly=30.;//y方向物理长度
double tau=.005;//时间间隔
double dif=0.01;//kT
double arho=100.;//归一化常数
double pert=1.e-7;//扰动量
int ntp=5;//多少时间间隔出一张
int nts=600;//出多少张图
double alpha0=0.05;

double dx=alx/(194.-1.);
double dy=aly/(258.-1.);
double dxt1p5=arho*tau/(2.*dx);
double dyt1p5=arho*tau/(2.*dy);
double dx1p5=1./(2.*dx);
double dy1p5=1./(2.*dy);
double dtx=dif*tau/(dx*dx);
double dty=dif*tau/(dy*dy);

double wi[194][258]={};
double w[194][258]={};
double phi[194][258]={};
double nei[194][258]={};
double ne[194][258]={};
double vx[194][258]={};
double vy[194][258]={};
double delta_phi[194][258]={};//设置电势扰动量
double delta_ne[194][258]={};//设置密度扰动量

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    return a.exec();
}
