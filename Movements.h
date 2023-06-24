#pragma once
#include "Python.h"
#include "DataPack.h"



#pragma region MicroFuncs

vector<int> Occurate(vector<int> pos) {
    return { pos[0] + 1 + Modals.field_pos.y, pos[1] * 2 + 1 + Modals.field_pos.x };
}

Object ObjFindName(string name) {
    for (auto& i : Game.objects.first)
    {
        if (i.name == name)
        {
            return i;
        }
    }
    return plate;
}

int NormLine(int num, char line) {
    if (num < 0 and line == 'y')
    {
        num = Game.y;
    }
    else if (num < 0 and line == 'x')
    {
        num = Game.x;
    }
    else if (num > Game.y and line == 'y')
    {
        num = 0;
    }
    else if (num > Game.x and line == 'x')
    {
        num = 0;
    }
    return num;
}

void UpdateFieldObject(Object obj) {
    for (int i = 0; i < Game.y + 1; i++)
    {
        for (int j = 0; j < Game.x + 1; j++)
        {
            if (obj.id == Game.field[i][j].id)
            {
                Game.field[i][j] = obj;
            }
        }
    }
    Game.objects.first[obj.id] = obj;
}

void ReplaceObj(int y, int x, Object obj) {
    bool light = !Event.night;
    if (Event.night) light = Game.field[y][x].lighted;
    Game.field[y][x] = obj;
    Game.field[y][x].lighted = light;
}

Object FieldPos(Pos pos) {
    return Game.field[pos.y][pos.x];
}

void SetFieldPos(int y, int x) {
    vector<int> vec = Occurate({ y, x });
    SetPos(vec[Y], vec[X]);
}

#pragma endregion



#pragma region OutPut

// Object Fore Edit
void OFE(Object obj, vector<int> vec, bool paint) { // y, x
    SetFieldPos(vec[Y], vec[X]);
    if (!paint)  ForePrint(obj.icon, obj.color, obj.back_color);
    else ForePrint(obj.icon, obj.color, "LIGHT RED");
}

// Entity Fore Edit
void EFE(Entity obj, Pos pos) {
    SetFieldPos(pos.y, pos.x);
    ForePrint(obj.icon, obj.color, obj.point.back_color);
}


void Field_GameActive() {
    Modal modal;
    string text = "Game Playing";
    if (Game.score >= 15000) text = "Game Win!";
    else if (player.die) text = "Game Lose!";
    else if (Event.pause) text = "Game Paused";
    else if (!player.active) text = "Heh, and where";

    Modals.game_active_pos.x = Modals.field_pos.x + Game.x - (size(text) / 2);
    modal.CreateModal(text, 1, 1, false, "LIGHT RED");

    SetConsoleCursorPosition(hand, { short(0), short(Modals.game_active_pos.y) });
    for (int i = 0; i < Modals.field_pos.x + Game.x * 2; i++) cerr << ' ';

    modal.OutContent(Modals.game_active_pos);


    SetConsoleCursorPosition(hand, { short(Modals.field_pos.x + 2), short(Modals.field_pos.y - 2) });
    ForePrint("Score: " + Str(Round(Game.score)), "LIGHT YELLOW");


    text = "";
    for (auto& i : Range(0, fruit.collected)) text += fruit.icon + " ";
    SetConsoleCursorPosition(hand, { short(Game.x - 2), short(Modals.game_active_pos.y - 2) });
    ForePrint(text, fruit.color);
}

void Field_Show_Pos() {
    if (Setups.show_pos)
    {
        Modal modal;
        string point = Str((char)249);
        modal.CreateModal("\nPosition (x | y):\n", 1, 1, false, "LIGHT RED");
        modal.SetFrameColor("LIGHT RED");
        modal.In(point + " Player Pos: " + Str(player.pos.x) + " | " + Str(player.pos.y) + "\n");
        modal.In(point + " Crims Pos: " + Str(crims.pos.x) + " | " + Str(crims.pos.y) + "\n");
        modal.In(point + " Phantom Pos: " + Str(phantom.pos.x) + " | " + Str(phantom.pos.y) + "\n");

        modal.Out(Modals.show_pos_pos);
    }
}

void Field_Show_Params() {
    if (Setups.show_params)
    {
        Modal modal;
        string point = Str((char)249);
        modal.CreateModal("\nParametrs:   \n", 1, 1, false, "LIGHT RED");
        modal.In(point + " Game Time: " + Str(Game.timer) + "\n");
        modal.In(point + " Tokens: " + Str(Game.objects.first[token.id].collected) + "\n");
        modal.In(point + " Tokens: " + Str(Game.objects.first[fruit.id].collected) + "\n");
        modal.In(point + " Player Speed: " + Str(player.speed) + "\n");
        modal.In(point + " Crims Speed : " + Str(crims.speed) + "\n");
        modal.In(point + " Phantom Speed: " + Str(phantom.speed) + "\n");

        modal.Out(Modals.show_params_pos);
    }
}

void FieldUpdate() {
    Field_Show_Pos();
    Field_Show_Params();
    Field_GameActive();
}

