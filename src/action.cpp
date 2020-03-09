#include "action.h"

Action::Action(QList<Layer *> *layers)
    : layers(layers),
      layer(nullptr)
{
}

Action::~Action(void)
{
}

void Action::redo(void)
{
    if (layers == nullptr)
    {
        return;
    }

    if (layer == nullptr)
    {
        return;
    }

    layers->append(layer);
    layer = nullptr;
}

void Action::undo(void)
{
    if (layers == nullptr)
    {
        return;
    }

    if (layers->size() <= 0)
    {
        return;
    }

    layer = layers->last();
    layers->removeLast();
}