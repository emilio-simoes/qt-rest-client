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
#include "credentials.h"

Credentials::Credentials(QObject* parent) : QObject(parent) {
}

Credentials::~Credentials() {
    if (_username) {
        delete _username;
        _username = NULL;
    }
    if (_password) {
        delete _password;
        _password = NULL;
    }
}

QString* Credentials::password() const {
    return _password;
}

QString* Credentials::username() const {
    return _username;
}

void Credentials::setPassword(QString* password) {
    if (_password == password)
        return;

    _password = password;
    emit passwordChanged(password);
}

void Credentials::setUsername(QString* username) {
    if (_username == username)
        return;

    _username = username;
    emit usernameChanged(username);
}
