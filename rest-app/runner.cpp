#include <QDebug>

#include "runner.h"

Runner::Runner(QObject* parent) : QObject(parent) {
}

Runner::~Runner() {
}

void Runner::run() {
    qDebug() << "Calling quit :P";
    QCoreApplication::exit(0);
}
