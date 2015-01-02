#include "testrunner.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TestRunner::TestRunner(QObject* parent) : QObject(parent) {
}

TestRunner::~TestRunner() {
}

void TestRunner::handleGetDocument(QJsonDocument* document) {
    qDebug() << "Response: " << document->toJson();

    QJsonObject jsonRootObject = document->object();

    QJsonValue value = jsonRootObject.value("data");
    QJsonArray jsonArray = value.toArray();

    foreach (const QJsonValue& current, jsonArray) {
        qDebug() << "Name: " << current.toObject().value("name").toString();
        qDebug() << "Value: " << current.toObject().value("value").toString();
    }

    emit done();
}