void FieldOut(int pick_y, int pick_x) {
    FieldUpdate();

    Modal field;
    string text;
    for (auto& i : Range(0, Game.y + 1)) {
        for (auto& i : Range(0, Game.x)) text += "  ";
        text += " \n";
    }
    field.CreateModal(text, 1, 2, true);
    field.OutFrame(Modals.field_pos);

    for (int i = 0; i < Game.y + 1; i++) {
        SetConsoleCursorPosition(hand, { short(1 + Modals.field_pos.x), short(1 + Modals.field_pos.y + i) });
        for (int j = 0; j < Game.x + 1; j++) {
            if (Event.pause and ((j == pick_x and pick_y == 1000) or (i == pick_y and pick_x == 1000) or (i == pick_y and j == pick_x))){
                ForePrint(Game.field[i][j].icon, Game.field[i][j].color, "LIGHT RED");
                SpaceOut(j, i, pick_y != 1000);
            }
            else if (!Event.night or (Event.night and Game.field[i][j].lighted)) {
                ForePrint(Game.field[i][j].icon, Game.field[i][j].color, Game.field[i][j].back_color);
                SpaceOut(i, j);
            }
            else {
                ForePrint(" ");
                if (j < Game.x) ForePrint(" ");
            }
        }
        ForePrint("\n");
    }

    if (!GameLife.active)
    {
        if ((Game.field[player.pos.y][player.pos.x].lighted or !Event.night) and player.active)
            EFE(player, player.pos);
        if ((Game.field[crims.pos.y][crims.pos.x].lighted or !Event.night) and crims.active)
            EFE(crims, crims.pos);
        if ((Game.field[phantom.pos.y][phantom.pos.x].lighted or !Event.night) and phantom.active)
            EFE(phantom, phantom.pos);
        if ((Game.field[moss.pos.y][moss.pos.x].lighted or !Event.night) and moss.active)
            EFE(moss, moss.pos);
    }
}


void SpaceOut(int y, int x, bool pause) {
    if (x < Game.x) {
        Object obj = Game.field[y][x];
        Object obj2 = Game.field[y][x+1];

        if (obj.wall == 0 or obj2.wall == 0)
        {
            if (pause) ForePrint(" ", "BLACK", "LIGHT RED");
            else ForePrint(" ");
        }
        else
        {
            if (obj.wall >= obj2.wall)
            {
                if (pause) ForePrint(obj.icon, obj.color, "LIGHT RED");
                else ForePrint(obj.icon, obj.color, obj.back_color);
            }
            else if (obj.wall <= obj2.wall)
            {
                if (pause) ForePrint(obj2.icon, obj2.color, "LIGHT RED");
                else ForePrint(obj2.icon, obj2.color, obj2.back_color);
            }
        }
    }
}

void SpaceOneObj(int y, int x, bool pause) {
    Object obj0 = Game.field[y][Collapse(x - 1, {0, Game.x})];
    Object obj1 = Game.field[y][Collapse(x, { 0, Game.x })];
    Object obj2 = Game.field[y][Collapse(x + 1, { 0, Game.x })];

    vector<int> vec = Occurate({ y, x });
    SetConsoleCursorPosition(hand, { short(vec[X]-1), short(vec[Y]) });

    if (0 < x) {
        string color = "LIGHT RED";
        if (obj0.wall == 0 or obj1.wall == 0) {
            if (!pause) color = "BLACK";
            ForePrint(" ", "BLACK", color);
        }
        else if (obj0.wall >= obj1.wall) {
            if (!pause) color = obj0.back_color;
            ForePrint(obj0.icon, obj0.color, color);
        }
        else if (obj0.wall <= obj1.wall) {
            if (!pause) color = obj1.back_color;
            ForePrint(obj1.icon, obj1.color, color);
        }
    }

    SetConsoleCursorPosition(hand, { short(vec[X] + 1), short(vec[Y]) });

    if (x < Game.x) {
        string color = "LIGHT RED";
        if (obj1.wall == 0 or obj2.wall == 0) {
            if (!pause) color = "BLACK";
            ForePrint(" ", "BLACK", color);
        }
        else if (obj1.wall >= obj2.wall) {
            if (!pause) color = obj1.back_color;
            ForePrint(obj1.icon, obj1.color, color);
        }
        else if (obj1.wall <= obj2.wall) {
            if (!pause) color = obj2.back_color;
            ForePrint(obj2.icon, obj2.color, color);
        }
    }
}


bool InVec(int a, vector<int> vec) {
    for (auto& i : vec) if (i == a) return true;
    return false;
}

#pragma endregion



void Infection() {
    for (int i = 1; i < Game.y; i++) for (int j = 1; j < Game.x; j++)
        {
            if (Game.field[i][j].virus)
            {
                Object virus = Game.field[i][j];
                if (rand() % 100 <= virus.virus_chance) {
                    switch (rand() % 4) {
                    case 0:
                        if (!Game.field[i - 1][j].wall) {
                            if (Game.movfield[i-1][j].id == uplate.id) OFE(virus, {i - 1, j});
                            ReplaceObj(i - 1, j, virus);
                            SpaceOneObj(i - 1, j);
                        }
                        break;

                    case 1:
                        if (!Game.field[i][j - 1].wall) {
                            if (Game.movfield[i - 1][j].id == uplate.id) OFE(virus, { i, j - 1 });
                            ReplaceObj(i, j - 1, virus);
                            SpaceOneObj(i, j - 1);
                        }
                        break;

                    case 2:
                        if (!Game.field[i + 1][j].wall) {
                            if (Game.movfield[i - 1][j].id == uplate.id) OFE(virus, { i + 1, j });
                            ReplaceObj(i + 1, j, virus);
                            SpaceOneObj(i + 1, j);
                        }
                        break;

                    case 3:
                        if (!Game.field[i][j + 1].wall) {
                            if (Game.movfield[i - 1][j].id == uplate.id) OFE(virus, { i, j + 1 });
                            ReplaceObj(i, j + 1, virus);
                            SpaceOneObj(i, j + 1);
                        }
                        break;

                    default:
                        break;
                    }
                }
            }
        }
}

