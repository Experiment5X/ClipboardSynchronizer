#ifndef CLIPBOARDSYNCHRONIZER_H
#define CLIPBOARDSYNCHRONIZER_H

#include <QObject>
#include <QClipboard>
#include <QDebug>
#include <QApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "ClipboardData.h"

class ClipboardSynchronizer : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardSynchronizer(QObject *parent = 0);

    QString hostName() const;
    void setHostName(const QString &hostName);

    quint16 hostPort() const;
    void setHostPort(const quint16 &hostPort);

    void connectToHost();

public slots:
    void onClipboardChanged(QClipboard::Mode mode);
    void onConnected();

signals:
    void connected();

private:
    QClipboard *m_clipboard;
    QTcpServer *m_server;
    QTcpSocket *m_socket;

    QString m_hostName;
    quint16 m_hostPort;
};

#endif // CLIPBOARDSYNCHRONIZER_H
