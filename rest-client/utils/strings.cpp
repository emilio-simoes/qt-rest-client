#include "strings.h"

Strings::Strings(QObject* parent) : QObject(parent) {
}

Strings::~Strings() {
}

const QString Strings::Empty = "";

bool Strings::startsWithAny(const QString& source, const QStringList& matches) {
    foreach (QString value, matches) {
        if (source.startsWith(value)) {
            return true;
        }
    }

    return false;
}

bool Strings::endsWithAny(const QString& source, const QStringList& matches) {
    foreach (QString value, matches) {
        if (source.endsWith(value)) {
            return true;
        }
    }

    return false;
}

QString Strings::toBase64String(QString source) {
    QByteArray byteArray;
    byteArray.append(source);
    return byteArray.toBase64();
}

QString Strings::fromBase64String(QString source) {
    QByteArray byteArray;
    byteArray.append(source);
    return QByteArray::fromBase64(byteArray);
}