void BakeLight() {
    for (int y = 0; y <= Game.y; y++) for (int x = 0; x <= Game.x; x++) Game.field[y][x].lighted = false;

    for (int y = 0; y <= Game.y; y++) for (int x = 0; x <= Game.x; x++)
        if (Game.field[y][x].light_source) {
            int light_range = Game.field[y][x].light_power;

            for (int i = Collapse(y - light_range, { 0, Game.y }); i <= Collapse(y + light_range, { 0, Game.y }); i++)
                for (int j = Collapse(x - light_range, { 0, Game.x }); j <= Collapse(x + light_range, { 0, Game.x }); j++)
                    if (0 <= i <= Game.y and 0 <= j <= Game.x) Game.field[i][j].lighted = true;
        }
}



#pragma region GameLife

vector<vector<int>> LifeMapInit(int y, int x) {
    srand(time(NULL));
    vector<vector<int>> vec;
    for (int i = 0; i < y; i++) {
        vector<int> temp;
        for (int j = 0; j < x; j++)
        {
            if (rand() % 2) temp.push_back(GameLife.zero_obj.id);
            else temp.push_back(GameLife.one_obj.id);
        }
        vec.push_back(temp);
    }
    return vec;
}

int AmountOfNeighbours(int y, int x) {
    int amount = 0;
    for (int i = y-1; i <= y+1; i++) for (int j = x-1; j <= x+1; j++) {
                if (i >= 0 and i <= Game.y and j >= 0 and j <= Game.x and !(i == y and j == x))
                {
                    if (Game.field[i][j].id == GameLife.one_obj.id) amount++;
                }
            }
    return amount;
}

void SimulateLife() {
    vector<vector<Object>> new_field;

    for (int i = 0; i < Game.y+1; i++) {
        vector<Object> temp;
        for (int j = 0; j < Game.x+1; j++) {
            int amount = AmountOfNeighbours(i, j);

            if (InVec(amount, GameLife.birth_rule)) {
                temp.push_back(GameLife.one_obj);
                OFE(GameLife.one_obj, { i, j });
                SpaceOut(i, j);
            }
            else if (InVec(amount, GameLife.life_rule)) temp.push_back(Game.field[i][j]);
            else {
                temp.push_back(GameLife.zero_obj);
                OFE(GameLife.zero_obj, { i, j });
                SpaceOut(i, j);
            }
        }
        new_field.push_back(temp);
    }
    Game.field = new_field;
}

#pragma endregion



#pragma region Movement

struct CrimsMove {
public:
    void Move() {
        srand(time(NULL));
        path = { {'y', 0, -1, 0, Game.field[Game.y][crims.pos.x].cr_avalb}, {'x', 0, 0, -1, Game.field[crims.pos.y][Game.x].cr_avalb}, {'y', Game.y, 1, 0, Game.field[0][crims.pos.x].cr_avalb}, {'x', Game.x, 0, 1, Game.field[crims.pos.y][0].cr_avalb} };
        if (crims.die)
        {
            crims.target = { {'y', crims.start_pos.y}, {'x', crims.start_pos.x} };
        }
        else if (Event.mode == Pursuit)
        {
            crims.target = { {'y', player.pos.y}, {'x', player.pos.x} };
        }
        else if (Event.mode == Scatter)
        {
            crims.target = { {'y', 1}, {'x', 1} };
        }
        else if (Event.mode == Panic)
        {
            Go(rand() % 4);
            if (crims.pos.Conside(player.pos) and Event.mode == Panic and !crims.die)  Die();
            if (crims.pos.Conside(crims.start_pos) and crims.die) Restart();
            Game.movfield[crims.pos.y][crims.pos.x] = crims;
            return;
        }


        int diff_x = Mod(crims.target['x'] - crims.pos.x) + 1;
        int diff_y = Mod(crims.target['y'] - crims.pos.y) + 1;
        bool plane;
        if (diff_x >= diff_y) { plane = diff_x / diff_y <= 2; }
        else { plane = diff_y / diff_x >= 2; }



        if ((crims.target['y'] == crims.pos.y) and (crims.target['x'] == crims.pos.x))
        {
            Go(rand() % 4);
        }
        else if (plane) {
        y_move:
            if ((crims.target['y'] < crims.pos.y))
            {
                Go(Up);
            }
            else if ((crims.target['y'] > crims.pos.y))
            {
                Go(Down);
            }
            else { goto x_move; }
        }
        else {
        x_move:
            if ((crims.target['x'] < crims.pos.x))
            {
                Go(Left);
            }
            else if ((crims.target['x'] > crims.pos.x))
            {
                Go(Right);
            }
            else { goto y_move; }
        }


        if (crims.pos.Conside(player.pos) and Event.mode == Panic)  Die();
        if (crims.pos.Conside(crims.start_pos)) Restart();
        Game.movfield[crims.pos.y][crims.pos.x] = crims;
    }

    void Die() {
        if (!crims.die)
        {
            crims.die = !crims.die;
            crims.speed /= 1.5;
            crims.color = "LIGHT RED";
            Sounds.CrimsDie();
        }
    }

    void Restart() {
        if (crims.die)
        {
            crims.die = !crims.die;
            crims.speed *= 1.5;
            crims.color = "RED";
        }
    }

    void CursoreMove(Pos point_pos, Object point) {
        if (crims.point.lighted or !Event.night)
        {
            OFE(crims.point, {crims.pos.y, crims.pos.x});
        }
        crims.point = point;
        if (point.lighted or !Event.night) EFE(crims, point_pos);
        Field_Show_Pos();
    }

private:
    vector<vector<int>> path;
    int cycle = 0;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos = Posit({ NormLine(crims.pos.y + vec[2], 'y'), NormLine(crims.pos.x + vec[3], 'x') });
        Object point = Game.field[point_pos.y][point_pos.x];

