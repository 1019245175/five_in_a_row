#ifndef STARTGAME_H
#define STARTGAME_H

#include <QMainWindow>
#include <QObject>
#include<QLabel>
#include<QPushButton>
#include<QFont>
class StartGame : public QWidget
{
    Q_OBJECT
public:
    explicit StartGame(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    QLabel *GameGroundPictureLabel;
    QImage *GameGroundPictureImage;
    QPushButton *StartGameButton;
    QPushButton *ExitGameButton;
    QPushButton *AboutGameButton;
    QFont *font;
    void connectAll();
    
    
public slots:
    void StartGameSlots();
    void ExitGameSlots();
    void AboutSlots();
    
};

#endif // STARTGAME_H
