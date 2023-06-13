#include "Python.h"
#include "Movements.h"
//#include "thread"


#pragma region Maps

map<string, map<char, int>> classic_pos = { {"player.pos", {{'x', 9}, {'y', 15}}}, {"crims.pos", {{'x', 9}, {'y', 9}}}, {"phantom.pos", {{'x', 8}, {'y', 9}} } };

vector<vector<int>> classic_map = {
        {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 5, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 5, 2},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2},
        {2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2},
        {2, 2, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 2},
        {2, 2, 2, 2, 1, 2, 0, 2, 2, 3, 2, 2, 0, 2, 1, 2, 2, 2, 2},
        {1, 1, 1, 1, 1, 0, 0, 3, 0, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 1, 2, 0, 2, 2, 3, 2, 2, 0, 2, 1, 2, 2, 2, 2},
        {2, 2, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 2},
        {2, 2, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 2, 2},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2},
        {2, 5, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 5, 2},
        {2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2},
        {2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2},
        {2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4},
};


map<string, map<char, int>> sandbox_pos = { {"player.pos", {{'x', 9}, {'y', 15}}}, {"crims.pos", {{'x', 9}, {'y', 9}}}, {"phantom.pos", {{'x', 8}, {'y', 9}} } };

vector<vector<int>> sandbox_map = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


map<string, map<char, int>> colos_pos = { {"player.pos", {{'x', 1}, {'y', 1}}}, {"crims.pos", {{'x', 10}, {'y', 10}}}, {"phantom.pos", {{'x', 20}, {'y', 20}} } };

vector<vector<int>> colos_map = Vec2DGenerator(1, 30, 30);

#pragma endregion

void Field_Comporator(vector<vector<int>> chosen_map, map<string, map<char, int>> chosen_pos) {
    game.y = size(chosen_map) - 1;
    game.x = size(chosen_map[0]) - 1;

    ModalsInit();

    for (int i = 0; i < game.y + 1; i++)
    {
        vector<MovableObject> temp;
        for (int j = 0; j < game.x + 1; j++)
        {
            temp.push_back(uplate);
        }
        game.movfield.push_back(temp);
    }

    for (int i = 0; i < game.y + 1; i++) {
        vector<Object> temp;
        for (int j = 0; j < game.x + 1; j++)
        {
            Object* a = &map_coding[chosen_map[i][j]];
            temp.push_back(*a);
        }
        game.field.push_back(temp);
    }

    player.pos.x = chosen_pos["player.pos"]['x'];
    player.pos.y = chosen_pos["player.pos"]['y'];
    crims.start_pos.x, crims.pos.x = chosen_pos["crims.pos"]['x'];
    crims.start_pos.y, crims.pos.y = chosen_pos["crims.pos"]['y'];
    phantom.pos.x = chosen_pos["phantom.pos"]['x'];
    phantom.pos.y = chosen_pos["phantom.pos"]['y'];

    crims.start_pos = crims.pos;
    phantom.start_pos = phantom.pos;
    game.movfield[player.pos.y][player.pos.x] = player;
    game.movfield[crims.pos.y][crims.pos.x] = crims;
    game.movfield[phantom.pos.y][phantom.pos.x] = phantom;

    game.fruit_pos = { {player.pos.x, player.pos.y}, {1, 1}, {game.x - 1, 1}, {game.x - 1, game.y - 1}, {1, game.y - 1} };
}

void LightField_Comporator() {
    for (int i = 0; i < game.y + 1; i++) {
        vector<int> temp;
        for (int j = 0; j < game.x + 1; j++)
        {
            if (events.night)
            {
                temp.push_back(Dark);
            }
            else
            {
                temp.push_back(Light);
            }
        }
        game.lightfield.push_back(temp);
    }
}



void Game_Win() {
    Fore("LIGHT RED");
    cout << endl << "You Win!" << endl;
    Fore();
    game.timer = 0;
}

void Game_Lose() {
    Fore("LIGHT RED");
    cout << endl << "You Lose!" << endl;
    Fore();
    game.timer = 0;
}

void Game_Play() {
    game.timer = 0;
    bool funny = false;
    int fun_timer = game.speed;
    double screen_timer = 0.1;
    int panic_timer = game.speed * 10;
    int infection_timer = game.speed * 5;

    int crims_timer = crims.speed * 10;
    int phantom_timer = phantom.speed * 10;
    int player_timer = player.speed;

    while (true)
    {
        if (crims_timer <= 0 and !events.pause and !events.freeze and crims.active and player.active)
        {
            crims_move.Move();
            crims_timer = crims.speed;
        }
        if (phantom_timer <= 0 and !events.pause and !events.freeze and phantom.active and player.active)
        {
            phantom_move.Move();
            phantom_timer = phantom.speed;
        }
        if (infection_timer <= 0 and !events.pause)
        {
            Infection();
            infection_timer = game.speed * 5;
        }


        if (((PosConside(player.pos, crims.pos) and crims.active and !crims.die) or (PosConside(phantom.pos, player.pos) and phantom.active and !phantom.die)) and events.mode != Panic) {
            Game_Lose();
            break;
        }
        else if (game.score >= 15000) {
            Game_Win();
            break;
        }
        else if (game.objects.first[token.id].collected == 50 and events.fruits_spawned == ZeroWave)  events.EvSpawnFruit();
        else if (panic_timer <= 0) {
            events.EvUnPanic();
            panic_timer = game.speed * 10;
        }
        else if (fun_timer <= 0 and !player.active) {
            funny = events.EvUnPlayer(funny);
            fun_timer = game.speed;
        }


        if (_kbhit() and player_timer <= 0) {
            player_move.Move(_getch());
            player_timer = player.speed;
        }



        if (!events.pause) {
            if (events.mode == Panic) panic_timer--;
            game.timer++;
            game.tick = (2 / (game.timer)) * 10000000;
            crims_timer--;
            phantom_timer--;
            fun_timer--;
            infection_timer--;
            if (game.timer >= 1000000)
            {
                game.timer -= Round(game.timer - (game.timer / 2));
            }
        }
        player_timer--;
    }
}



void main() {
    SetBooferWindow(100, 50);
    SetWindow(1500, 1000);
    SetConcoleFont(15, 24);
    SetShowCursor(false);
    Beep(550, 300);
    Beep(500, 100);
    Beep(500, 100);
    Beep(600, 50);

    BaseObjectsInit();
    BaseMovableObjectInit();
    game.objects = { {plate, token, fruit, tabl, bush, phantwall, wall, torch}, { player, crims, phantom } };
    CommandGenerate();
    Field_Comporator(classic_map, classic_pos);
    LightField_Comporator();
    Field_Out();
    Field_Out();
    BaseObjectsInit();

    Game_Play();
}