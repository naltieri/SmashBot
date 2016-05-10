#include <cmath>
#include <math.h>

#include "FsmashStrategy.h"
#include "../Util/Constants.h"
#include "../Tactics/FsmashTactic.h"

FsmashStrategy::FsmashStrategy()
{
    m_tactic = NULL;
    m_attackFrame = 0;
    m_lastAction = (ACTION)m_state->m_memory->player_one_action;
    m_shieldedAttack = false;
    m_actionChanged = true;
    m_chargingLastFrame = false;
    m_lastActionCount = 0;
}

FsmashStrategy::~FsmashStrategy()
{
    delete m_tactic;
}

void FsmashStrategy::DetermineTactic()
{
    //If we're not in a state to interupt, just continue with what we've got going
    if((m_tactic != NULL) && (!m_tactic->IsInterruptible()))
    {
        m_tactic->DetermineChain();
        return;
    }

    //Else: Fsmash!
    CreateTactic(FsmashTactic);
    m_tactic->DetermineChain();
    
}
