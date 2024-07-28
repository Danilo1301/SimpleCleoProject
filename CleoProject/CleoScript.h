#pragma once

#include "CleoOpcodes.h"
#include "Log.h"

#include "menu/IMenuVSL.h"
extern IMenuVSL* menuVSL;

class CleoScript {
public:
    static void OnLoad();
    static void OnFirstUpdate();
    static void OnUpdate();

    static void CreateMenu();
};