#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>
#include <QJsonDocument>

class TestRunner : public QObject {
        Q_OBJECT

    public:
        explicit TestRunner(QObject* parent = 0);
        ~TestRunner();

    signals:
        void done();

    public slots:
        void handleGetDocument(QJsonDocument* document);
};

#endif // TESTRUNNER_H
