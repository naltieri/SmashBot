#include "KillOpponent.h"
#include "../Strategies/FsmashStrategy.h"


KillOpponent::KillOpponent()
{
    m_strategy = NULL;
}

KillOpponent::~KillOpponent()
{
    delete m_strategy;
}

void KillOpponent::Strategize()
{

    //Do Fsmash Strategy
    CreateStrategy(FsmashStrategy);
    m_strategy->DetermineTactic();

}
