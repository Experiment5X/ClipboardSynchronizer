#include "ClipboardData.h"

QByteArray MimeDataToRawData(const QMimeData *mimeData)
{
    static const QMimeType types[] = { QMimeType::TEXT, QMimeType::HTML, QMimeType::URLS, QMimeType::IMAGE, QMimeType::COLOR };

    // figure out which type of data is on the clipboard
    QMimeType type = QMimeType::NONE;
    for (int i = 0; i < (int)(sizeof(types) / sizeof(QMimeType)); i++)
    {
        if (mimeData->hasFormat(QMimeTypeFormat(types[i])))
        {
            type = types[i];
            break;
        }
    }

    // if nothing is on the clipboard then there is no data to store
    if (type == QMimeType::NONE)
        return QByteArray();

    // allocate enough memory for the data type indicator byte at the beginning and for the data itself
    QByteArray rawData;
    rawData.reserve(mimeData->data(QMimeTypeFormat(type)).size() + 1);

    // put the data into a raw buffer
    rawData[0] = (int)type;
    rawData.replace(1, rawData.length() - 1, mimeData->data(QMimeTypeFormat(type)));

    return rawData;
}

QMimeData* RawDataToMimeData(const QByteArray &byteArray)
{
    QMimeData *toReturn = new QMimeData;

    if (byteArray.length() == 0)
        return toReturn;

    // get the type and verify it
    int type = byteArray.at(0);
    if (type < 0 || type > 4)
    {
        qDebug() << "Invalid QMimeType.";
        return toReturn;
    }

    toReturn->setData(QMimeTypeFormat((QMimeType)type), byteArray.mid(1));
    return toReturn;
}
