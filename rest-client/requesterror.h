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
#ifndef REQUESTERROR_H
#define REQUESTERROR_H

#include <QObject>

class RequestError : public QObject {
        Q_OBJECT
        Q_PROPERTY(QString errorMessage READ errorMessage WRITE setErrorMessage NOTIFY errorMessageChanged)
        Q_PROPERTY(QString result READ result WRITE setResult NOTIFY resultChanged)

    public:
        explicit RequestError(QObject* parent = 0);
        ~RequestError();

        QString errorMessage() const;
        QString result() const;

    public slots:
        void setErrorMessage(const QString& errorMessage);
        void setResult(const QString& result);

    signals:
        void errorMessageChanged(QString errorMessage);
        void resultChanged(QString result);

    private:
        QString _errorMessage;
        QString _result;
};

#endif // REQUESTERROR_H
