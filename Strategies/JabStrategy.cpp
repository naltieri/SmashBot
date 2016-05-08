#include <cmath>
#include <math.h>

#include "JabStrategy.h"
#include "../Util/Constants.h"
#include "../Tactics/JabTactic.h"

JabStrategy::JabStrategy()
{
    m_tactic = NULL;
    m_attackFrame = 0;
    m_lastAction = (ACTION)m_state->m_memory->player_one_action;
    m_shieldedAttack = false;
    m_actionChanged = true;
    m_chargingLastFrame = false;
    m_lastActionCount = 0;
}

JabStrategy::~JabStrategy()
{
    delete m_tactic;
}

void JabStrategy::DetermineTactic()
{
    //If we're not in a state to interupt, just continue with what we've got going
    if((m_tactic != NULL) && (!m_tactic->IsInterruptible()))
    {
        m_tactic->DetermineChain();
        return;
    }

    //Else: JAB!
    CreateTactic(JabTactic);
    m_tactic->DetermineChain();
    
}
