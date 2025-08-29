#include <vector>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <cctype>

struct cell{
    uint8_t x;
    uint8_t y;
};

struct ship : public cell {
    uint8_t len;
    uint8_t life;
    bool direction;
};

struct Battlefield {
    uint8_t height = 10;
    uint8_t width = 10;
};

class Player {
    std::vector<ship> ships_alive;
    std::vector<ship> ships_dead;
};

enum class Game_status {
    preparation,
    run,
    stop
};

class Game : public Battlefield, public GameBot {
    Game_status status = Game_status::preparation;

    public:
        bool IsGameRun() {
            return status == Game_status::run;
        }
                
        Game_status GetStatus() {
            return status;
        }

        void SetStatus(Game_status new_status) { status = new_status; }

        
};

class GameBot {
    public:
        cell TakeShot () {

        }

        void GetShot (cell shot) {

        }

        void SetResult (std::string result) {

        }


};

void PreparationParse (std::string& command, Game& Battleship) {
    // COMMANDS:
    // ping
    // create [master,slave]
    // start

    std::string sub_command;
    std::vector<std::string> Sub_commands;
    std::istringstream input(command);
    while (input >> sub_command) 
            Sub_commands.push_back(sub_command);


    if (Sub_commands.size() == 1 && Sub_commands[0] == "ping") 
        std::cout << "pong\n";

    else if (Sub_commands.size() == 1 && command == "exit") 
        std::cout << "ok\n";

    else if (Sub_commands.size() == 1 && command == "start")
        Battleship.SetStatus(Game_status::run);

    else std::cerr << "unknow command\n";
}

void RunParse(std::string& command, Game& Battleship) {
    // COMMANDS:
    // stop
    // continue
    // shot X Y
    // shot
    // set result [miss,hit,kill]

    std::string sub_command;
    std::vector<std::string> Sub_commands;
    std::istringstream input(command);
    while (input >>  sub_command)
        Sub_commands.push_back(sub_command);


    if (Sub_commands.size() == 1 && Sub_commands[0] == "stop")
        Battleship.SetStatus(Game_status::stop);

    else if (Sub_commands.size() == 1 && Sub_commands[0] == "continue") 
        Battleship.SetStatus(Game_status::run);

    else if (Sub_commands.size() == 1 && Sub_commands[0] == "shot") {
        cell shot = Battleship.TakeShot();
        std::cout << shot.x << ' ' << shot.y << '\n';
    } 
    
    else if (Sub_commands.size() == 3 && Sub_commands[0] == "shot" && isdigit(Sub_commands[1]) && isdigit(Sub_commands[2])) {
        Battleship.GetShot({Sub_commands[1], Sub_commands[2]});
        std::cout << "ok\n";
    }
    
    else if (Sub_commands.size() == 3 && Sub_commands[0] == "set" && Sub_commands[1] == "result") {
        if (Sub_commands[2] == "kill" || Sub_commands[2] == "hit" || Sub_commands[2] == "miss") {
            Battleship.SetResult(Sub_commands[2]);
            std::cout << "ok\n";
        }

        else std::cerr << "unknown result\n";
    }
    
    else std::cerr << "unknown command\n";
}

int main() {
    Game Battleship;

    std::string command;
    while (command != "exit") {
        std::getline(std::cin, command);
        
        if (!Battleship.IsGameRun())
            PreparationParse(command, Battleship);
        else 
            RunParse(command, Battleship);
    }

    return 0;
}