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
