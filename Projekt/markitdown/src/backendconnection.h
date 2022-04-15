#ifndef BACKENDCONNECTION_H
#define BACKENDCONNECTION_H

#include <QObject>
#include <QtQml/qqml.h>

class BackendConnection : public QObject
{
    Q_OBJECT
    explicit BackendConnection(QObject *parent = nullptr);
public:
    static BackendConnection& getInstance();

signals:

};

#endif // BACKENDCONNECTION_H
