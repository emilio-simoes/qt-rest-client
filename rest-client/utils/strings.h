#ifndef STRINGS_H
#define STRINGS_H

#include <QObject>
#include <QStringList>
#include <QByteArray>

class Strings : public QObject {
        Q_OBJECT
    public:
        explicit Strings(QObject* parent = 0);
        ~Strings();

        static const QString Empty;

        static bool startsWithAny(const QString& source, const QStringList& matches);
        static bool endsWithAny(const QString& source, const QStringList& matches);

        static QString toBase64String(QString source);
        static QString fromBase64String(QString source);
};

#endif // STRINGS_H
