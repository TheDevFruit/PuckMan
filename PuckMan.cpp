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
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
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

    phantom.points = { {1, 1}, { Game.y - 1, 1 }, { Game.y - 1, Game.x - 1 }, { 1, Game.x - 1 } };
    moss.points = { {1, 1}, {1, Game.x - 1}, {Game.y - 1, Game.x - 1}, {Game.y - 1, 1} };

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
        x /= ((Game.x + 1 % 20) / 2);
    }
    if (Game.y > 20)
    {
        y /= ((Game.y + 1 % 20) / 2);
    }
    SetConsoleFont(x, y);
}



void GameWin() {
    Field_GameActive();
    Game.timer = 0;
    Sleep(100000000000);
}

void GameLose() {
    Game.player_lives -= 1;
    Field_GameActive();
    Game.timer = 0;
    Sleep(10000);
    if (Game.player_lives != 0) {
        GameInit();
        return;
    }
    Sleep(100000000000);
}

void GamePlay() {
    Game.timer = 0;
    bool funny = false;

    while (true) {
        if (!GameLife.active) {
            if (!Event.pause and !Event.freeze and player.active)
            {
                if (Timer.crims <= 0 and crims.active)
                {
                    crims_move.Move();
                    Timer.crims = crims.speed;
                    if (crims.point.id == mycelium.id) Timer.crims -= (crims.speed / 5);
                }
                if (Timer.phantom <= 0 and phantom.active)
                {
                    phantom_move.Move();
                    Timer.phantom = phantom.speed;
                    if (phantom.point.id == mycelium.id) Timer.phantom -= (phantom.speed / 5);
                }
                if (Timer.moss <= 0 and moss.active)
                {
                    moss_move.Move();
                    Timer.moss = moss.speed;
                    if (moss.point.id == mycelium.id) Timer.moss -= (moss.speed / 5);
                }
                if (Timer.infection <= 0)
                {
                    Infection();
                    Timer.infection = Game.speed * 5;
                }
            }


            if (((player.pos.Conside(crims.pos) and crims.active and !crims.die) or
                (player.pos.Conside(phantom.pos) and phantom.active and !phantom.die) or
                (player.pos.Conside(moss.pos) and moss.active and !moss.die)) and Event.mode != Panic)
            {
                GameLose();
                break;
            }
            else if (Game.score >= 15000) {
                GameWin();
                break;
            }
            else if (Game.objects.first[token.id].collected == 50 and Event.fruits_spawned == ZeroWave)  Event.ToSpawnFruit();
            else if (Timer.panic <= 0) {
                Event.ToUnPanic();
                Timer.panic = Game.speed * 10;
            }
            else if (Timer.fun <= 0 and !player.active) {
                funny = Event.ToUnPlayer(funny);
                Timer.fun = Game.speed;
            }
        }

        if (GameLife.active and Timer.life == 0) {
            SimulateLife();
            Timer.life = GameLife.speed;
        }


        if (_kbhit() and Timer.player <= 0) {
            player_move.Move(_getch());
            Timer.player = player.speed;
        }
        else if (!Event.night and Timer.player <= -(player.speed / 2) and player.move_dir != -1)
        {
            if (player.move_dir == Up) player_move.Move('w');
            else if (player.move_dir == Left) player_move.Move('a');
            else if (player.move_dir == Down) player_move.Move('s');
            else if (player.move_dir == Right) player_move.Move('d');

            Timer.player = player.speed;
        }



        if (!Event.pause and !GameLife.active) {
            if (Event.mode == Panic) Timer.panic--;
            Game.timer++;
            Game.tick = (2 / (Game.timer)) * 10000000;
            Timer.crims--;
            Timer.phantom--;
            Timer.moss--;
            if (!player.active) Timer.fun--;
            Timer.infection--;
            if (Game.timer >= 1000000)
            {
                Game.timer -= Round(Game.timer - (Game.timer / 2));
            }
        }
        if (!Event.pause and GameLife.active) Timer.life--;
        Timer.player--;
    }
}



void GameInit() {
    BaseEntityInit();
    Game.objects.second = { player, crims, phantom, moss };
    Timers t(player, crims, phantom, moss);
    Timer = t;
    CommandGenerate();
    Sounds.GameStart();
    Field_Comporator(classic_map, classic_pos);
    Modals.Init();
    FieldOut();
    GamePlay();
}

void WorldInit() {
    BaseConsoleGameInit();
    BaseObjectsInit();
    map_coding = { {0, plate}, {1, token}, {2, wall}, {3, phantwall}, {4, torch}, {5, tabl}, {6, bush} };
    BaseEntityInit();
    Game.objects = { {plate, token, fruit, tabl, bush, phantwall, wall, torch, mycelium, mushroom}, { player, crims, phantom, moss } };
    BaseGameLifeInit();
}

void main() {
    WorldInit();
    GameInit();
}