#include "maingame.h"
//1 white  2black
#include<QDebug>
#include<QApplication>
#include<QDesktopWidget>
MainGame::MainGame(QWidget *parent) : QWidget(parent)
{
    time = new QTime();
    time->start();
    showHideTimer = new QTimer();
 
    font = new QFont();
    font->setBold(true);
    font->setPointSize(18);
    chessBlackImage = new QImage();
    chessBlackImage->load(tr("black.png"));
    chessWhiteImage = new  QImage();
    chessWhiteImage->load(tr("white.png"));
    gamegroundImage = new QImage();
    gamegroundImage->load(tr("gameground.jpeg"));
    gamegroundLabel = new QLabel("",this);
    gamegroundLabel->setPixmap(QPixmap::fromImage(*gamegroundImage));
    gamegroundLabel->show();
    chessBoardImage = new QImage();
    chessBoardImage->load(tr("qipan.png"));
    chessBoardLabel = new QLabel("",this);
    chessBoardLabel->setPixmap(QPixmap::fromImage(*chessBoardImage));
    chessBoardLabel->move(this->width()/2-chessBoardLabel->width()/2,this->height()/2-150);
    chessBoardLabel->show();
    chessRedPointImage = new QImage();
    chessRedPointImage->load(tr("redpoint.png"));
    chessRedPointLabel = NULL;
   // chessRedPointLabel->setPixmap(QPixmap::fromImage(*chessRedPointImage));
    //chessRedPointLabel->hide();
    
    timeLabel = new QLabel(tr("时间:"),this);
    timeLabel->move(60,180);
    timeLabel->setFont(*font);
    timeLabel->show();
    timeLabel->setStyleSheet("color:white;");
    timer = new QTimer();
    timer->start(1000);
    hourTimeLabel = new QLabel("00",this);
    hourTimeLabel->setFont(*font);
    hourTimeLabel->move(timeLabel->pos().rx()+75,timeLabel->pos().ry());
    hourTimeLabel->setStyleSheet("color:white;");
    hourTimeSplitLabel = new QLabel(":",this);
    hourTimeSplitLabel->setFont(*font);
    hourTimeSplitLabel->move(hourTimeLabel->pos().rx()+30,hourTimeLabel->pos().ry());
    hourTimeSplitLabel->setStyleSheet("color:white;");
    minuteTimeLabel = new QLabel("00",this);
    minuteTimeLabel->move(hourTimeSplitLabel->pos().rx()+15,hourTimeLabel->pos().ry());
    minuteTimeLabel->setFont(*font);
    minuteTimeLabel->setStyleSheet("color:white;");
    minuteTimeSpliteLabel = new QLabel(":",this);
    minuteTimeSpliteLabel->move(minuteTimeLabel->pos().rx()+30,minuteTimeLabel->pos().ry());
    minuteTimeSpliteLabel->setFont(*font);
    minuteTimeSpliteLabel->setStyleSheet("color:white;");
    secondTimeLabel = new QLabel("00",this);
    secondTimeLabel->setFont(*font);
    secondTimeLabel->setStyleSheet("color:white;");
    secondTimeLabel->move(minuteTimeSpliteLabel->pos().rx()+10,minuteTimeSpliteLabel->pos().ry());
    regresButton = new QPushButton(tr("悔棋"),this);
    regresButton->setFont(*font);
    regresButton->setFlat(true);
    regresButton->move(930,180);
    regresButton->show();
    regresButton->setStyleSheet("color:yellow;");
    giveUpButton = new QPushButton(tr("认输"),this);
    giveUpButton->setFont(*font);
    giveUpButton->setFlat(true);
    giveUpButton->move(regresButton->width()+950,180);
    giveUpButton->show();
    giveUpButton->setStyleSheet("color:white;");
    replayButton = new QPushButton(tr("重玩"),this);
    replayButton->setFont(*font);
    replayButton->setFlat(true);
    replayButton->move(930,regresButton->height()+180+30);
    replayButton->show();
    replayButton->setStyleSheet("color:white;");
    exitButton = new QPushButton(tr("退出"),this);
    exitButton->setFont(*font);
    exitButton->setFlat(true);
    exitButton->move(regresButton->width()+950,regresButton->height()+180+30);
    exitButton->show();
    exitButton->setStyleSheet("color:red;");
    winLabel = new QLabel(tr("胜:"),this);
    winLabel->setFont(*font);
    winLabel->move(timeLabel->pos().rx(),timeLabel->pos().ry()+50);
    winLabel->setStyleSheet("color:yellow;");
    winLabel->show();
    lostLabel = new QLabel(tr("负:"),this);
    lostLabel->setFont(*font);
    lostLabel->move(winLabel->pos().rx() +65,winLabel->pos().ry());
    lostLabel->setStyleSheet("color:yellow;");

    drawLabel = new QLabel(tr("平:"),this);
    drawLabel->setFont(*font);
    drawLabel->move(lostLabel->pos().rx() + 65,lostLabel->pos().ry());
    drawLabel->setStyleSheet("color:yellow;");

    winNumberLabel = new QLabel("0",this);
    winNumberLabel->setFont(*font);
    winNumberLabel->move(winLabel->pos().rx()+45,winLabel->pos().ry());
    winNumberLabel->setStyleSheet("color:red;");

    lostNumberLabel = new QLabel(tr("0"),this);
    lostNumberLabel->setFont(*font);
    lostNumberLabel->move(lostLabel->pos().rx()+45,lostLabel->pos().ry());
    lostNumberLabel->setStyleSheet("color:red;");
    drawNumberLabel = new QLabel(tr("0"),this);
    drawNumberLabel->setFont(*font);
    drawNumberLabel->move(drawLabel->pos().rx()+45,drawLabel->pos().ry());
    drawNumberLabel->setStyleSheet("color:red;");
    QString gameEndStr = tr("游戏结束");
    setWindowIcon(QIcon("icon.ico"));
    setFixedSize(gamegroundLabel->width(),gamegroundLabel->height());
    //this->move(QApplication::desktop()->width()-this->width()/2,(QApplication::desktop()->height() - this->height())/2);
    winMessagebox = new QMessageBox(QMessageBox::NoIcon,gameEndStr,tr("你赢了，是否重来？"));
    winMessagebox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    winMessagebox->setButtonText(QMessageBox::Ok,tr("确定"));
    winMessagebox->setButtonText(QMessageBox::Cancel,tr("取消"));
    
    lostMessagebox = new QMessageBox(QMessageBox::NoIcon,gameEndStr,tr("你输了，是否重来?"));
    lostMessagebox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    lostMessagebox->setButtonText(QMessageBox::Ok,tr("确定"));
    lostMessagebox->setButtonText(QMessageBox::Cancel,tr("取消"));
    
    giveupMessagebox = new QMessageBox(QMessageBox::NoIcon,tr("认输"),tr("确定认输？"));
    giveupMessagebox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    giveupMessagebox->setButtonText(QMessageBox::Ok,tr("确定"));
    giveupMessagebox->setButtonText(QMessageBox::Cancel,tr("取消"));
    
    drawMessagebox = new QMessageBox(QMessageBox::NoIcon,gameEndStr,tr("平局,是否重来?"));
    drawMessagebox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    drawMessagebox->setButtonText(QMessageBox::Ok,tr("确定"));
    drawMessagebox->setButtonText(QMessageBox::Cancel,tr("取消"));
    
    replayMessagebox = new QMessageBox(QMessageBox::NoIcon,tr("重玩"),tr("确定重新开始吗？"));
    replayMessagebox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    replayMessagebox->setButtonText(QMessageBox::Ok,tr("确定"));
    replayMessagebox->setButtonText(QMessageBox::Cancel,tr("取消"));
    
    connectAll();
    winNumberInt = 0;
    lostNumberInt = 0;
    drawNumberInt = 0;
    historyVector.clear();
    //游戏数据初始化
    CleanChessBoard();//清空棋盘
    chessNumberInt = 0;
    whiteTurnBool = false;
    directXInt[0] = -1;
    directXInt[1] = -1;
    directXInt[2] = 0;
    directXInt[3] = 1;
    directXInt[4] = 1;
    directXInt[5] = 1;
    directXInt[6] = 0;
    directXInt[7] = -1;
    
    directYInt[0] = 0;
    directYInt[1] = 1;
    directYInt[2] = 1;
    directYInt[3] = 1;
    directYInt[4] = 0;
    directYInt[5] = -1;
    directYInt[6] = -1;
    directYInt[7] = -1;
  //  gameplay();        
    
    
    
    
}
void MainGame::connectAll()
{
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitButtonSlots()));
    connect(replayButton,SIGNAL(clicked()),this,SLOT(ReplayGameSlots()));
    connect(giveUpButton,SIGNAL(clicked()),this,SLOT(GiveUpGameSlots()));
    connect(regresButton,SIGNAL(clicked()),this,SLOT(regresSlots()));
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeOutSlots()));
    connect(showHideTimer,SIGNAL(timeout()),this,SLOT(ChessHideAndShowSlots()));
}
void MainGame::mousePressEvent(QMouseEvent*event)
{
    curposPoint = event->pos();
    QPoint b = chessBoardLabel->pos();
    curposPoint -=b;
    //24是棋盘边缘的宽度
    //32一个棋盘格子的大小
    if(curposPoint.rx()>=0&&curposPoint.rx()<chessBoardLabel->width())
    {
        if(curposPoint.ry()>0&&curposPoint.ry()<=chessBoardLabel->height())
        {
            nowSetPoint.rx() = (curposPoint.rx()-12)/32;
            if(curposPoint.rx()%32>=16)
            {
                nowSetPoint.rx() = nowSetPoint.rx()++;
                
            }
            nowSetPoint.ry() = (curposPoint.ry()-12)/32;
            if(curposPoint.rx()%32>=16)
            {
                nowSetPoint.ry() = nowSetPoint.ry()++;
            }
            if(gameplay())
            {
                GameAIMain();
            }
            
            
           
        }
        
    }
}
void MainGame::exitButtonSlots()
{
    this->close();
}
int MainGame::gameplay()
{
    if(chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] == 0)
    {
        if(whiteTurnBool)
        {
         //   GameAIMain();
            chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] = 1;
            ShowGame(); 
            if(GameIsEnd())
            {
                return false;
            }
            whiteTurnBool = !whiteTurnBool;
            historyVector.push_back(nowSetPoint);

            return true;
        }
        else {
            chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] = 2;

            ShowGame();
            if(GameIsEnd())
            {
                return false;
            }
            whiteTurnBool = !whiteTurnBool;
            historyVector.push_back(nowSetPoint);
            return true;
        }     
    }
 
    return false;
    
}
void MainGame::ShowGame()
{
    if(chessRedPointLabel != NULL)
    {
        delete chessRedPointLabel;
        chessRedPointLabel = NULL;
    }

    if(chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] == 1)
    {
        chessLabelArr[chessNumberInt] = new QLabel(this);

        chessLabelArr[chessNumberInt]->setPixmap(QPixmap::fromImage(*chessWhiteImage));
        chessLabelArr[chessNumberInt]->move(nowSetPoint.rx()*32+chessBoardLabel->pos().rx()+8,nowSetPoint.ry()*32+8+chessBoardLabel->pos().ry());
        chessLabelArr[chessNumberInt]->show();
         chessRedPointLabel = new QLabel(this);
        chessRedPointLabel->setPixmap(QPixmap::fromImage(*chessRedPointImage));
        chessRedPointLabel->move(nowSetPoint.rx()*32+chessBoardLabel->pos().rx()+20,nowSetPoint.ry()*32+18+chessBoardLabel->pos().ry());
        chessRedPointLabel->show();
        chessNumberInt++;
    }
    else {
        if(chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] == 2)
        {
            chessLabelArr[chessNumberInt] = new QLabel(this);
            chessLabelArr[chessNumberInt]->setPixmap(QPixmap::fromImage(*chessBlackImage));
            chessLabelArr[chessNumberInt]->move(nowSetPoint.rx()*32+chessBoardLabel->pos().rx()+8,nowSetPoint.ry()*32+8+chessBoardLabel->pos().ry());
            chessLabelArr[chessNumberInt]->show();
           // chessRedPointLabel->move(nowSetPoint.rx()*32+chessBoardLabel->pos().rx()+8,nowSetPoint.ry()*32+8+chessBoardLabel->pos().ry());
          //  chessRedPointLabel->show();
            chessNumberInt++;
        }
    }

}

