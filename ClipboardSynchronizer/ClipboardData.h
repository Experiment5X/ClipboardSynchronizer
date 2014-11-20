#ifndef CLIPBOARDDATA_H
#define CLIPBOARDDATA_H

#include <QMimeData>
#include <QByteArray>

#include "QMimeType.h"

class ClipboardData
{
public:
    ClipboardData(const QMimeData *mimeData);

    QByteArray rawData() const;

private:
    QByteArray m_rawData;
};

#endif // CLIPBOARDDATA_H
