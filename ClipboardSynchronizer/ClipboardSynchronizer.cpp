#include "ClipboardSynchronizer.h"

ClipboardSynchronizer::ClipboardSynchronizer(QObject *parent) :
    m_port(5544), QObject(parent)
{
     m_clipboard = QApplication::clipboard();
     connect(m_clipboard, SIGNAL(changed(QClipboard::Mode)), this, SLOT(onClipboardChanged(QClipboard::Mode)));

     QTcpSocket *serverSocket = new QTcpSocket(this);
     connect(serverSocket, SIGNAL(connected()), this, SLOT(onConnected()));
     m_connectedSockets.push_back(serverSocket);

     m_server = new QTcpServer(this);
     connect(m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

     if (!m_server->listen(QHostAddress::Any, m_port))
         qDebug() << "Server couldn't start";
}

void ClipboardSynchronizer::onClipboardChanged(QClipboard::Mode mode)
{
    if (m_justChangedClipboard)
    {
        m_justChangedClipboard = false;
        return;
    }

    QString modeStr;
    switch (mode)
    {
        case QClipboard::Clipboard:
        {
            modeStr = "Clipboard: ";

            QByteArray rawData = MimeDataToRawData(m_clipboard->mimeData(mode));
            sendClipboardData(rawData);
            break;
        }
        case QClipboard::FindBuffer:
            modeStr = "Find Buffer: ";
            break;
        case QClipboard::Selection:
            modeStr = "Selection: ";
            break;
    }

    qDebug() << modeStr << m_clipboard->text(mode);
}

void ClipboardSynchronizer::onNewConnection()
{
    QTcpSocket *socket = m_server->nextPendingConnection();
    m_connectedSockets.append(socket);

    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void ClipboardSynchronizer::onReadyRead()
{
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());

    // if the sender is not of type QTcpSocket, then we can't send any data to it
    if (socket == nullptr)
        return;

    QByteArray clipboardData = socket->readAll();

    m_justChangedClipboard = true;
    m_clipboard->setMimeData(RawDataToMimeData(clipboardData));

    qDebug() << "Received clipboard data from" << socket->localAddress();
}

void ClipboardSynchronizer::onConnected()
{
    qDebug() << "Connected to" << m_hostName << "at port" << m_port;
    emit connected();
}

quint16 ClipboardSynchronizer::port() const
{
    return m_port;
}

void ClipboardSynchronizer::connectToHost()
{
    m_connectedSockets.at(0)->connectToHost(m_hostName, m_port);
}

void ClipboardSynchronizer::sendClipboardData(QByteArray &data)
{
    // try and send data to all the listeners
    for (QTcpSocket *socket : m_connectedSockets)
    {
        if (socket->isWritable())
            socket->write(data);
        else
            qDebug() << "Couldn't write data to" << socket->localAddress().toIPv4Address();
    }
}

QString ClipboardSynchronizer::hostName() const
{
    return m_hostName;
}

void ClipboardSynchronizer::setHostName(const QString &hostName)
{
    m_hostName = hostName;
}

