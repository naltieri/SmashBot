#include "Fsmash.h"

void Fsmash::PressButtons()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    switch(frame)
    {
        case 0:
        {
            //Press towards Opponent

            bool isOnRight = m_state->m_memory->player_one_x < m_state->m_memory->player_two_x;
            if(isOnRight)
            {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 1);
            }       
            else {
                m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, 0);
            }       
  
            break;
        }
        case 1:
        {
            // UpB!!!
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, 1, .5);
            m_controller->pressButton(Controller::BUTTON_B);

            break;
        }
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
