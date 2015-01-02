#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QTimer>
#include <QObject>

#include "restclient.h"
#include "requesterror.h"
#include "resturlbuilder.h"
#include "runner.h"
#include "testrunner.h"

void buildUrl();
void getColors();
TestRunner* getColorsAsync(RestClient& client);

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    buildUrl();
    getColors();

    RestClient client;
    Runner r;
    TestRunner* runner = getColorsAsync(client);
    QObject::connect(runner, SIGNAL(done()), &r, SLOT(run()));

    return a.exec();
}

void buildUrl() {
    //"http://localhost:5000"
    RestUrlBuilder builder;

    builder.appendHost("localhost");
    builder.appendPort(5000);

    builder.appendPath("colors");
    qDebug() << builder.urlString();

    builder.appendPath("/red");
    qDebug() << builder.urlString();
}

void getColors() {
    qDebug() << "########## GET REQUEST TEST ##########";
    qDebug() << "########## GET LIST ##########";

    RestClient client;
    QJsonDocument* jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/colors")));

    qDebug() << "Response: " << jsonResponse->toJson();

    QJsonObject jsonRootObject = jsonResponse->object();

    QJsonValue value = jsonRootObject.value("data");
    QJsonArray jsonArray = value.toArray();

    foreach (const QJsonValue& current, jsonArray) {
        qDebug() << "Name: " << current.toObject().value("name").toString();
        qDebug() << "Value: " << current.toObject().value("value").toString();
    }

    delete jsonResponse;

    qDebug() << "########## GET SINGLE ELEMENT ##########";

    jsonResponse = client.getJson(QUrl(QString("http://localhost:5000/api/colors/red")));

    qDebug() << "Response: " << jsonResponse->toJson();

    QJsonObject jsonObject = jsonResponse->object();

    qDebug() << "Name: " << jsonObject.value("name").toString();
    qDebug() << "Value: " << jsonObject.value("value").toString();

    delete jsonResponse;
}

TestRunner* getColorsAsync(RestClient& client) {
    TestRunner* runner = new TestRunner();

    QObject::connect(&client, SIGNAL(onJsonRequestExecuted(QJsonDocument*)), runner,
                     SLOT(handleGetDocument(QJsonDocument*)));
    client.getResource(QUrl(QString("http://localhost:5000/api/colors")));

    return runner;
}
