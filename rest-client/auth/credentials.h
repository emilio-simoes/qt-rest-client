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
