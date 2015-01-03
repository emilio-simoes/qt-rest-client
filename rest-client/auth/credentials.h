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
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <QObject>

class Credentials : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString* username READ username WRITE setUsername NOTIFY usernameChanged)
        Q_PROPERTY(QString* password READ password WRITE setPassword NOTIFY passwordChanged)

    public:
        explicit Credentials(QObject* parent = 0);
        virtual ~Credentials();

        QString* password() const;
        QString* username() const;

    public slots:
        void setUsername(QString* username);
        void setPassword(QString* password);

        virtual QString* asBase64() const = 0;

    signals:
        void usernameChanged(QString* username);
        void passwordChanged(QString* password);

    private:
        QString* _password;
        QString* _username;
};

#endif // CREDENTIALS_H
