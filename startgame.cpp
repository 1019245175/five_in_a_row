#include "startgame.h"
#include<QFont>
#include"maingame.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QIcon>
StartGame::StartGame(QWidget *parent) : QWidget(parent)
{
    font = new QFont();
    font->setBold(true);
    font->setPointSize(18);
    GameGroundPictureImage = new QImage();
    GameGroundPictureImage->load(tr("startgame.jpeg"));
    GameGroundPictureLabel = new QLabel(this);
    GameGroundPictureLabel->setPixmap(QPixmap::fromImage(*GameGroundPictureImage));
    GameGroundPictureLabel->contentsRect();
    GameGroundPictureLabel->resize(GameGroundPictureImage->width(),GameGroundPictureImage->height());
    GameGroundPictureLabel->show();
    GameGroundPictureLabel->resize(GameGroundPictureImage->width(),GameGroundPictureImage->height());
    StartGameButton = new QPushButton(tr("开始游戏"),this);
    StartGameButton->show();
  //  StartGameButton->setStyleSheet("background-color: rgb(255,255,150)");
    StartGameButton->resize(200,70);
    StartGameButton->move(GameGroundPictureLabel->width()/2 - StartGameButton->width()/2,GameGroundPictureLabel->height()/2 - StartGameButton->height()-50);
    //StartGameButton->setFlat(true);
    StartGameButton->setStyleSheet("QPushButton {color: red;}QPushButton:pressed {color: red;}");
    StartGameButton->setFont(*font);

    ExitGameButton = new QPushButton(tr("退出游戏"),this);
    ExitGameButton->show();
    ExitGameButton->resize(200,70);
    ExitGameButton->move(GameGroundPictureLabel->width()/2- StartGameButton->width()/2,GameGroundPictureLabel->height()/2);
    ExitGameButton->setStyleSheet("QPushButton {color: red;}QPushButton:pressed {color: red;}");
    ExitGameButton->setFont(*font);
    AboutGameButton = new QPushButton(tr("关于"),this);
    AboutGameButton->resize(200,70);
    AboutGameButton->setStyleSheet("QPushButton {color: red;}QPushButton:pressed {color: red;}");
    AboutGameButton->move(GameGroundPictureLabel->width()/2- StartGameButton->width()/2,GameGroundPictureLabel->height()/2+120);
    AboutGameButton->show();
    AboutGameButton->setFont(*font);
    connectAll();
    setWindowIcon(QIcon("icon.ico"));
    setFixedSize(GameGroundPictureLabel->width(),GameGroundPictureLabel->height());
    
    
}
void StartGame::connectAll()
{
    connect(StartGameButton,SIGNAL(clicked()),this,SLOT(StartGameSlots()));
    connect(ExitGameButton,SIGNAL(clicked()),this,SLOT(ExitGameSlots()));
    connect(AboutGameButton,SIGNAL(clicked()),this,SLOT(AboutSlots()));
    
}
void StartGame::StartGameSlots()
{
    
    MainGame *maingame = new MainGame();
    maingame->show();
    this->close();
}
void StartGame::ExitGameSlots()
{
    this->close();
}
void StartGame::AboutSlots()
{
    QString str = tr("作者:刘志刚 \n")+"Powered:Qt\n" + "IDE:QtCreator\n" +tr("AI借鉴了少量网上代码，图片均来自互联网。")  ;


   QMessageBox::information(this,tr("关于"),str,QMessageBox::Ok);
}

