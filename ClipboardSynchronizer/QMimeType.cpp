#include "QMimeType.h"

QString QMimeTypeFormat(QMimeType type)
{
    static const QString formats[] =
    {
        "",
        "text/plain",
        "text/html",
        "text/uri-list",
        "image/ *",
        "application/x-color"
    };

    return formats[(int)type];
}
