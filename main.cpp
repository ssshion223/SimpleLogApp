#include "sidelogwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SideLogWidget w;
    w.show();
    return QCoreApplication::exec();
}
