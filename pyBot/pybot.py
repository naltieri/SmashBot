'''pybot starts by doing a shell call to start smashbot, then it tries looping to read states and write actions
if things constally loops, reading gamestate from a file, and outputting actions
to another file.
'''
import os
import numpy as np

def read_gamestate_from_file(fileloc="./gamestate.txt"):
    pass
    #return np.array()
def get_gamestate(from_c="./gamestate.txt",previous_buttons=_previous_buttons):#from_py="./controlleraction.txt"):
    return {'framenum':get_frame_num(from_c),''}

def opponent_is_on_left(gamestate):
    return True #TODO
def can_I_jab_now(gamestate):
    return True #TODO

def write_action_jab(filoc="./controlleraction.txt"):
    with open(fileloc,'w') as f:
        f.write(get_jab_action_as_string())

def get_jab_action_as_string():
    return "press_A"

def start_smashbot():
    os.system("./smashbot")

if __name__=="__main__":
    start_smashbot()
    if playing_game():
        while True:
            gs=get_gamestate
            write_action(gs)


#include "Jab.h"

void Jab::PressButtons()
{
    uint frame = m_state->m_memory->frame - m_startingFrame;
    switch(frame)
    {
        case 0:
        {
            //Jab
            m_controller->pressButton(Controller::BUTTON_A);
            m_controller->tiltAnalog(Controller::BUTTON_MAIN, .5, .5);
            break;
        }
        case 1:
        {
            //Let go of jab
            m_controller->releaseButton(Controller::BUTTON_A);
            break;
        }
    }
}

bool Jab::IsInterruptible()
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

Jab::Jab()
{
    m_startingFrame = m_state->m_memory->frame;
}

Jab::~Jab()
{
}
