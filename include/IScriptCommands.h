#pragma once

#include "SimpleGTA.h"

#include <iostream>
#include <cstdint>

#define DEFOPCODE(__opcode, __name, __args) const SCRIPT_COMMAND scm_##__name = { 0x##__opcode, #__args }

#define MAX_SCRIPT_VARS 16

struct SCRIPT_COMMAND
{
    uint16_t  opCode;
    char      params[MAX_SCRIPT_VARS];
};

class IScriptCommands {
public:

    //1.0.0

    /** Calls a script opcode (mini-cleo).
    *  A serious crash may appear if you are using this function and one of the arguments is a pointer (&scmHandle).
    *  Make sure, that the variable you need pointer for (scmHandle1 in this case)
    *  is defined OUTSIDE of the function, otherwise the stack corruption and crash will be your best friends!
    *  For more info, check SAUtils's sautils.cpp, line #1462, you will see.
    *
    *  \param pScriptCommand A pointer to SCRIPT_COMMAND struct var
    *  \param ... All arguments
    *  \return A possibly returned value
    */
    virtual int ScriptCommand(const SCRIPT_COMMAND *pScriptCommand, ...) = 0;
};