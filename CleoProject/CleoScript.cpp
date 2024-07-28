#include "CleoScript.h"

#include <string>

bool createdMenu = false;

void CleoScript::OnLoad()
{
    _debug->visible = true;
    _debug->AddLine("SimpleCleoProject loaded!");
}

void CleoScript::OnFirstUpdate()
{
    _debug->AddLine("OnFirstUpdate");

    _debug->AddLine("waiting 3 seconds...");
    WAIT(3000, []() {
        _debug->AddLine("waited 3 seconds!");

        WAIT(3000, []() {
            _debug->AddLine("waited more 3 seconds!");
        });
    });

    RunSpecialFunctions();
}

void CleoScript::OnUpdate()
{
    auto playerActor = GET_PLAYER_ACTOR(0);

    auto carHandle = ACTOR_USED_CAR(playerActor);

    if(carHandle > 0 && !createdMenu)
    {
        createdMenu = true;

        _debug->AddLine("car: " + std::to_string(carHandle));

        CreateMenu();
    }
}

void CleoScript::CreateMenu()
{
    auto window = menuVSL->AddWindow();
    window->m_Title = "Title";

    auto close = window->AddButton("close", CRGBA(255, 255, 255));
    close->onClick = [window]() {
        window->SetToBeRemoved();
    };
}

int testInt = 0;
int testInt2 = 0;

void CleoScript::RunSpecialFunctions()
{
    scriptCommands->AddCondition([](std::function<void()> cancel){
        // executed every game update

        testInt++;
        
        if(testInt == 10)
        {
            // return true to complete condition
            return true;
        }

        return false;
    }, [](){
        _debug->AddLine("condition 1 completed!");
    }, [](){
        _debug->AddLine("condition 1 cancelled");
    });

    scriptCommands->AddCondition([](std::function<void()> cancel){
        // executed every game update

        testInt2++;
        
        if(testInt2 == 15)
        {
            // call cancel() to cancel condition
            cancel();
            return false;
        }

        return false;
    }, [](){
        _debug->AddLine("condition 2 completed!");
    }, [](){
        _debug->AddLine("condition 2 cancelled");
    });
}