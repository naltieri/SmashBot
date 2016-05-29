#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <csignal>
#include <string>
#include <time.h>
#include <sstream>


#include "Goals/KillOpponent.h"
#include "Goals/NavigateMenu.h"

#include "Util/GameState.h"
#include "Util/MemoryWatcher.h"
#include "Util/Logger.h"
#include "Util/Controller.h"


bool isDebug = false;


void FirstTimeSetup()
{
    struct passwd *pw = getpwuid(getuid());
    std::string home_path = std::string(pw->pw_dir);
    // std::string legacy_config_path = home_path + "/.dolphin-emu";
    std::string legacy_config_path = "/Applications/Dolphin.app";
    std::string mem_watcher_path;
    std::string pipe_path;

    struct stat buffer;
    if(stat(legacy_config_path.c_str(), &buffer) != 0)
    {
        //If the legacy app path is not present, see if the new one is
        const char *env_XDG_DATA_HOME = std::getenv("XDG_DATA_HOME");
        if(env_XDG_DATA_HOME == NULL)
        {
            //Try $HOME/.local/share next
            std::string backup_path = home_path + "/.local/share/dolphin-emu";
            if(stat(backup_path.c_str(), &buffer) != 0)
            {
                std::cout << "In smashbot" << std::endl;
                std::cout << "ERROR: $XDG_DATA_HOME was empty and so was $HOME/.dolphin-emu and $HOME/.local/share/dolphin-emu " \
                    "Are you sure Dolphin is installed? Make sure it is, and then run SmashBot again." << std::endl;
                exit(-1);
            }
            else
            {
                mem_watcher_path = backup_path;
                mem_watcher_path += "/MemoryWatcher/";
                pipe_path = backup_path;
                pipe_path += "/Pipes/";
            }
        }
        else
        {
            mem_watcher_path = env_XDG_DATA_HOME;
            mem_watcher_path += "/MemoryWatcher/";
            pipe_path = env_XDG_DATA_HOME;
            pipe_path += "/Pipes/";
        }
    }
    else
    {
        mem_watcher_path = legacy_config_path + "/MemoryWatcher/";
        pipe_path = legacy_config_path + "/Pipes/";
    }

    //Create the MemoryWatcher directory if it doesn't already exist
    if(stat(mem_watcher_path.c_str(), &buffer) != 0)
    {
        if(mkdir(mem_watcher_path.c_str(), 0775) != 0)
        {
            std::cout << "ERROR: Could not create the directory: \"" << mem_watcher_path << "\". Dolphin seems to be installed, " \
                "But this is not working for some reason. Maybe permissions?" << std::endl;
            exit(-1);
        }
        std::cout << "WARNING: Had to create a MemoryWatcher directory in Dolphin just now. " \
            "You may need to restart Dolphin and SmashBot in order for this to work. (You should only see this warning once)" << std::endl;
    }

    std::ifstream src("Locations.txt", std::ios::in);
    std::ofstream dst(mem_watcher_path + "/Locations.txt", std::ios::out);
    dst << src.rdbuf();

    //Create the Pipes directory if it doesn't already exist
    if(stat(pipe_path.c_str(), &buffer) != 0)
    {
        if(mkdir(pipe_path.c_str(), 0775) != 0)
        {
            std::cout << "ERROR: Could not create the directory: \"" << pipe_path << "\". Dolphin seems to be installed, " \
                "But this is not working for some reason. Maybe permissions?" << std::endl;
            exit(-1);
        }
        std::cout << "WARNING: Had to create a Pipes directory in Dolphin just now. " \
            "You may need to restart Dolphin and SmashBot in order for this to work. (You should only see this warning once)" << std::endl;
    }
}

