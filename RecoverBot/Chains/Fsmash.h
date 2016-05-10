#ifndef FSMASH_H
#define FSMASH_H

#include "Chain.h"

//Do a single Fsmash
class Fsmash : public Chain
{

public:

    Fsmash();
    ~Fsmash();
    //Determine what buttons to press in order to execute our tactic
    void PressButtons();
    bool IsInterruptible();
    std::string ToString(){return "Fsmash";};

};

#endif
