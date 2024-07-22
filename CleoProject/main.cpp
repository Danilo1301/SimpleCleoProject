#include <mod/amlmod.h>
#include <mod/logger.h>
#include <mod/config.h>

#include "utils.h"

#include "Log.h"
#include "CleoFunctions.h"

// ---------------------------------------

MYMODCFG(net.danilo1301.cleoProject, Cleo Project, 1.0.0, Danilo1301)

// ---------------------------------------

// CLEO 2.0.1.5
#include "cleo.h"
cleo_ifs_t* cleo = NULL;

// Script Commands
#include "IScriptCommands.h"
IScriptCommands* scriptCommands = NULL;

// Menu VSL
#include "menu/IMenuVSL.h"
IMenuVSL* menuVSL = NULL;

// ---------------------------------------

uintptr_t pGameLib = 0;
void* pGameHandle = NULL;

// ---------------------------------------

DECL_HOOK(void*, UpdateGameLogic, uintptr_t a1)
{
    Log::Level(eLogLevel::LOG_BOTH) << "UpdateGameLogic" << std::endl;
    
    CleoFunctions::Update(menuVSL->deltaTime);
    
    //your cleo code here:

    auto debug = menuVSL->debug;
    debug->m_Visible = true;

    if(CleoFunctions::PLAYER_DEFINED(0))
    {
        auto playerActor = CleoFunctions::GET_PLAYER_ACTOR(0);
        auto carHandle = CleoFunctions::ACTOR_USED_CAR(playerActor);

        debug->AddLine("carHandle: " + std::to_string(carHandle));
    }
    
    return UpdateGameLogic(a1);
}

//---------------------------------------------------------------------------------------------------

extern "C" void OnModPreLoad()
{
    char logPath[512];
	sprintf(logPath, "%s/cleoProject/", aml->GetConfigPath());
    Log::Open(logPath, "cleoProject");

    Log::Level(eLogLevel::LOG_BOTH) << "Preload()" << std::endl;
    Log::Level(eLogLevel::LOG_BOTH) << "AML headers: 1.0.3.1" << std::endl;

    logger->SetTag("CleoProject");

    logger->Info("Preload");

    Log::Level(eLogLevel::LOG_BOTH) << "Preload() END" << std::endl;
}

extern "C" void OnModLoad()
{
    Log::Level(eLogLevel::LOG_BOTH) << "Load()" << std::endl;

    cfg->Bind("Author", "", "About")->SetString("Danilo1301"); cfg->ClearLast();
    cfg->Bind("Discord", "", "About")->SetString("https://discord.gg/mkCDRf4zJA"); cfg->ClearLast();
    cfg->Bind("GitHub", "", "About")->SetString("https://github.com/Danilo1301/GTASA_libModPolicia"); cfg->ClearLast();
    cfg->Save();

    Log::Level(eLogLevel::LOG_BOTH) << "Loading interfaces..." << std::endl;

    LoadInterface(&cleo, "CLEO");
    LoadInterface(&scriptCommands, "ScriptCommands");
    LoadInterface(&menuVSL, "MenuVSL");

    Log::Level(eLogLevel::LOG_BOTH) << "Loading addresses..." << std::endl;
    
    pGameHandle = dlopen("libGTASA.so", RTLD_LAZY);
    uintptr_t gameAddr = (uintptr_t)(cleo->GetMainLibraryLoadAddress());

    Log::Level(eLogLevel::LOG_BOTH) << "Hooking..." << std::endl;

    HOOKPLT(UpdateGameLogic, gameAddr + 0x66FE58);

    Log::Level(eLogLevel::LOG_BOTH) << "Load() END" << std::endl;
}
