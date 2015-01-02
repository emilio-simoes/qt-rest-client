#include "requesterror.h"

RequestError::RequestError(QObject* parent) : QObject(parent) {
}

RequestError::~RequestError() {
}

QString RequestError::errorMessage() const {
    return _errorMessage;
}

void RequestError::setErrorMessage(const QString& errorMessage) {
    _errorMessage = errorMessage;
    emit errorMessageChanged(errorMessage);
}

QString RequestError::result() const {
    return _result;
}

void RequestError::setResult(const QString& result) {
    _result = result;
    emit resultChanged(result);
}
