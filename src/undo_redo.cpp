#include "undo_redo.h"

UndoRedo::UndoRedo()
{
}

UndoRedo::~UndoRedo(void)
{
}

void UndoRedo::doSomething(QList<Layer *> *layers)
{
    Action *action = new Action(layers);
    undoActions.append(action);
    clearRedo();
}

void UndoRedo::clearRedo(void)
{
    for (int i = 0; i < redoActions.size(); i++)
    {
        delete redoActions.at(i);
    }

    redoActions.clear();
}

void UndoRedo::clearUndo(void)
{
    for (int i = 0; i < undoActions.size(); i++)
    {
        delete undoActions.at(i);
    }

    undoActions.clear();
}

bool UndoRedo::canUndo(void)
{
    if (undoActions.size() <= 0)
    {
        return false;
    }
    return true;
}

bool UndoRedo::canRedo(void)
{
    if (redoActions.size() <= 0)
    {
        return false;
    }
    return true;
}

void UndoRedo::redo(void)
{
    if (redoActions.size() <= 0)
    {
        return;
    }

    Action *action = redoActions.last();
    action->redo();
    redoActions.removeLast();
    undoActions.append(action);
}

void UndoRedo::undo(void)
{
    if (undoActions.size() <= 0)
    {
        return;
    }

    Action *action = undoActions.last();
    action->undo();
    undoActions.removeLast();
    redoActions.append(action);
}
