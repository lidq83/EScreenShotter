#ifndef _ACTION_H_
#define _ACTION_H_

#include <QList>
#include "layer.h"

class Action
{
public:
    Action(QList<Layer *> *layers);
    virtual ~Action();

    virtual void redo(void);
    virtual void undo(void);

private:
    QList<Layer *> *layers;
    Layer *layer;
};

#endif