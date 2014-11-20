#include <QApplication>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

#include "ClipboardSynchronizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Waiting for clipboard changes...";

    ClipboardSynchronizer sync;
    sync.setHostName("localhost");
    sync.setHostPort(22);
    sync.connectToHost();

    return a.exec();
}
