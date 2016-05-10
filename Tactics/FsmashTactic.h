#ifndef FSMASHTACTIC_H
#define FSMASHTACTIC_H

#include "Tactic.h"

//Fsmash!!!
class FsmashTactic : public Tactic
{

public:
    FsmashTactic();
    ~FsmashTactic();
    void DetermineChain();
    std::string ToString(){return "FsmashTactic";};

};

#endif
