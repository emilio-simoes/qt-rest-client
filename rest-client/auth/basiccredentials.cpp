#include "basiccredentials.h"

BasicCredentials::BasicCredentials(QObject* parent) : Credentials(parent) {
}

BasicCredentials::~BasicCredentials() {
}

QString* BasicCredentials::asBase64() const {
    QString baseString = *username() + QString(":") + *password();
    baseString = Strings::toBase64String(baseString);
    return new QString(baseString);
}
