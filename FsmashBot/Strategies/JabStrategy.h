#ifndef JABSTRATEGY_H
#define JABSTRATEGY_H

#include "Strategy.h"

//Jab!
class JabStrategy : public Strategy
{

public:

    JabStrategy();
    ~JabStrategy();

    //Determine what tactic to employ in order to further our strategy
    void DetermineTactic();
    std::string ToString(){return "JabStrategy";};

private:
    //Frame that the player's attack started
    //0 means no attack
    uint m_attackFrame;
    //The action the opponent was in last frame
    ACTION m_lastAction;
    uint m_lastActionCount;
    //Did the enemy's action change from last frame?
    bool m_actionChanged;
    //Have we shielded the opponent's current attack?
    bool m_shieldedAttack;
    //Was the opponent charging a smash last frame?
    bool m_chargingLastFrame;
};

#endif
