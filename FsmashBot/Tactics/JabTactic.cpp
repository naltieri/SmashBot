#include <typeinfo>

#include "JabTactic.h"
#include "../Chains/Jab.h"

JabTactic::JabTactic()
{
    m_chain = NULL;
}

JabTactic::~JabTactic()
{
    delete m_chain;
}

void JabTactic::DetermineChain()
{
    //If Jab is done, then Jab again!!!
    if(m_chain != NULL && m_chain->IsInterruptible())
    {
        delete m_chain;
        m_chain = NULL;
    }
    CreateChain(Jab);
    m_chain->PressButtons();
}