        if ((point.cr_avalb or crims.die) and !crims.last_point.Conside(point_pos)) {
            CursoreMove(point_pos, point);
            Game.movfield[crims.pos.y][crims.pos.x] = uplate;
            crims.last_point = crims.pos;
            crims.pos = point_pos;
            cycle = 0;
        }
        else if (cycle >= 4) {}
        else { path_num += 1; path_num = Loop(path_num, { Up, Right }); cycle++;  Go(path_num); return; }
    }
} crims_move;

struct PhantomMove {
public:
    void Move() {
        srand(time(NULL));
        path = { {phantom.pos.y, 0, -1, 0}, {phantom.pos.x, 0, 0, -1}, {phantom.pos.y, Game.y, 1, 0}, {phantom.pos.x, Game.x, 0, 1} };

        if (phantom.die)
        {
            phantom.target = { {'y', phantom.start_pos.y}, {'x', phantom.start_pos.x} };
        }
        else if (Event.mode == Pursuit)
        {
            phantom.target = { {'y', player.pos.y}, {'x', player.pos.x} };
        }
        else if (Event.mode == Scatter)
        {
            phantom.target = { {'y', Game.y - 1}, {'x', Game.x - 1} };
        }
        else if (Event.mode == Panic)
        {
            vector<vector<int>> corns{ {1, 1}, { Game.y - 1, 1 }, { Game.y - 1, Game.x - 1 }, { 1, Game.x - 1 } };
            int min = Mod(phantom.pos.y - corns[0][0]) + Mod(phantom.pos.x - corns[0][1]);
            int min_num = 0;
            for (int i = 0; i < size(corns); i++)
            {
                if (Mod(phantom.pos.y - corns[i][0]) + Mod(phantom.pos.x - corns[i][1]) < min)
                {
                    min = Mod(phantom.pos.y - corns[i][0]) + Mod(phantom.pos.x - corns[i][1]);
                    min_num = i;
                }
            }
            phantom.target = { {'y', corns[min_num][0]}, {'x', corns[min_num][1]} };

            int diff_x = Mod(player.pos.x - phantom.pos.x);
            int diff_y = Mod(player.pos.y - phantom.pos.y);
            if (diff_x + diff_y <= 10)
            {
                if (min_num == 3)
                {
                    min_num = 0;
                }
                else
                {
                    min_num++;
                }
                phantom.target = { {'y', corns[min_num][0]}, {'x', corns[min_num][1]} };
            }
        }

        int diff_x = Mod(phantom.target['x'] - phantom.pos.x) + 1;
        int diff_y = Mod(phantom.target['y'] - phantom.pos.y) + 1;
        bool plane;
        if (diff_x >= diff_y) { plane = diff_x / diff_y < 2; }
        else if (diff_x < diff_y) { plane = diff_y / diff_x > 2; }



        if ((phantom.target['y'] == phantom.pos.y) and (phantom.target['x'] == phantom.pos.x))
        {
            Go(rand() % 4);
        }
        else if (plane) {
        y_move:
            if (phantom.target['y'] < phantom.pos.y)
            {
                Go(Up);
            }
            else if (phantom.target['y'] > phantom.pos.y)
            {
                Go(Down);
            }
            else { goto x_move; }
        }
        else {
        x_move:
            if (phantom.target['x'] < phantom.pos.x)
            {
                Go(Left);
            }
            else if (phantom.target['x'] > phantom.pos.x)
            {
                Go(Right);
            }
            else { goto y_move; }
        }


        if (phantom.pos.Conside(player.pos) and Event.mode == Panic)  Die();
        if (phantom.pos.Conside(phantom.start_pos)) Restart();
        Game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
    }

    void Die() {
        if (!phantom.die)
        {
            phantom.speed /= 2, 5;
            phantom.color = "LIGHT MAGENTA";
            phantom.die = true;
            Sounds.PhantomDie();
        }
    }

    void Restart() {
        if (phantom.die)
        {
            phantom.speed *= 2, 5;
            phantom.color = "MAGENTA";
            phantom.die = false;
        }
    }

    void CursoreMove(Pos point_pos, Object point) {
        if (phantom.point.lighted or !Event.night)
        {
            OFE(phantom.point, { phantom.pos.y, phantom.pos.x });
            OFE(phantom.point, { phantom.pos.y, phantom.pos.x });
        }
        phantom.point = point;
        if (point.lighted or !Event.night) EFE(phantom, point_pos);
        FieldUpdate();
    }

private:
    vector<vector<int>> path;
    int cycle = 0;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos = Posit({ NormLine(phantom.pos.y + vec[2], 'y'), NormLine(phantom.pos.x + vec[3], 'x') });
        Object point = Game.field[point_pos.y][point_pos.x];

        if (point.ph_avalb) {
            if (point.lighted or !Event.night) CursoreMove(point_pos, point);
            Game.movfield[phantom.pos.y][phantom.pos.x] = uplate;
            phantom.pos = point_pos;
        }
        else if (cycle >= 4) {}
        else { path_num += 1; path_num = Loop(path_num, { 0, 3 }); cycle++;  Go(path_num); return; }
    }
} phantom_move;

