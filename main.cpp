#include "five_in_a_row.h"
#include <QApplication>
#include"startgame.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartGame startgame;
    startgame.show();
    
   // five_in_a_row w;
   // w.show();
    
    return a.exec();
}
