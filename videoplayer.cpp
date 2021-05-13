#include "videoplayer.h"
#include "ui_videoplayer.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

extern int nts;

Videoplayer::Videoplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Videoplayer)
{
    ui->setupUi(this);
    setWindowTitle("Evolution");

    //图像转换为视频
    writevideo("phi");
    writevideo("wi");
    writevideo("delta ne");
    writevideo("ne");
    writevideo("vx");
    writevideo("vy");

    //新建QMediaPlayer对象
    player1 = new QMediaPlayer;
    player2 = new QMediaPlayer;
    player3 = new QMediaPlayer;
    player4 = new QMediaPlayer;
    player5 = new QMediaPlayer;
    player6 = new QMediaPlayer;

    //用QMediaPlayer播放已经生成的视频，并定位到QVideoWidget
    locate("phi", ui->phi, player1);
    locate("wi", ui->wi, player2);
    locate("delta ne", ui->deltane, player3);
    locate("ne", ui->ne, player4);
    locate("vx", ui->vx, player5);
    locate("vy", ui->vy, player6);

    //初始进入暂停模式，显示第一帧，防止黑屏
    player1->pause();
    player2->pause();
    player3->pause();
    player4->pause();
    player5->pause();
    player6->pause();

    //将QMediaPlayer状态转变的信号与pause_after_stop槽关联
    connect(player1, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);
    connect(player2, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);
    connect(player3, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);
    connect(player4, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);
    connect(player5, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);
    connect(player6, &QMediaPlayer::stateChanged, this, &Videoplayer::pause_after_stop);

    //QMediaPlayer的时长与QSlider最大值同步
    connect(player1, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(player2, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(player3, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(player4, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(player5, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);
    connect(player6, &QMediaPlayer::durationChanged, ui->slider, &QSlider::setMaximum);

    //QMediaPlayer的播放进度与QSlider值同步
    connect(player1, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(player2, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(player3, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(player4, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(player5, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);
    connect(player6, &QMediaPlayer::positionChanged, ui->slider, &QSlider::setValue);

    //实现QSlider调控播放进度
    connect(ui->slider, &QSlider::sliderMoved, player1, &QMediaPlayer::setPosition);
    connect(ui->slider, &QSlider::sliderMoved, player2, &QMediaPlayer::setPosition);
    connect(ui->slider, &QSlider::sliderMoved, player3, &QMediaPlayer::setPosition);
    connect(ui->slider, &QSlider::sliderMoved, player4, &QMediaPlayer::setPosition);
    connect(ui->slider, &QSlider::sliderMoved, player5, &QMediaPlayer::setPosition);
    connect(ui->slider, &QSlider::sliderMoved, player6, &QMediaPlayer::setPosition);
}

//实现播放结束后进入暂停状态，防止黑屏
void Videoplayer::pause_after_stop()
{
    if(player1->state()==QMediaPlayer::StoppedState) {player1->pause();}
    if(player2->state()==QMediaPlayer::StoppedState) {player2->pause();}
    if(player3->state()==QMediaPlayer::StoppedState) {player3->pause();}
    if(player4->state()==QMediaPlayer::StoppedState) {player4->pause();}
    if(player5->state()==QMediaPlayer::StoppedState) {player5->pause();}
    if(player6->state()==QMediaPlayer::StoppedState) {player6->pause();}
}

//图像序列转化为视频
void Videoplayer::writevideo(string myString)
{
    VideoWriter writer;
    int codec = CV_FOURCC('M', 'J', 'P', 'G');
    double fps = 25.0;
    string filename0 = "/Applications/.PlasmaCalc/"+myString+".avi";
    writer.open(filename0, codec, fps, Size(300, 300));
    Mat frame;
    for(int i =1; i<=nts; i++)
    {
        string filename = "/Applications/.PlasmaCalc/"+myString + to_string(i) +".png";
        frame = imread(filename);
        writer << frame;
    }
}

//QMediaPlayer读入视频，并定位到QVideoWidget上
void Videoplayer::locate(QString myString, QVideoWidget* myVideoWidget, QMediaPlayer* player)
{
    player->setVideoOutput(myVideoWidget);
    player->setMedia(QUrl::fromLocalFile("/Applications/.PlasmaCalc/"+myString+".avi"));
}

Videoplayer::~Videoplayer()
{
    delete ui;
}

void Videoplayer::on_pauseButton_clicked()
{
    player1->pause();
    player2->pause();
    player3->pause();
    player4->pause();
    player5->pause();
    player6->pause();
}

void Videoplayer::on_playButton_clicked()
{   
    player1->play();
    player2->play();
    player3->play();
    player4->play();
    player5->play();
    player6->play();
}

void Videoplayer::on_stopButton_clicked()
{
    player1->stop();
    player2->stop();
    player3->stop();
    player4->stop();
    player5->stop();
    player6->stop();
}
