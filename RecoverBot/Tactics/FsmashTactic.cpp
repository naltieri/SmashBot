#include <typeinfo>

#include "FsmashTactic.h"
#include "../Chains/Fsmash.h"

FsmashTactic::FsmashTactic()
{
    m_chain = NULL;
}

FsmashTactic::~FsmashTactic()
{
    delete m_chain;
}

void FsmashTactic::DetermineChain()
{
    //If Fsmash is done, then Fsmash again!!!
    if(m_chain != NULL && m_chain->IsInterruptible())
    {
        delete m_chain;
        m_chain = NULL;
    }
    CreateChain(Fsmash);
    m_chain->PressButtons();
}
