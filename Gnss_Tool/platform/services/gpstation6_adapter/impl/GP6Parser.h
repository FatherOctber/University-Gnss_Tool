#ifndef GP6PARSER_H
#define GP6PARSER_H
#include <QByteArray>
#include "Context.h"

using namespace gnss;


class GP6Parser
{
public:
     GP6Parser();
    ~GP6Parser();

public:
    void parse(QByteArray data, Context* workingContext);

private:
    void scanNovatelMessage(Context *ctx, int type);
};

#endif
