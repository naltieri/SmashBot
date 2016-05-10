#ifndef JABTACTIC_H
#define JABTACTIC_H

#include "Tactic.h"

//JAB!!!
class JabTactic : public Tactic
{

public:
    JabTactic();
    ~JabTactic();
    void DetermineChain();
    std::string ToString(){return "JabTactic";};

};

#endif
