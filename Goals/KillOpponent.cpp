#include "KillOpponent.h"
#include "../Strategies/JabStrategy.h"


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

    //Do Jab Strategy
    CreateStrategy(JabStrategy);
    m_strategy->DetermineTactic();

}
