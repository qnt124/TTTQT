#include "TTT.h"
#include "title.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qApp->setQuitOnLastWindowClosed(0);
    QApplication a(argc, argv);
    Title w;
    QObject::connect(&w, &Title::exited, &a, &QApplication::quit);
    w.show();
    return a.exec();
}
