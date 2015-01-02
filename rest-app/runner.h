#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QCoreApplication>

class Runner : public QObject {
        Q_OBJECT
    public:
        explicit Runner(QObject* parent = 0);
        ~Runner();

    public slots:
        void run();
};

#endif // RUNNER_H
