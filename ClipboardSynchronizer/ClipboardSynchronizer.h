#ifndef CLIPBOARDSYNCHRONIZER_H
#define CLIPBOARDSYNCHRONIZER_H

#include <QObject>
#include <QClipboard>
#include <QDebug>
#include <QApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "ClipboardData.h"

class ClipboardSynchronizer : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardSynchronizer(QObject *parent = 0);

    QString hostName() const;
    void setHostName(const QString &hostName);

    quint16 port() const;

    void connectToHost();

    void sendClipboardData(QByteArray &data);

public slots:
    void onClipboardChanged(QClipboard::Mode mode);
    void onConnected();
    void onNewConnection();
    void onReadyRead();

signals:
    void connected();

private:
    QClipboard *m_clipboard;
    QTcpServer *m_server;

    QString m_hostName;
    quint16 m_port;

    bool m_justChangedClipboard = false;

    QList<QTcpSocket*> m_connectedSockets;
};

#endif // CLIPBOARDSYNCHRONIZER_H
