#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>

using namespace std;

namespace Ui
{
    class Videoplayer;
}

class Videoplayer : public QDialog
{
    Q_OBJECT

public:
    explicit Videoplayer(QWidget *parent = 0);
    ~Videoplayer();
    void writevideo(string myString); //将图片转换为视频
    void locate(QString myString, QVideoWidget* myVideoWidget, QMediaPlayer* player); //将视频定位到QVideoWidget上

private slots:
   void on_pauseButton_clicked();
   void on_playButton_clicked();
   void on_stopButton_clicked();
   void pause_after_stop(); //将“终态”转变为“暂停态”，防止黑屏

private:
    Ui::Videoplayer *ui;
    QMediaPlayer *player1, *player2, *player3, *player4, *player5, *player6;

};

#endif // VIDEOPLAYER_H
