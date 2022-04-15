#include "backendconnection.h"

BackendConnection::BackendConnection(QObject *parent)
    : QObject{parent}
{

}

BackendConnection& BackendConnection::getInstance()
{
    static BackendConnection backend;
    return backend;
}


