#ifndef _UNDO_REDO_H_
#define _UNDO_REDO_H_

#include <QList>
#include "action.h"

class UndoRedo
{
public:
    UndoRedo();
    virtual ~UndoRedo();

    virtual void doSomething(QList<Layer *> *layers);

    virtual void clearRedo(void);
    virtual void clearUndo(void);

    virtual bool canUndo(void);
    virtual bool canRedo(void);

    virtual void redo(void);
    virtual void undo(void);

private:
    QList<Action *> undoActions;
    QList<Action *> redoActions;
};

#endif