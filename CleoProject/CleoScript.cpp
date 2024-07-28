#include "CleoScript.h"

#include <string>

bool createdMenu = false;

void CleoScript::OnUpdate()
{
    auto playerActor = GET_PLAYER_ACTOR(0);

    auto carHandle = ACTOR_USED_CAR(playerActor);

    _debug->AddLine("car: " + std::to_string(carHandle));

    if(carHandle > 0 && !createdMenu)
    {
        createdMenu = true;
        CreateMenu();
    }
}

void CleoScript::OnLoad()
{
    _debug->visible = true;
    _debug->AddLine("OnLoad");
}

void CleoScript::OnFirstUpdate()
{
    _debug->AddLine("OnFirstUpdate");

    WAIT(3000, []() {
        _debug->AddLine("waited 3 seconds!");

        WAIT(3000, []() {
            _debug->AddLine("waited more 3 seconds!");
        });
    });
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