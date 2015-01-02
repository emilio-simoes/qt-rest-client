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