bool MainGame::GameIsEnd()
{
                qDebug("history %d, num%d",historyVector.size(),chessNumberInt);
    int num[8] = {0,0,0,0,0,0,0,0};
    for(int i = 0;i<8;i++)
    {
        int tx = nowSetPoint.rx();
        int ty = nowSetPoint.ry();
        for(int j = 0;j<5;j++)
        {
            tx +=  directXInt[i];
            ty += directYInt[i];
            if(tx>=0&&tx<=18&&ty>=0&&ty<=18&&whiteTurnBool&&chessBoardIntArr[tx][ty] == 1)
            {
                num[i]++;
              
            }
            else {
                if(tx>=0&&tx<=18&&ty>=0&&ty<=18&&!whiteTurnBool&&chessBoardIntArr[tx][ty] == 2)
                {
                    num[i]++;
               
                }
                else {
                    break;
                }
                
            }
                
        }
    }
    for(int i = 0;i<4;i++)
    {
        if(num[i] + num[i+4]>=4)
        {

            int tmp = 0;
            if(chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] !=0)
            {  
                
                int tx_1 = nowSetPoint.rx();
                int ty_1= nowSetPoint.ry();
                int tx_2 = nowSetPoint.rx();
                int ty_2 = nowSetPoint.ry();
                for(int j = 0;j<5;j++)
                {
                    
                    tx_1 += directXInt[i];
                    ty_1 += directYInt[i];
                    tx_2 += directXInt[i+4];
                    ty_2 += directYInt[i+4];
                    if((chessBoardIntArr[tx_1][ty_1] == chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] || chessBoardIntArr[tx_2][ty_2] ==chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()]))
                    {
                        for(int k = 0;k<historyVector.size();k++)
                        {
                            if(historyVector[k].rx() == tx_1 && historyVector[k].ry() == ty_1)
                            {
                                hideshowintarr[tmp] = k;
                                tmp ++;
                                
                            }
                            if(historyVector[k].rx() == tx_2 && historyVector[k].ry() == ty_2)
                            {
                                hideshowintarr[tmp] = k;
                                tmp++;
                            }
                        }
                        showHideTimer->start(500);
                        
                    }
                }
              
                    
                    if(chessBoardIntArr[nowSetPoint.rx()][nowSetPoint.ry()] == 1)
                    {
                        if( lostMessagebox->exec() == QMessageBox::Ok)
                        {
                            showHideTimer->stop();
                            lostNumberInt++;
                            lostNumberLabel->setText(QString::number(lostNumberInt,10));
                            CleanChessBoard();
                            return true;
                        }
                        else
                        {
                            this->close();
                        }
                        
                    }
                    else {
                        if( winMessagebox->exec() == QMessageBox::Ok)
                        {
                            showHideTimer->stop();
                            winNumberInt++;
                            winNumberLabel->setText(QString::number(winNumberInt,10));
                            CleanChessBoard();
                            return true;
                        }
                        else {
                            this->close();
                        }
                    }
               
               
         
                
                
            }
               }
            
        }
    
    if(chessNumberInt == 361)
    {
        if(drawMessagebox->exec()  == QMessageBox::Ok)
        {
            drawNumberInt++;
            drawNumberLabel->setText(QString::number(drawNumberInt,10));
            showHideTimer->stop();
            CleanChessBoard();
            return true;
        }
        
    }
    return false;
}
void MainGame::GameAIMain()
{
    
    AI_CalcHowManyInLine();
    AI_SetPositionScore();
    AI_SetFinalPosition();
}
void MainGame::AI_CalcHowManyInLine()
{
    //把用来计分的数组清空
    for (int i = 0;i<19;i++)
        {
            for (int j = 0;j<19;j++)
            {
                scoreIntArr[i][j] = 0;
                for (int k = 0;k<8;k++)
                {
                    for (int t = 0;t<2;t++)
                    {
                        scoreDirectionIntArr[i][j][k][t] = 0;
                    }
                }
            }
        }
    int px = 0;
    int py = 0;
    int cnt_1;
    int cnt_2;
    for (int i = 0;i<19;i++)
        {
            for (int j = 0;j<19;j++)
            {
                if (chessBoardIntArr[i][j] == 0)
                {
                    for (int k = 0;k<8;k++)
                    {
                        cnt_1 = 0;
                        cnt_2 = 0;
                        px = i;
                        py = j;
                        for (int t = 0;t<5;t++)
                        {
                            
                            px += directXInt[k];
                            py += directYInt[k];
                           // if (t == 0&& chessBoardIntArr[px][py] == 2)
                         //   {
                          //      scoreDirectionIntArr[i][j][k][0] = 0;
                          //      break;
                          //  }
                            if (px>18||px<0||py>18||py<0)
                            {
                                break;
                            }
                            else
                            {
                                if (chessBoardIntArr[px][py] == 1)
                                {
                                    
                                    
                                        cnt_1++;
                                        scoreDirectionIntArr[i][j][k][0] = cnt_1;
                                    
                                    
                                }
                                else
                                {
                                   // if (chessBoardIntArr[px][py] == 2)
                                   // {
                                       break;
                                   // }
                                    
                                }
                            }
                            
                        }
                        ////////////////////
                        cnt_1 = 0;
                        cnt_2 = 0;
                        px = i;
                        py = j;
                        for (int t = 0;t<5;t++)
                        {
                            
                            px += directXInt[k];
                            py += directYInt[k];
                           // if (t == 0&& chessBoardIntArr[px][py] == 2)
                         //   {
                          //      scoreDirectionIntArr[i][j][k][0] = 0;
                          //      break;
                          //  }
                            if (px>18||px<0||py>18||py<0)
                            {
                                break;
                            }
                            else
                            {
                                if (chessBoardIntArr[px][py] == 2)
                                {
                                    
                                    
                                        cnt_2++;
                                        scoreDirectionIntArr[i][j][k][1] = cnt_2;
                                    
                                    
                                }
                                else
                                {
                                   // if (chessBoardIntArr[px][py] == 1)
                                   // {
                                        break;
                                  //  }
                                    
                                }
                            }
                            
                        }
                        //////////////////////
                    }
    
    
                }
                
            }
        }
}
void MainGame::AI_SetPositionScore()
{
    int score = 0;
	for (int i = 0;i<19;i++)
	{
		for (int j = 0;j<19;j++)
		{
			score = 0;
			if (chessBoardIntArr[i][j] == 0)
			{
				for (int k = 0;k<4;k++)
				{
					if (scoreDirectionIntArr[i][j][k][0] + scoreDirectionIntArr[i][j][k+4][0]>=4)
					{
                        
						score += 10000;
					}
					if (scoreDirectionIntArr[i][j][k][0] + scoreDirectionIntArr[i][j][k+4][0] == 3)
					{
						score += 1000;
					}
					if (scoreDirectionIntArr[i][j][k][0] + scoreDirectionIntArr[i][j][k+4][0] == 2)
					{
						score += 100;
					}
					if (scoreDirectionIntArr[i][j][k][0] + scoreDirectionIntArr[i][j][k+4][0] == 1)
					{
                  
						score += 10;
					}
                    if (scoreDirectionIntArr[i][j][k][1] + scoreDirectionIntArr[i][j][k+4][1]>=4)
					{
                        
						score += 10000;
					}
					if (scoreDirectionIntArr[i][j][k][1] + scoreDirectionIntArr[i][j][k+4][1] == 3)
					{
						score += 1000;
					}
					if (scoreDirectionIntArr[i][j][k][1] + scoreDirectionIntArr[i][j][k+4][1] == 2)
					{
						score += 100;
					}
					if (scoreDirectionIntArr[i][j][k][1] + scoreDirectionIntArr[i][j][k+4][1] == 1)
					{
                  
						score += 10;
					}
					if (score>0)
					{
						scoreIntArr[i][j] = score;
					}
					
				}
			}
		}
	}
}
void MainGame::AI_SetFinalPosition()
{
    int max = 0;
    int max_x =  0;//*x;
    int max_y =  0;//*y;
    for (int i = 0;i<19;i++)
    {
        for(int j = 0;j<19;j++)
        {
         
            if (scoreIntArr[i][j]>max)
            {
                 max = scoreIntArr[i][j];
                 max_x = i;
                 max_y = j;
             }
         }
     }
    nowSetPoint.setX(max_x);
    nowSetPoint.setY(max_y);
    gameplay();
}
void MainGame::AI_SetRandomPosition()
{
    
}
void MainGame::ReplayGameSlots()
{
    if(replayMessagebox->exec() == QMessageBox::Ok)
    {
        CleanChessBoard();
    }
    
    
}
void MainGame::CleanChessBoard()
{
    for(int i = 0;i<19;i++)
    {
        for(int j = 0;j<19;j++)
        {
            chessBoardIntArr[i][j] = 0;
        }
    }
    for(int i = 0;i < chessNumberInt;i++)
    {
        chessLabelArr[i]->hide();
        delete chessLabelArr[i];
        chessLabelArr[i] = 0;
    }
    chessNumberInt = 0;
    historyVector.clear();
    whiteTurnBool = false;
    time->restart();
    if(chessRedPointLabel != NULL)
    {
        delete chessRedPointLabel;
        chessRedPointLabel = NULL;
    }
}
void MainGame::GiveUpGameSlots()
{
    if(giveupMessagebox->exec() == QMessageBox::Ok)
    {
        CleanChessBoard();
        lostNumberInt++;
        lostNumberLabel->setText(QString::number(lostNumberInt,10));
    }
            
}
void MainGame::regresSlots()
{
    if(chessNumberInt>0)
    {
        for(int i = 0;i<2;i++)
        {
            delete chessLabelArr[chessNumberInt-1];
            chessLabelArr[chessNumberInt-1] = NULL;
            chessBoardIntArr[historyVector[chessNumberInt-1].rx()][historyVector[chessNumberInt-1].ry()] = 0;
            int x = historyVector[chessNumberInt-1].rx();
            int y = historyVector[chessNumberInt-1].ry();
            qDebug("%d,%d,= %d",x,y,chessBoardIntArr[x][y]);
            
            historyVector.remove(historyVector.size()-1);
            whiteTurnBool = !whiteTurnBool;
           
            chessNumberInt--;
            
                
            
        }
        
    }

    
    
}
void MainGame::TimeOutSlots()
{
    int time_second = time->elapsed()/1000;
    int hour = time_second /3600;
    int minute = (time_second-hour*60*60)/60;
    int second = time_second-hour*60*60-minute*60;
    if(hour /10 == 0)
    {
        hourTimeLabel->setText("0"+QString::number(hour,10));
    }
    else
    {
        hourTimeLabel->setText("0"+QString::number(hour,10));
    }
    if(minute / 10 == 0)
    {
        minuteTimeLabel->setText("0"+QString::number(minute,10));
    }
    else {
        minuteTimeLabel->setText(QString::number(minute,10));
    }
    if(second / 10 == 0)
    {
       secondTimeLabel->setText("0"+QString::number(second,10)); 
    }
    else {
        secondTimeLabel->setText(QString::number(second,10));
    }
    
}
void MainGame::ChessHideAndShowSlots()
{
    static int  times = 0;
    times++;
    if(times%2 != 0)
    {
        for(int i = 0;i<4;i++)
        {
            chessLabelArr[hideshowintarr[i]]->hide();
        }
        chessLabelArr[historyVector.size()]->hide();
    }
    
   if(times%2 == 0)
   {
       for(int i = 0;i<4;i++)
       {
           chessLabelArr[hideshowintarr[i]]->show();
       }
       chessLabelArr[historyVector.size()]->show();
   }
    
}
