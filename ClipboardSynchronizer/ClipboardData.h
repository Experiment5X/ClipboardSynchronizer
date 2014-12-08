#ifndef CLIPBOARDDATA_H
#define CLIPBOARDDATA_H

#include <QMimeData>
#include <QByteArray>
#include <QDebug>

#include "QMimeType.h"

QByteArray MimeDataToRawData(const QMimeData *mimeData);
QMimeData* RawDataToMimeData(const QByteArray &byteArray);

#endif // CLIPBOARDDATA_H
