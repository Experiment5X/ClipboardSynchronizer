#ifndef CLIPBOARDSYNCHRONIZER_H
#define CLIPBOARDSYNCHRONIZER_H

#include <QObject>
#include <QClipboard>
#include <QDebug>
#include <QApplication>

class ClipboardSynchronizer : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardSynchronizer(QObject *parent = 0);

public slots:
    void onClipboardChanged(QClipboard::Mode mode);

private:
    QClipboard *m_clipboard;
};

#endif // CLIPBOARDSYNCHRONIZER_H
