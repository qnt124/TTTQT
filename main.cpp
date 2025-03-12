#include "TTT.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TTT w;
    w.show();
    return a.exec();
}
