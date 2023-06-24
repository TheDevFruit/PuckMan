#include "Python.h"
#include "Movements.h"
//#include "thread"


#pragma region Maps

map<int, Object> map_coding;


map<string, map<char, int>> zero_pos = { {"player.pos", {{'x', 0}, {'y', 0}}}, {"crims.pos", {{'x', 0}, {'y', 0}}}, {"phantom.pos", {{'x', 0}, {'y', 0}} }, {"moss.pos", {{'x', 0}, {'y', 0}}} };


map<string, map<char, int>> classic_pos = { {"player.pos", {{'x', 9}, {'y', 15}}}, {"crims.pos", {{'x', 9}, {'y', 9}}}, {"phantom.pos", {{'x', 8}, {'y', 9}} }, {"moss.pos", {{'x', 10}, {'y', 9}}} };

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


map<string, map<char, int>> sandbox_pos = { {"player.pos", {{'x', 9}, {'y', 15}}}, {"crims.pos", {{'x', 9}, {'y', 9}}}, {"phantom.pos", {{'x', 8}, {'y', 9}} }, {"moss.pos", {{'x', 10}, {'y', 9}}} };

vector<vector<int>> sandbox_map = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
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


map<string, map<char, int>> colos_pos = { {"player.pos", {{'x', 1}, {'y', 1}}}, {"crims.pos", {{'x', 10}, {'y', 10}}}, {"phantom.pos", {{'x', 20}, {'y', 20}} }, {"moss.pos", {{'x', 25}, {'y', 25}}} };

vector<vector<int>> colos_map = Vec2DGenerator(30, 30, 1);


map<string, map<char, int>> life_pos = { {"player.pos", {{'x', 9}, {'y', 15}}}, {"crims.pos", {{'x', 9}, {'y', 9}}}, {"phantom.pos", {{'x', 8}, {'y', 9}} }, {"moss.pos", {{'x', 10}, {'y', 9}}} };

#pragma endregion

void Field_Comporator(vector<vector<int>> chosen_map, map<string, map<char, int>> chosen_pos) {
    Game.y = size(chosen_map) - 1;
    Game.x = size(chosen_map[0]) - 1;

    for (int i = 0; i < Game.y + 1; i++)
    {
        vector<Entity> temp;
        for (int j = 0; j < Game.x + 1; j++)
        {
            temp.push_back(uplate);
        }
        Game.movfield.push_back(temp);
    }

    for (int i = 0; i < Game.y + 1; i++) {
        vector<Object> temp;
        for (int j = 0; j < Game.x + 1; j++)
        {
            Object* a = &map_coding[chosen_map[i][j]];
            temp.push_back(*a);
        }
        Game.field.push_back(temp);
    }

    player.pos.x = chosen_pos["player.pos"]['x'];
    player.pos.y = chosen_pos["player.pos"]['y'];
    crims.pos.x = chosen_pos["crims.pos"]['x'];
    crims.pos.y = chosen_pos["crims.pos"]['y'];
    phantom.pos.x = chosen_pos["phantom.pos"]['x'];
    phantom.pos.y = chosen_pos["phantom.pos"]['y'];
    moss.pos.x = chosen_pos["moss.pos"]['x'];
    moss.pos.y = chosen_pos["moss.pos"]['y'];

    crims.start_pos = crims.pos;
    moss.start_pos = moss.pos;
    moss.start_pos = moss.pos;

    Game.movfield[player.pos.y][player.pos.x] = player;
    Game.movfield[crims.pos.y][crims.pos.x] = crims;
    Game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
    Game.movfield[moss.pos.y][moss.pos.x] = moss;

    Game.fruit_pos = { {player.pos.y, player.pos.x}, {1, 1}, {1, Game.x - 1}, {Game.y - 1, Game.x - 1}, {Game.y - 1, 1} };
}

void DeSizeConsole() {
    int x = 15;
    int y = 24;
    if (Game.x > 20)
    {
        x /= ((Game.x+1 % 20)/2);
    }
    if (Game.y > 20)
    {
        y /= ((Game.y+1 % 20)/2);
    }
    SetConsoleFont(x, y);
}



void Game_Win() {
    Field_GameActive();
    Game.timer = 0;
    Sleep(100000000000);
}

void Game_Lose() {
    player.die = true;
    Field_GameActive();
    Game.timer = 0;
    Sleep(100000000000);
}

void Game_Play() {
    Game.timer = 0;
    bool funny = false;
    int fun_timer = Game.speed;
    double screen_timer = 0.1;
    int panic_timer = Game.speed * 10;
    int infection_timer = Game.speed * 5;
    int life_timer = GameLife.speed;

    int crims_timer = crims.speed * 10;
    int phantom_timer = phantom.speed * 10;
    int moss_timer = moss.speed * 10;
    int player_timer = player.speed;

    while (true) {
        if (!GameLife.active) {
            if (!Event.pause and !Event.freeze and player.active)
            {
                if (crims_timer <= 0 and crims.active)
                {
                    crims_move.Move();
                    crims_timer = crims.speed;
                }
                if (phantom_timer <= 0 and phantom.active)
                {
                    phantom_move.Move();
                    phantom_timer = phantom.speed;
                }
                if (moss_timer <= 0 and moss.active)
                {
                    moss_move.Move();
                    moss_timer = moss.speed;
                }
                if (infection_timer <= 0)
                {
                    Infection();
                    infection_timer = Game.speed * 5;
                }
            }


            if (((player.pos.Conside(crims.pos) and crims.active and !crims.die) or (player.pos.Conside(phantom.pos) and phantom.active and !phantom.die)) or (moss.pos.Conside(moss.pos) and moss.active and !moss.die) and Event.mode != Panic) {

            }
            else if (Game.score >= 15000) {
                Game_Win();
                break;
            }
            else if (Game.objects.first[token.id].collected == 50 and Event.fruits_spawned == ZeroWave)  Event.ToSpawnFruit();
            else if (panic_timer <= 0) {
                Event.ToUnPanic();
                panic_timer = Game.speed * 10;
            }
            else if (fun_timer <= 0 and !player.active) {
                funny = Event.ToUnPlayer(funny);
                fun_timer = Game.speed;
            }
        }

        if (GameLife.active and life_timer == 0) {
                SimulateLife();
                life_timer = GameLife.speed;
            }


        if (_kbhit() and player_timer <= 0) {
                player_move.Move(_getch());
                player_timer = player.speed;
            }



        if (!Event.pause and !GameLife.active) {
                if (Event.mode == Panic) panic_timer--;
                Game.timer++;
                Game.tick = (2 / (Game.timer)) * 10000000;
                crims_timer--;
                phantom_timer--;
                moss_timer--;
                fun_timer--;
                infection_timer--;
                if (Game.timer >= 1000000)
                {
                    Game.timer -= Round(Game.timer - (Game.timer / 2));
                }
            }
        if (!Event.pause and GameLife.active) life_timer--;
        player_timer--;
    }
}



void GameInit() {
    Game.objects = { {plate, token, fruit, tabl, bush, phantwall, wall, torch}, { player, crims, phantom, moss } };
    CommandGenerate();
    Sounds.GameStart();
    Field_Comporator(classic_map, classic_pos);
    Modals.Init();
    FieldOut();
    Game_Play();
}

void WorldInit() {
    BaseConsoleGameInit();
    BaseObjectsInit();
    map_coding = { {0, plate}, {1, token}, {2, wall}, {3, phantwall}, {4, torch}, {5, tabl}, {6, bush} };
    BaseEntityInit();
    BaseGameLifeInit();
    CommandGenerate();
}

void main() {
    WorldInit();
    GameInit();
}