struct MossMove {
public:
    void Move() {
        srand(time(NULL));
        path = { {'y', 0, -1, 0, Game.field[Game.y][moss.pos.x].cr_avalb}, {'x', 0, 0, -1, Game.field[moss.pos.y][Game.x].cr_avalb}, {'y', Game.y, 1, 0, Game.field[0][moss.pos.x].cr_avalb}, {'x', Game.x, 0, 1, Game.field[moss.pos.y][0].cr_avalb} };
        if (moss.die)
        {
            moss.target = { {'y', moss.start_pos.y}, {'x', moss.start_pos.x} };
        }
        else if (Event.mode == Pursuit)
        {
            moss.target = { {'y', player.pos.y}, {'x', player.pos.x} };
        }
        else if (Event.mode == Scatter)
        {
            moss.target = { {'y', 1}, {'x', Game.x-1} };
        }
        else if (Event.mode == Panic)
        {
            Go(rand() % 4);
            if (moss.pos.Conside(player.pos) and Event.mode == Panic and !moss.die)  Die();
            if (moss.pos.Conside(moss.start_pos) and moss.die) Restart();
            Game.movfield[moss.pos.y][moss.pos.x] = moss;
            return;
        }


        int diff_x = Mod(moss.target['x'] - moss.pos.x) + 1;
        int diff_y = Mod(moss.target['y'] - moss.pos.y) + 1;
        bool plane;
        if (diff_x >= diff_y) { plane = diff_x / diff_y <= 2; }
        else { plane = diff_y / diff_x >= 2; }



        if ((moss.target['y'] == moss.pos.y) and (moss.target['x'] == moss.pos.x))
        {
            Go(rand() % 4);
        }
        else if (plane) {
        y_move:
            if ((moss.target['y'] < moss.pos.y))
            {
                Go(Up);
            }
            else if ((moss.target['y'] > moss.pos.y))
            {
                Go(Down);
            }
            else { goto x_move; }
        }
        else {
        x_move:
            if ((moss.target['x'] < moss.pos.x))
            {
                Go(Left);
            }
            else if ((moss.target['x'] > moss.pos.x))
            {
                Go(Right);
            }
            else { goto y_move; }
        }


        if (moss.pos.Conside(player.pos) and Event.mode == Panic)  Die();
        if (moss.pos.Conside(moss.start_pos)) Restart();
        Game.movfield[moss.pos.y][moss.pos.x] = moss;
    }

    void Die() {
        if (!moss.die)
        {
            moss.die = !moss.die;
            moss.speed /= 1.5;
            moss.color = "LIGHT GREEN";
            Sounds.CrimsDie();
        }
    }

    void Restart() {
        if (moss.die)
        {
            moss.die = !moss.die;
            moss.speed *= 1.5;
            moss.color = "GREEN";
        }
    }

    void CursoreMove(Pos point_pos, Object point) {
        if (moss.point.lighted or !Event.night)
        {
            OFE(moss.point, { moss.pos.y, moss.pos.x });
        }
        moss.point = point;
        if (point.lighted or !Event.night) EFE(moss, point_pos);
        Field_Show_Pos();
    }

private:
    vector<vector<int>> path;
    int cycle = 0;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos = Posit({ NormLine(moss.pos.y + vec[2], 'y'), NormLine(moss.pos.x + vec[3], 'x') });
        Object point = Game.field[point_pos.y][point_pos.x];

        if ((point.cr_avalb or moss.die) and !moss.last_point.Conside(point_pos)) {
            CursoreMove(point_pos, point);
            Game.movfield[moss.pos.y][moss.pos.x] = uplate;
            moss.last_point = moss.pos;
            moss.pos = point_pos;
            cycle = 0;
        }
        else if (cycle >= 4) {}
        else { path_num += 1; path_num = Loop(path_num, { Up, Right }); cycle++;  Go(path_num); return; }
    }
} moss_move;

struct PlayerMove {
public:
    void Move(char dir) {
        if (!Event.pause)
        {
            path = { {player.pos.y, 0, Game.y, -1, 0}, {player.pos.x, 0, Game.x, 0, -1}, {player.pos.y, Game.y, 0, 1, 0}, {player.pos.x, Game.x, 0, 0, 1} };

            int num = dir;
            if (num == 224) {}
            else if (num == 119 or num == 72 or num == -26 or num == 87) Go(Up);
            else if (num == 97 or num == 75 or num == -28 or num == 65) Go(Left);
            else if (num == 115 or num == 80 or num == -21 or num == 83) Go(Down);
            else if (num == 100 or num == 77 or num == -94 or num == 68) Go(Right);

            if (!crims.die) if (player.pos.Conside(crims.pos) and Event.mode == Panic and !crims.die)  crims_move.Die();
            if (!phantom.die) if (player.pos.Conside(phantom.pos) and Event.mode == Panic and !phantom.die)  phantom_move.Die();
            Game.movfield[player.pos.y][player.pos.x] = player;
        }

        switch (dir)
        {
        case ' ':
            Event.pause = !Event.pause;
            FieldOut();
            Field_GameActive();
            break;

        case 'e':
            if (Event.pause)
            {
                CommandInput();
            }
            break;

        default:
            break;
        }
    }

    void CursoreMove(Pos point_pos, Object point) {
        if (player.point.collectable or (!player.point.lighted and Event.night))
        {
            OFE(plate, { player.pos.y, player.pos.x });
        }
        else OFE(player.point, { player.pos.y, player.pos.x });

        player.point = point;
        EFE(player, point_pos);
        FieldUpdate();
    }

