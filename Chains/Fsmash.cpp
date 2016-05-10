#include "Fsmash.h"

void Fsmash::PressButtons()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    // switch(frame)
    // {
    //     case 0:
    //     {
            //Fsmash

            bool isOnRight = m_state->m_memory->player_one_x < m_state->m_memory->player_two_x;
            if(isOnRight)
            {
                m_controller->tiltAnalog(Controller::BUTTON_C, 0, .5);
            }       
            else {
                m_controller->tiltAnalog(Controller::BUTTON_C, 1, .5);
            }       
  
            // break;
        // }
        // case 1:
        // {
            // //Let go of Fsmash
            // m_controller->tiltAnalog(Controller::BUTTON_C, .5, .5);
            // break;
        // }
    }
}

bool Fsmash::IsInterruptible()
{
    if(m_state->m_memory->player_two_action == STANDING)
    {
        return true;
    }

    uint frame = m_state->m_memory->frame - m_startingFrame;
    if(frame >= 18)
    {
        return true;
    }
    return false;
}

Fsmash::Fsmash()
{
    m_startingFrame = m_state->m_memory->frame;
}

Fsmash::~Fsmash()
{
}
