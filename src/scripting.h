#pragma once

#include "cstate.h"

void InitialiseScripting(CState *state);
void ScriptingConfigure(CState *state);
void ScriptingDestroy(CState *state);

void ScriptingPushCState(CState *state);