    void Collect(Object& point) {
        point.collected += 1;
        UpdateFieldObject(point);
        Game.objects.first[point.id].collected += 1;
        Game.score += point.cost * Game.tick + point.cost;

        if (point.id == tabl.id) { Event.ToPanic(); Sounds.Tabl(); }
        else if (point.id == fruit.id) { Sounds.Fruit(); }
        else if (point.name == "error") Sounds.Error();
        else if (point.id == bush.id) {
            Event.ToScatter();
            if (Game.field[player.last_point.y][player.last_point.x].id != bush.id) Sounds.Bush();
        }
        if (point.id != bush.id and player.point.id == bush.id) { Event.ToUnScatter(); Sounds.NoBush(); }
    }

private:
    vector<vector<int>> path;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos = Posit({ NormLine(player.pos.y + vec[3], 'y'), NormLine(player.pos.x + vec[4], 'x') });
        Object* point = &Game.field[point_pos.y][point_pos.x];

        if ((*point).pl_avalb) {
            CursoreMove(point_pos, *point);
            Game.movfield[player.pos.y][player.pos.x] = uplate;
            if (player.point.collectable) ReplaceObj(player.pos.y, player.pos.x, plate);

            player.pos = point_pos;
            Game.movfield[player.pos.y][player.pos.x] = player;
            Collect(*point);
        }
        else if ((*point).name == "error") Sounds.Error();
    }
} player_move;

#pragma endregion



#pragma region Commands

void CommandGenerate() {
    commands = {};


    for (auto& i : Game.objects.first)
    {
        commands.push_back("spawn_" + i.name + "=[x,y]");
        commands.push_back("spawn_" + i.name + "_x" + "=[x]");
        commands.push_back("spawn_" + i.name + "_y" + "=[y]");
    }

    commands.push_back("replace_all=[replacement]");
    for (auto& i : Game.objects.first)  commands.push_back("replace_" + i.name + "=" + "[replacer_name]");
    for (auto& i : Game.objects.second)  commands.push_back("place_" + i.name + "=[y,x]");


    vector<string> active{ "freeze", "crims", "phantom", "moss", "player", "night" };
    for (auto& i : active)  commands.push_back("active_" + i + "=(true or false)");
    commands.push_back("active_mode=(pursuit or scatter or panic)");

    vector<string> set{ "tokens", "fruits", "speed", "player_speed", "crims_speed", "phantom_speed", "moss_speed" };
    for (auto& i : set)  commands.push_back("set_" + i + "=[int]");

    commands.push_back("show_pos=(true or false)");
    commands.push_back("show_params=(true or false)");


    commands.push_back("mod_create=(true or false)");
    if (Mods.create)
    {
        commands.push_back("mod_create_obj=(item, name, color, back_color)");
        for (auto& i : Game.objects.first)
        {
            commands.push_back("mod_create_edit_params_" + i.name + "=" + "(icon, name, color, back_color)");
            commands.push_back("mod_create_edit_light_" + i.name + "=" + "(lighting, light_power)");
            commands.push_back("mod_create_edit_avalb_" + i.name + "=" + "(iswall, pl_avalb, cr_avalb, ph_avalb)");
            commands.push_back("mod_create_edit_virus_" + i.name + "=" + "(virus, virus_chance)");
            commands.push_back("mod_create_edit_cost_" + i.name + "=" + "(collectable, cost)");
        }
    }
    commands.push_back("mod_gamelife=(true or false)");
    if (Mods.gamelife)
    {
        commands.push_back("mod_gamelife_active=(true or false)");
        commands.push_back("mod_gamelife_speed=(int)");
        commands.push_back("mod_gamelife_zero_obj=(object)");
        commands.push_back("mod_gamelife_one_obj=(object)");
        commands.push_back("mod_gamelife_birth_rule=(nums)");
        commands.push_back("mod_gamelife_life_rule=(nums)");
    }
}

