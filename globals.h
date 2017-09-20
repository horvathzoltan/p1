#ifndef GLOBALS_H
#define GLOBALS_H

#include "masterdata.h"
#include "zitemeditorfactory.h"

#define zforeach(var, container) for(auto var = (container).begin(); var != (container).end(); ++var)

extern MasterData md;
extern zItemEditorFactory zif;

#endif // GLOBALS_H
