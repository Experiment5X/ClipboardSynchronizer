#ifndef QMIMETYPE_H
#define QMIMETYPE_H

#include <QString>

enum class QMimeType
{
    NONE = 0,
    TEXT = 1,
    HTML = 2,
    URLS = 3,
    IMAGE = 4,
    COLOR = 5
};

QString QMimeTypeFormat(QMimeType type);

#endif // QMIMETYPE_H