void CommandTab(string command) {
    vector<string> vec = Split(Connect(Split(command, "="), "_"), "_");

    if (size(vec[size(vec) - 1]) != 0)
    {
        if (vec[0] == "spawn")
        {
            vector<string> params = Split(vec[size(vec) - 1], ",");
            if (vec[2] == "x") { params.push_back("1000"); }
            if (vec[2] == "y") { 
                params.push_back(params[0]);
                params[0] = "1000";
            }

            Object spawned = ObjFindName(vec[1]);

            if (vec[2] == "x") {
                for (int i = 0; i < Game.y + 1; i++) {
                    Game.field[i][Int(params[0])] = spawned;
                }
            }
            else if (vec[2] == "y") {
                for (int i = 0; i < Game.x + 1; i++) {
                    Game.field[Int(params[1])][i] = spawned;
                }
            }
            else {
                Game.field[Int(params[1])][Int(params[0])] = spawned;
            }

            BakeLight();
            FieldOut(Int(params[1]), Int(params[0]));
        }
        else if (vec[0] == "replace") {
            Object replaced = ObjFindName(vec[1]);
            Object replacer = ObjFindName(vec[size(vec) - 1]);

            for (int y = 0; y < Game.y + 1; y++) {
                for (int x = 0; x < Game.x + 1; x++) {
                    if (vec[1] == "all") {
                        Game.field[y][x] = replacer;
                    }
                    else if (Game.field[y][x].id == replaced.id) {
                        Game.field[y][x] = replacer;
                    }
                }
            }
            if (vec[1] == "all") {
                player.point = plate;
                crims.point = plate;
                phantom.point = plate;
            }
            BakeLight();
            FieldOut();
        }
        else if (vec[0] == "place")
        {
            vector<string> params = Split(vec[size(vec) - 1], ",");
            vector<int> point_pos = { Int(params[0]), Int(params[1]) };
            Object point = Game.field[Int(params[0])][Int(params[1])];

            if (vec[1] == "player") {
                player_move.CursoreMove(Posit(point_pos), point);
                Game.movfield[player.pos.y][player.pos.x] = uplate;
                if (player.point.collectable) ReplaceObj(player.pos.y, player.pos.x, plate);
                
                player.pos.y = Int(params[0]);
                player.pos.x = Int(params[1]);
                Game.movfield[player.pos.y][player.pos.x] = player;
                player_move.Collect(point);
            }
            else if (vec[1] == "crims") {
                crims_move.CursoreMove(Posit(point_pos), point);
                Game.movfield[crims.pos.y][crims.pos.x] = uplate;

                crims.pos.y = Int(params[0]);
                crims.pos.x = Int(params[1]);
                Game.movfield[crims.pos.y][crims.pos.x] = crims;
            }
            else if (vec[1] == "phantom") {
                phantom_move.CursoreMove(Posit(point_pos), point);
                Game.movfield[phantom.pos.y][phantom.pos.x] = uplate;

                phantom.pos.y = Int(params[0]);
                phantom.pos.x = Int(params[1]);
                Game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
            }
            else if (vec[1] == "moss") {
                moss_move.CursoreMove(Posit(point_pos), point);
                Game.movfield[moss.pos.y][moss.pos.x] = uplate;

                moss.pos.y = Int(params[0]);
                moss.pos.x = Int(params[1]);
                Game.movfield[moss.pos.y][moss.pos.x] = moss;
            }
        }
        else if (vec[0] == "active")
        {
            string param = vec[size(vec) - 1];

            if (vec[1] == "mode")
            {
                int par = Pursuit;
                if (param == "scatter") par = Scatter;
                else if (param == "panic") par = Panic;
                Event.mode = par;
            }
            else
            {
                bool par = Bool(param);
                if (vec[1] == "night")
                {
                    if (par == true)
                    {
                        Event.ToNight();
                    }
                    else
                    {
                        Event.ToUnNight();
                    }
                }
                else if (vec[1] == "freeze")
                {
                    Event.freeze = par;
                }
                else if (vec[1] == "crims")
                {
                    crims.active = par;
                    if (par)
                    {
                        Game.movfield[crims.pos.y][crims.pos.x] = crims;
                        EFE(crims, crims.pos);
                    }
                    else
                    {
                        Game.movfield[crims.pos.y][crims.pos.x] = uplate;
                        SetFieldPos(crims.pos.y, crims.pos.x);
                        cerr << ' ';
                    }
                }
                else if (vec[1] == "phantom")
                {
                    phantom.active = par;
                    if (par)
                    {
                        Game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
                        EFE(phantom, phantom.pos);
                    }
                    else
                    {
                        Game.movfield[phantom.pos.y][phantom.pos.x] = uplate;
                        SetFieldPos(phantom.pos.y, phantom.pos.x);
                        cerr << ' ';
                    }
                }
                else if (vec[1] == "moss")
                {
                    moss.active = par;
                    if (par)
                    {
                        Game.movfield[moss.pos.y][moss.pos.x] = moss;
                        EFE(moss, moss.pos);
                    }
                    else
                    {
                        Game.movfield[moss.pos.y][moss.pos.x] = uplate;
                        SetFieldPos(moss.pos.y, moss.pos.x);
                        cerr << ' ';
                    }
                }
                else if (vec[1] == "player")
                {
                    player.active = par;
                    if (par)
                    {
                        Game.movfield[player.pos.y][player.pos.x] = player;
                        EFE(player, player.pos);
                    }
                    else
                    {
                        Game.movfield[player.pos.y][player.pos.x] = uplate;
                        SetFieldPos(player.pos.y, player.pos.x);
                        cerr << ' ';
                    }
                }
            }
        }
        else if (vec[0] == "set")
        {
            if (vec[1] == "tokens")
            {
                token.collected = Int(vec[size(vec) - 1]);
                Game.score = (token.collected * token.cost) / ((Game.timer / 100000000) / 2);
                UpdateFieldObject(token);
            }
            else if (vec[1] == "fruits")
            {
                fruit.collected = Int(vec[size(vec) - 1]);
                Game.score = (fruit.collected * fruit.cost) / ((Game.timer / 100000000) / 2);
                UpdateFieldObject(fruit);
            }
            else if (vec[1] == "speed")
            {
                Game.speed = Int(vec[size(vec) - 1]);
                player.speed = (Game.speed / 100) * 25;
                crims.speed = (Game.speed / 100) * 50;
                phantom.speed = (Game.speed / 100) * 75;
            }
            else if (vec[1] == "player" and vec[2] == "speed")
            {
                player.speed = Int(vec[size(vec) - 1]);
            }
            else if (vec[1] == "crims" and vec[2] == "speed")
            {
                crims.speed = Int(vec[size(vec) - 1]);
            }
            else if (vec[1] == "phantom" and vec[2] == "speed")
            {
                phantom.speed = Int(vec[size(vec) - 1]);
            }
            else if (vec[1] == "moss" and vec[2] == "speed")
            {
                moss.speed = Int(vec[size(vec) - 1]);
            }

            FieldOut();
        }
        else if (vec[0] == "show")
        {
            bool param = Bool(vec[size(vec) - 1]);

            if (vec[1] == "pos")
            {
                Setups.show_pos = param;
                Field_Show_Pos();
            }
            else if (vec[1] == "params")
            {
                Setups.show_params = param;
                Field_Show_Params();
            }
        }
        else if (vec[0] == "mod")
        {
            if (vec[1] == "create")
            {
                if (Mods.create and vec[2] == "obj")
                {
                    vector<string> params = Split(vec[size(vec) - 1], ",");
                    Object block;

                    block.id = size(Game.objects.first);
                    block.icon = Char(params[0]);
                    block.name = params[1];
                    block.color = params[2];
                    block.back_color = params[3];

                    Game.objects.first.push_back(block);
                    CommandGenerate();
                }
                else if (Mods.create and vec[2] == "edit")
                {
                    Object block = ObjFindName(vec[4]);
                    if (vec[3] == "params")
                    {
                        vector<string> params = Split(vec[size(vec) - 1], ",");

                        block.icon = Char(params[0]);
                        block.name = params[1];
                        block.color = params[2];
                        block.back_color = params[3];
                    }
                    else if (vec[3] == "light")
                    {
                        vector<string> params = Split(vec[size(vec) - 1], ",");

                        block.light_source = Bool(params[0]);
                        block.light_power = Int(params[1]);
                    }
                    else if (vec[3] == "avalb")
                    {
                        vector<string> params = Split(vec[size(vec) - 1], ",");

                        block.wall = Int(params[0]);
                        block.pl_avalb = Bool(params[1]);
                        block.cr_avalb = Bool(params[2]);
                        block.ph_avalb = Bool(params[3]);
                    }
                    else if (vec[3] == "virus") {
                        vector<string> params = Split(vec[size(vec) - 1], ",");
                        map<string, int> rules{ {"None", 0}, { "UnderId", 1 }, { "UpperId", 2 }, { "All", 3 }, };

                        block.virus = Bool(params[0]);
                        block.virus_chance = Int(params[1]);
                    }
                    else if (vec[3] == "cost")
                    {
                        vector<string> params = Split(vec[size(vec) - 1], ",");

                        block.collectable = Bool(params[0]);
                        block.cost = Int(params[1]);
                    }

                    int num = 0;
                    for (int i = 0; i < size(Game.objects.first); i++)
                    {
                        if (Game.objects.first[i].name == vec[4])
                        {
                            num = i;
                        }
                    }
                    Game.objects.first[num] = block;
                    UpdateFieldObject(block);
                    FieldOut();
                }
                else
                {
                    Mods.create = Bool(vec[size(vec) - 1]);
                    CommandGenerate();
                }
            }
            else if (vec[1] == "gamelife")
            {
                if (Mods.gamelife)
                {
                    if (vec[2] == "active") GameLife.active = Bool(vec[size(vec) - 1]);
                    else if(vec[2] == "speed") GameLife.speed = Int(vec[size(vec) - 1]);
                    else if (vec[2] == "zero" and vec[3] == "obj") GameLife.zero_obj = ObjFindName(vec[size(vec) - 1]);
                    else if (vec[2] == "one" and vec[3] == "obj") GameLife.one_obj = ObjFindName(vec[size(vec) - 1]);

                    else if (vec[2] == "birth" and vec[3] == "rule")
                    {
                        GameLife.birth_rule = {};
                        for (auto& i : vec[size(vec) - 1]) { 
                            string a = ""; a += i;
                            GameLife.birth_rule.push_back(Int(a));
                        }
                    }
                    else if (vec[2] == "life" and vec[3] == "rule")
                    {
                        GameLife.life_rule = {};
                        for (auto& i : vec[size(vec) - 1]) {
                            string a = ""; a += i;
                            GameLife.life_rule.push_back(Int(a));
                        }
                    }
                    FieldOut();
                }
                else
                {
                    Mods.gamelife = Bool(vec[size(vec) - 1]);
                    CommandGenerate();
                }
            }
        }
    }
}

