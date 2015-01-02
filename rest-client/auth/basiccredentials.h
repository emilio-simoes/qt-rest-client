#ifndef BASICCREDENTIALS_H
#define BASICCREDENTIALS_H

#include <QObject>

#include "credentials.h"
#include "utils/strings.h"

class BasicCredentials : public Credentials {
        Q_OBJECT

    public:
        explicit BasicCredentials(QObject* parent = 0);
        ~BasicCredentials();

        QString* asBase64() const;
};

#endif // BASICCREDENTIALS_H
