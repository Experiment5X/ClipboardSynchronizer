#include "ClipboardSynchronizer.h"

ClipboardSynchronizer::ClipboardSynchronizer(QObject *parent) :
    QObject(parent)
{
     m_clipboard = QApplication::clipboard();
     connect(m_clipboard, SIGNAL(changed(QClipboard::Mode)), this, SLOT(onClipboardChanged(QClipboard::Mode)));
}

void ClipboardSynchronizer::onClipboardChanged(QClipboard::Mode mode)
{
    QString modeStr;
    switch (mode)
    {
        case QClipboard::Clipboard:
            modeStr = "Clipboard: ";
            break;
        case QClipboard::FindBuffer:
            modeStr = "Find Buffer: ";
            break;
        case QClipboard::Selection:
            modeStr = "Selection: ";
            break;
    }

    qDebug() << modeStr << m_clipboard->text(mode);
}