void CommandInput() {
    SetConsoleCursorPosition(hand, { short(Modals.field_pos.x), short(Modals.field_pos.y + Game.y + 3) });
    string command; ForePrint("Enter Command: ", "LIGHT RED");
    vector<string> maybe = { "" };
    while (true)
    {
        if (_kbhit())
        {
            SetConsoleCursorPosition(hand, { short(Modals.field_pos.x + size("Enter Command: ")), short(Modals.field_pos.y + Game.y + 3)});
            char button = _getch();
            int but_num = button;   
            if (but_num == 13)
            { 
                if (command.find('=') <= 100)
                {
                    break;
                }
                else
                {
                    maybe = Find(commands, command);
                    if (size(maybe) != 0)
                    {
                        string mb_command = "";
                        for (auto& i : maybe[0])
                        {
                            mb_command += i;
                            if (i == '=') { break; }
                        }
                        command = mb_command;
                    }
                }
            }
            else if (button == '\b') {
                if (size(command) != 0) command.pop_back();
            }
            else command += button;
            ForePrint(command, "LIGHT RED");

            SetConsoleCursorPosition(hand, { short(Modals.field_pos.x + size("Enter Command: ") + size(command)), short(Modals.field_pos.y + Game.y + 3) });
            if (size(maybe) != 0) for (int i = 0; i < size(maybe[0]) + 4; i++) cerr << ' ';

            SetConsoleCursorPosition(hand, { short(Modals.field_pos.x + size("Enter Command: ") + size(command)), short(Modals.field_pos.y + Game.y + 3) });
            vector<string> mmaybe = Find(commands, command);
            if (size(mmaybe) != 0) 
            {
                Fore("GRAY");
                maybe = mmaybe;
                cerr << "  ~" << maybe[0] << endl;
            }
        }
    }
    SetConsoleCursorPosition(hand, { short(Modals.field_pos.x), short(Modals.field_pos.y + Game.y + 3) });
    for (int i = 0; i < size(maybe[0]) + size("Enter Command: ") + size(command) + 4; i++) cerr << ' ';
    CommandTab(command);
}

#pragma endregion
