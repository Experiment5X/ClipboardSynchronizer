#include "ClipboardSynchronizer.h"

ClipboardSynchronizer::ClipboardSynchronizer(QObject *parent) :
    QObject(parent)
{
     m_clipboard = QApplication::clipboard();
     connect(m_clipboard, SIGNAL(changed(QClipboard::Mode)), this, SLOT(onClipboardChanged(QClipboard::Mode)));

     m_socket = new QTcpSocket(this);
     connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
}

void ClipboardSynchronizer::onClipboardChanged(QClipboard::Mode mode)
{
    QString modeStr;
    switch (mode)
    {
        case QClipboard::Clipboard:
        {
            modeStr = "Clipboard: ";

            // if we can't write to the server then don't bother trying
            if (!m_socket->isWritable())
                break;

            ClipboardData data(m_clipboard->mimeData(mode));
            m_socket->write(data.rawData());

            qDebug() << "Wrote clipboard data to server.";

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

void ClipboardSynchronizer::onConnected()
{
    qDebug() << "Connected to " << m_hostName << " at port " << m_hostPort;
    emit connected();
}

quint16 ClipboardSynchronizer::hostPort() const
{
    return m_hostPort;
}

void ClipboardSynchronizer::setHostPort(const quint16 &hostPort)
{
    m_hostPort = hostPort;
}

void ClipboardSynchronizer::connectToHost()
{
    m_socket->connectToHost(m_hostName, m_hostPort);
}

QString ClipboardSynchronizer::hostName() const
{
    return m_hostName;
}

void ClipboardSynchronizer::setHostName(const QString &hostName)
{
    m_hostName = hostName;
}

