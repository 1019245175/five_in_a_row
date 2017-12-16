#ifndef MAINGAME_H
#define MAINGAME_H
#include <QObject>
#include <QWidget>
#include<QLabel>
#include<QImage>
#include<QPushButton>
#include<QFont>
#include<QMouseEvent>
#include<QPoint>
#include<QMessageBox>
#include<QVector>
#include<QTime>
#include<QTimer>
class MainGame : public QWidget
{
    Q_OBJECT
public:
    explicit MainGame(QWidget *parent = 0);
private:
    
    QLabel *chessBoardLabel;
    QLabel *gamegroundLabel;
    QLabel *winLabel;
    QLabel *lostLabel;
    QLabel *drawLabel;
    QLabel *winNumberLabel;
    QLabel *lostNumberLabel;
    QLabel *drawNumberLabel;
    
    QImage *chessBoardImage;
    QImage *gamegroundImage;
    QLabel *chessLabelArr[361];
    QImage *chessWhiteImage;
    QImage *chessBlackImage;
    QImage *chessRedPointImage;
    QLabel *chessRedPointLabel;
    QPushButton *regresButton;
    QPushButton *giveUpButton;
    QPushButton *exitButton;
    QPushButton *replayButton;
    QLabel *timeLabel;
    QLabel *hourTimeLabel;
    QLabel *minuteTimeLabel;
    QLabel *secondTimeLabel;
    QLabel *hourTimeSplitLabel;
    QLabel *minuteTimeSpliteLabel;
    QFont *font;
    QPoint curposPoint;
    QMessageBox *winMessagebox;
    QMessageBox *lostMessagebox;
    QMessageBox *drawMessagebox;
    QMessageBox *giveupMessagebox;
    QMessageBox *replayMessagebox;
    
    QTime *time;
    QTimer *timer;
    QTimer *showHideTimer;
    int lostNumberInt;
    int winNumberInt;
    int drawNumberInt;
    void connectAll();
    int hideshowintarr[4];
    int  gameplay();   //游戏的核心逻辑
    void ShowGame();
    bool GameIsEnd();
    void GameAIMain();
    void AI_CalcHowManyInLine();
    void AI_SetPositionScore();
    void AI_SetFinalPosition();
    void AI_SetRandomPosition();
    void CleanChessBoard();
  
    //游戏数据
    QPoint nowSetPoint;
    int chessBoardIntArr[19][19];
    int chessNumberInt;
    bool whiteTurnBool;
    bool gameIsEndBool;
    bool whiteIsWinnerBool;
    int directXInt[8];
    int directYInt[8];
    int scoreIntArr[19][19];
    int scoreDirectionIntArr[19][19][8][2];
    QVector<QPoint> historyVector;
protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    
public slots:
    void exitButtonSlots();
    void ReplayGameSlots();
    void GiveUpGameSlots();
    void regresSlots();
    void TimeOutSlots();
      void ChessHideAndShowSlots();
};

#endif // MAINGAME_H
