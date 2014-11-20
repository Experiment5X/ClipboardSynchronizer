#include "ClipboardData.h"

ClipboardData::ClipboardData(const QMimeData *mimeData)
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
        return;

    // allocate enough memory for the data type indicator byte at the beginning and for the data itself
    m_rawData.reserve(mimeData->data(QMimeTypeFormat(type)).size() + 1);

    // put the data into a raw buffer
    m_rawData[0] = (int)type;
    m_rawData.replace(1, m_rawData.length() - 1, mimeData->data(QMimeTypeFormat(type)));
}

QByteArray ClipboardData::rawData() const
{
    return m_rawData;
}
