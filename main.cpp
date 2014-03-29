#include "screenshoot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenShoot w;
    w.show();

    return a.exec();
}
