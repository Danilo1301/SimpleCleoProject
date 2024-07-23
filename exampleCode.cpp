void OnFirstUpdate()
{
    debug->AddLine("OnFirstUpdate");

    debug->AddLine("waiting 5 seconds");
    WAIT(5000, []() {
        debug->AddLine("finished waiting 5 seconds");
    });

    scriptCommands->AddCondition([](std::function<void()> cancel)
    {
        auto playerActor = GET_PLAYER_ACTOR(0);
        auto carHandle = ACTOR_USED_CAR(playerActor);
        
        if(carHandle > 0)
        {
            auto modelId = GET_CAR_MODEL(carHandle);

            if(modelId == 522)
            {
                // return true to complete the condition
                return true;
            }

            // call the 'cancel' function to cancell the condition
            cancel();
            return false;
        }

        return false;
    }, []() {
        //on complete:

        debug->AddLine("condition completed");
        debug->AddLine("you entered on a NRG-500");
    }, []() {
        //on cancel:

        debug->AddLine("condition cancelled");
        debug->AddLine("you entered on a different vehicle");
    });
}

void OnUpdate()
{
    if(PLAYER_DEFINED(0))
    {
        auto playerActor = GET_PLAYER_ACTOR(0);
        auto carHandle = ACTOR_USED_CAR(playerActor);

        if(carHandle > 0)
        {
            debug->AddLine("carHandle: " + std::to_string(carHandle));
        }
    }
}

void OnLoad()
{
    scriptCommands->AddOnFirstUpdateGame(OnFirstUpdate);
    scriptCommands->AddOnUpdateGame(OnUpdate);

    debug->m_Visible = true;
}