void signal_handler(int signal)
{
    std::string logpath = "Logs";
    struct stat buffer;

    Controller *controller = Controller::Instance();
    controller->emptyInput();

    if(isDebug)
    {
        Logger *logger = Logger::Instance();
        std::string logdump = logger->DumpLog();

        if(stat(logpath.c_str(), &buffer) != 0)
        {
            if(mkdir(logpath.c_str(), 0775) != 0)
            {
                std::cout << "ERROR: Could not create the directory: \"" << logpath << "\". Maybe permissions?" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        //Name the file as a timestamp
        static char name[20];
        time_t now = time(0);
        strftime(name, sizeof(name), "%Y%m%d_%H%M%S", localtime(&now));
        std::string filename = std::string(name);

        std::cout << "\nINFO: Log file written to: " << logpath + "/" + filename + ".csv" << std::endl;

        std::ofstream dst(logpath + "/" + filename + ".csv", std::ios::out);
        dst << logdump;
        dst.close();
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        std::string arg = std::string(argv[1]);
        if(arg == "--debug")
        {
            isDebug = true;
        }
    }

    //Do some first-time setup
    FirstTimeSetup();

    std::signal(SIGINT, signal_handler);

    Logger *logger = Logger::Instance();
    logger->SetDebug(isDebug);
    GameState *state = GameState::Instance();
    Controller *m_controller;
    m_controller = Controller::Instance();  

    MemoryWatcher *watcher = new MemoryWatcher();
    uint last_frame = 0;
    //Get our goal
    Goal *goal = NULL;
    MENU current_menu;

    //Main frame loop
    for(;;)
    {
        //If we get a new frame, process it. Otherwise, keep reading memory
        if(!watcher->ReadMemory())
        {
            continue;
        }

        current_menu = (MENU)state->m_memory->menu_state;
        if(state->m_memory->frame != last_frame)
        {
            if(state->m_memory->frame > last_frame+1)
            {
                std::cout << "WARNING: FRAME MISSED" << std::endl;
            }
            last_frame = state->m_memory->frame;

            //If we're in a match, play the match!
            if(state->m_memory->menu_state == IN_GAME)
            {
				//Make sure our states are updated before writing
				watcher->ReadMemory();
				std::string frame_s;

				frame_s = std::to_string(state->m_memory->frame);


				
                //Write Gamestate to File:
                //Open GamestateFile:
                //Q: Why do we need std? Something to do with namestates
                std::ofstream statef;
                statef.open ("gamestate.txt");
                
                
                
				int fnum = 0;

				statef <<  std::dec << state->m_memory->frame << ","; //0
				statef <<  std::dec << fnum << ",";
				statef <<  std::clock() << ",";
				statef <<  state->m_memory->player_one_percent << ","; 
				statef <<  state->m_memory->player_two_percent << ",";  //4
				statef <<  state->m_memory->player_one_stock << ",";
				statef <<  state->m_memory->player_two_stock << ",";
				statef <<  state->m_memory->player_one_character << ",";
				statef <<  state->m_memory->player_two_character << ",";  //8
				statef <<  state->m_memory->player_one_facing << ",";
				statef <<  state->m_memory->player_two_facing << ",";

				statef <<  std::hex << state->m_memory->stage << ",";
				
				statef <<  state->m_memory->menu_state << ",";   //12
				statef <<  state->m_memory->player_two_pointer_x << ",";
				statef <<  state->m_memory->player_two_pointer_y << ",";

				statef <<  std::fixed << std::setprecision(2) << state->m_memory->player_one_x << ",";
				statef <<  std::fixed << std::setprecision(2) << state->m_memory->player_one_y << ",";  //16

				statef <<  std::fixed << std::setprecision(2) << state->m_memory->player_two_x << ",";
				statef <<  std::fixed << std::setprecision(2) << state->m_memory->player_two_y << ",";

				statef <<  std::hex << state->m_memory->player_one_action << ",";
				statef <<  std::hex << state->m_memory->player_two_action << ",";  //20

				statef <<  std::dec << state->m_memory->player_one_action_counter << ",";
				statef <<  std::dec << state->m_memory->player_two_action_counter << ",";

				statef <<  std::dec << state->m_memory->player_one_action_frame << ",";
				statef <<  std::dec << state->m_memory->player_two_action_frame << ",";  //24

				statef <<  state->m_memory->player_one_invulnerable << ",";
				statef <<  state->m_memory->player_two_invulnerable << ",";

				statef <<  state->m_memory->player_one_charging_smash << ",";
				statef <<  state->m_memory->player_two_charging_smash << ",";  //28

				statef <<  state->m_memory->player_one_hitlag_frames_left << ",";
				statef <<  state->m_memory->player_two_hitlag_frames_left << ",";

				statef <<  state->m_memory->player_one_hitstun_frames_left << ",";
				statef <<  state->m_memory->player_two_hitstun_frames_left << ",";  //32

				statef <<  state->m_memory->player_one_jumps_left << ",";
				statef <<  state->m_memory->player_two_jumps_left << ",";

				statef <<  state->m_memory->player_one_on_ground << ",";
				statef <<  state->m_memory->player_two_on_ground << ",";  //36

				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_one_speed_air_x_self << ",";
				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_two_speed_air_x_self << ",";

				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_one_speed_y_self << ",";
				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_two_speed_y_self << ",";  //40

				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_one_speed_x_attack << ",";
				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_two_speed_x_attack << ",";

				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_one_speed_y_attack << ",";
				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_two_speed_y_attack << ",";  //44

				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_one_speed_ground_x_self << ",";
				statef <<  std::fixed << std::setprecision(2) <<  state->m_memory->player_two_speed_ground_x_self << "\n";
				
				//statef <<  state->m_memory->controller_1_digital << ",";
				//statef <<  state->m_memory->controller_1_analog << ",";  //48
				//statef <<  state->m_memory->controller_1_shoulder << ",";
				
				//statef <<  state->m_memory->controller_2_digital << ",";
				//statef <<  state->m_memory->controller_2_analog << ",";
				//statef <<  state->m_memory->controller_2_shoulder << "\n";  //52
				
				


                statef.close(); 

				std::ofstream myfile;

                myfile.open ("curframe.txt");
                int cur_frame = state->m_memory->frame;
                std::string s;

                s = std::to_string(cur_frame);
                myfile << s;

                myfile.close(); 

                //Get new input from python
                bool pythonRun = true;
                //Initialize to -1, you know, just in case
                int py_frame = -1;
                while(pythonRun){

                    std::ifstream myfile ("pyframe.txt");
                    std::string line;
                    // I don't understand why this if-else clause is necessary but it's in the tutorial
                    if (myfile.is_open()){
                        getline (myfile,line);
                        myfile.close();
                        // I don't understand why this works; I just copy-pasted it from quora      
                        std::stringstream convert(line);
                        convert>>py_frame;
                    }  
                    else std::cout << "Unable to open pyframe\n"; 
                    if(py_frame == cur_frame){
                        //We have just completed our computation of the next action
                        pythonRun = false;

                        //Read new actions 

                        std::ifstream myfile ("inputs.txt");
                        std::string line;
                        int input;
                        double x;
                        double y;

                        // I don't understand why this if-else clause is necessary but it's in the tutorial
                        if (myfile.is_open()){
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream converta(line);
                            converta>>input;
                            if(input == 1){
                                //Press A
                                m_controller->pressButton(Controller::BUTTON_A);

                            }else{
                                //Input should be zero
                                //Release A
                                m_controller->releaseButton(Controller::BUTTON_A);
                            }
                            
                            
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertb(line);
                            convertb>>input;
                            if(input == 1){
                                //Press B
                                m_controller->pressButton(Controller::BUTTON_B);

                            }else{
                                //Input should be zero
                                //Release B
                                m_controller->releaseButton(Controller::BUTTON_B);
                            }
                            
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertx(line);
                            convertx>>input;
                            if(input == 1){
                                //Press X
                                m_controller->pressButton(Controller::BUTTON_X);

                            }else{
                                //Input should be zero
                                //Release X
                                m_controller->releaseButton(Controller::BUTTON_X);
                            }
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream converty(line);
                            converty>>input;
                            if(input == 1){
                                //Press Y
                                m_controller->pressButton(Controller::BUTTON_Y);

                            }else{
                                //Input should be zero
                                //Release Y
                                m_controller->releaseButton(Controller::BUTTON_Y);
                            }
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertz(line);
                            convertz>>input;
                            if(input == 1){
                                //Press Z
                                m_controller->pressButton(Controller::BUTTON_Z);

                            }else{
                                //Input should be zero
                                //Release Z
                                m_controller->releaseButton(Controller::BUTTON_Z);
                            }
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertl(line);
                            convertl>>input;
                            if(input == 1){
                                //Press L
                                m_controller->pressButton(Controller::BUTTON_L);

                            }else{
                                //Input should be zero
                                //Release L
                                m_controller->releaseButton(Controller::BUTTON_L);
                            }
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertr(line);
                            convertr>>input;
                            if(input == 1){
                                //Press R
                                m_controller->pressButton(Controller::BUTTON_R);

                            }else{
                                //Input should be zero
                                //Release R
                                m_controller->releaseButton(Controller::BUTTON_R);
                            }
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertd(line);
                            convertd>>input;
                            if(input == 1){
                                //Press Up on D-pad
                                m_controller->pressButton(Controller::BUTTON_D_UP);

                            }else{
                                //Input should be zero
                                //Release Up on D-pad
                                m_controller->releaseButton(Controller::BUTTON_D_UP);
                            }
                            
                            
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertax(line);
                            convertax>>x;
                            
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertay(line);
                            convertay>>y;
       
							//Press direction on analog stick
							m_controller->tiltAnalog(Controller::BUTTON_MAIN, x, y);
							
							
							getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertcx(line);
                            convertcx>>x;
                            
                            getline (myfile,line);
                            // I don't understand why this works; I just copy-pasted it from quora
                            std::stringstream convertcy(line);
                            convertcy>>y;
       
							//Press direction on analog stick
							m_controller->tiltAnalog(Controller::BUTTON_C, x, y);


                            myfile.close();
                                                    }  
                        else std::cout << "Unable to open inputs\n"; 
                        }

                }

            }
            //If we're in a menu, then let's navigate the menu
            else if(state->m_memory->menu_state == CHARACTER_SELECT ||
                state->m_memory->menu_state == STAGE_SELECT ||
                state->m_memory->menu_state == POSTGAME_SCORES)
            {
                if(goal == NULL )
                {
                    goal = new NavigateMenu();
                }
                if(typeid(*goal) != typeid(NavigateMenu))
                {
                    delete goal;
                    goal = new NavigateMenu();
                }
                goal->Strategize();
            }
        }
        //If the menu changed
        else if(current_menu != state->m_memory->menu_state)
        {
            last_frame = 1;
            current_menu = (MENU)state->m_memory->menu_state;
        }

        logger->SetGoal(goal);
        logger->LogFrame();
    }

    return EXIT_SUCCESS;
}
