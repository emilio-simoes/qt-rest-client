/*
 * Qt REST Client
 * Copyright (C) 2014 Emílio Simões
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
