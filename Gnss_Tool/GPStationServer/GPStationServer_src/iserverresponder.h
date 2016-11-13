#ifndef ISERVERRESPONDER_H
#define ISERVERRESPONDER_H
#include <QByteArray>

class IServerResponder
{
public:
    virtual QByteArray response() = 0;
};

#endif // ISERVERRESPONDER_H
