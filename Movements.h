#pragma once
#include "Python.h"
#include <algorithm>
using namespace std;
void Field_Out(int pick_x = 1000, int pick_y = 1000);
void Light_Generate();

int Occur_x(int x) {
    return x * 2 + 2;
}
int Occur_y(int y) {
    return y + 1;
}

#pragma region Initialization

enum Dirs {
    Up = 0,
    Left = 1,
    Down = 2,
    Right = 3
};
enum light {
    Dark = 0,
    Light = 1
};
enum Waves {
    ZeroWave = 0,
    FirstWave = 1,
    SecondWave = 2
};
enum Modes {
    Pursuit = 0,
    Scatter = 1,
    Panic = 2
};
enum VirusRules {
    None = 0,
    UnderId = 1,
    UpperId = 2,
    All = 3
};

class Pos {
public:
    int x;
    int y;
};

#pragma region Objects

class Object {
public:
    int id = 0;
    char icon = 'X';
    string name = "error";
    string color = "BLUE";
    string back_color = "BLACK";

    bool virus = false;
    int virus_chance = 50;
    int virus_rule = None;

    bool collectable = false;
    int cost = 0;
    int collected = 0;

    bool light_source = false;
    int light_power = 0;

    bool pl_avalb = false;
    bool cr_avalb = false;
    bool ph_avalb = false;


    void Init(string iname) {
        id = ids[iname];
        icon = icons[iname];
        name = iname;
        color = colors[iname];
        back_color = back_colors[iname];

        virus = viruses[iname];
        int virus_chance = virus_chances[iname];

        collectable = collectables[iname];
        cost = costs[iname];

        light_source = light_sources[iname];
        light_power = light_powers[iname];

        pl_avalb = pl_avalbs[iname];
        cr_avalb = cr_avalbs[iname];
        ph_avalb = ph_avalbs[iname];
    }
private:
    map<string, int> ids{ {"plate", 0},       {"token", 1},     {"fruit", 2},     {"tabl", 3},     {"bush", 4},     {"phantwall", 5},     {"wall", 6},     {"torch", 7} };
    map<string, char> icons{ {"plate", ' '},     {"token", 249},   {"fruit", 15},    {"tabl", 4},     {"bush", 177},     {"phantwall", 254},    {"wall", 254},   {"torch", 5} };
    map<string, string> back_colors{ {"plate", "BLACK"}, {"token", "BLACK"},        {"fruit", "BLACK"},     {"tabl", "BLACK"}, {"bush", "BLACK"},   {"phantwall", "LIGHT RED"}, {"wall", "LIGHT BLUE"}, {"torch", "BLACK"} };
    map<string, string> colors{ {"plate", "BLACK"}, {"token", "LIGHT YELLOW"}, {"fruit", "LIGHT RED"}, {"tabl", "WHITE"}, {"bush", "LIGHT CYAN"}, {"phantwall", "LIGHT RED"},  {"wall", "LIGHT BLUE"}, {"torch", "YELLOW"} };

    map<string, bool> viruses{ {"plate", false},   {"token", false}, {"fruit", false}, {"tabl", false}, {"bush", true}, {"phantwall", false}, {"wall", false}, {"torch", false} };
    map<string, int> virus_chances{ {"plate", 0},   {"token", 0}, {"fruit", 0}, {"tabl", 0}, {"bush", 50}, {"phantwall", 0}, {"wall", 0}, {"torch", 0} };
    map<string, int> virus_rules{ {"plate", None},   {"token", UnderId}, {"fruit", None}, {"tabl", None}, {"bush", UnderId}, {"phantwall", None}, {"wall", None}, {"torch", None} };

    map<string, bool> collectables{ {"plate", false}, {"token", true}, {"fruit", true}, {"tabl", true}, {"bush", false}, {"phantwall", false}, {"wall", false}, {"torch", false} };
    map<string, int> costs{ {"plate", 0}, {"token", 1}, {"fruit", 20}, {"tabl", 0}, {"bush", 0}, {"phantwall", 0},   {"wall", 0}, {"torch", 0} };

    map<string, bool> light_sources{ {"plate", false},   {"token", false}, {"fruit", false}, {"tabl", false}, {"bush", false}, {"phantwall", false}, {"wall", false}, {"torch", true} };
    map<string, int> light_powers{ {"plate", 0},       {"token", 0},     {"fruit", 0},     {"tabl", 0},     {"bush", 0},  {"phantwall", 0},   {"wall", 0},   {"torch", 5} };

    map<string, bool> pl_avalbs{ {"plate", true}, {"token", true}, {"fruit", true}, {"tabl", true}, {"bush", true}, {"phantwall", false}, {"wall", false}, {"torch", false} };
    map<string, bool> cr_avalbs{ {"plate", true}, {"token", true}, {"fruit", true}, {"tabl", true}, {"bush", true}, {"phantwall", true}, {"wall", false}, {"torch", false} };
    map<string, bool> ph_avalbs{ {"plate", true}, {"token", true}, {"fruit", true}, {"tabl", true}, {"bush", true}, {"phantwall", true}, {"wall", true}, {"torch", false} };
};
map<int, Object> map_coding;

Object plate;
Object token;
Object fruit;
Object tabl;
Object bush;
Object phantwall;
Object wall;
Object torch;
void BaseObjectsInit() {
    plate.Init("plate");
    token.Init("token");
    fruit.Init("fruit");
    tabl.Init("tabl");
    bush.Init("bush");
    phantwall.Init("phantwall");
    wall.Init("wall");
    torch.Init("torch");

    map_coding = { {0, plate}, {1, token}, {2, wall}, {3, phantwall}, {4, torch}, {5, tabl}, {6, bush} };
}

class MovableObject {
public:
    int id = 0;
    char icon = 1;
    string name = "noob";
    string color = "YELLOW";
    string back_color = "BLACK";
    bool virus = false;
    bool light_source = false;
    int light_power = 0;

    bool pl_avalb = true;
    bool collectable = false;
    bool cr_avalb = true;
    bool ph_avalb = true;

    Pos pos;
    Pos start_pos;
    Object point;
    map<char, int> target;
    Pos last_point;
    int speed = 0;
    bool active = true;
    bool die = false;
};

MovableObject uplate;
MovableObject player;
MovableObject crims;
MovableObject phantom;

#pragma endregion

class Game {
public:
    vector<string> commands;
    pair<vector<Object>, vector<MovableObject>> objects;

    vector<vector<Object>> field;
    vector<vector<int>> lightfield;
    vector<vector<MovableObject>> movfield;

    int y = 0;
    int x = 0;

    vector<vector<int>> fruit_pos;

    int speed = 30000;
    double timer = 0;
    double tick = 0;
    double score = 0;
};
Game game;

class Modals {
public:
    Pos field_pos;
    Pos game_active_pos;
    Pos show_pos_pos;
    Pos show_params_pos;
    Pos command_wnd_pos;
};
Modals modals;

void ModalsInit() {
    modals.field_pos.x = 4;
    modals.field_pos.y = 5;
    modals.game_active_pos.y = modals.field_pos.y - 4;
    modals.show_params_pos.x = modals.field_pos.x + 0 + (game.x * 2) + 3;
    modals.show_params_pos.y = modals.field_pos.y;
    modals.show_pos_pos.x = modals.field_pos.x + (game.x * 2) + 3;
    modals.show_pos_pos.y = modals.show_params_pos.y + 9;
}

void BaseMovableObjectInit() {
    player.id = 5;
    player.icon = 1;
    player.name = "player";
    player.color = "YELLOW";
    player.light_source = true;
    player.light_power = 2;
    player.speed = (game.speed / 100) * 25;
    player.point = plate;

    crims.id = 7;
    crims.icon = 2;
    crims.name = "crims";
    crims.color = "RED";
    crims.speed = (game.speed / 100) * 50;
    crims.point = plate;

    phantom.id = 9;
    phantom.icon = 2;
    phantom.name = "phantom";
    phantom.color = "MAGENTA";
    phantom.speed = (game.speed / 100) * 75;
    phantom.point = plate;
}


Object ObjFindName(string name);

class Events {
public:
    int mode = Pursuit;
    bool pause = false;
    bool fruits_spawned = ZeroWave;

    bool freeze = false;
    bool night = false;


    bool EvUnPlayer(bool funny) {
        for (int i = 0; i < size(game.field); i++)
        {
            for (int j = 0; j < size(game.field[i]); j++)
            {
                if (funny)
                {
                    game.field[i][j] = bush;
                }
                else
                {
                    game.field[i][j] = phantwall;
                }
            }
        }
        int player_point = 0;
        int crims_point = 0;
        int phantom_point = 0;
        Field_Out();
        return !funny;
    }

    void EvSpawnFruit() {
        for (int i = 0; i < size(game.fruit_pos); i++)
        {
            game.field[game.fruit_pos[i][1]][game.fruit_pos[i][0]] = fruit;
        }
        fruits_spawned += 1;
    }

    void EvScatter() {
        if (mode != Panic)
        {
            mode = Scatter;
        }
    }

    void EvUnScatter() {
        if (mode != Panic)
        {
            mode = Pursuit;
        }
    }

    void EvPanic() {
        if (mode != Panic)
        {
            mode = Panic;
            crims.speed *= 1, 5;
            phantom.speed /= 1, 5;
            crims.color = "BLUE";
            phantom.color = "BLUE";
        }
    }

    void EvUnPanic() {
        if (mode == Panic)
        {
            mode = Pursuit;
            crims.speed /= 1, 5;
            phantom.speed *= 1, 5;
            crims.color = "RED";
            phantom.color = "MAGENTA";
        }
    }

    void EvNight() {
        srand(time(NULL));
        if (!night)
        {
            night = true;
            for (int i = 0; i < game.y; i++)
            {
                for (int j = 0; j < game.x; j++)
                {
                    if (game.field[i][j].id < ObjFindName("bush").id and rand() % 100 < 5)
                    {
                        game.field[i][j] = ObjFindName("bush");
                    }
                }
            }
            Light_Generate();
        }
    }

    void EvUnNight() {
        if (night)
        {
            night = false;
            Light_Generate();
            Field_Out();
        }
    }
};
Events events;

class Setups {
public:
    bool show_pos = false;
    bool show_params = false;
};
Setups setups;

class Mods {
public:
    bool create = false;
};
Mods mods;

class Sounds {
public:
    void Tabl() {
        Beep(400, 30);
        Beep(450, 20);
        Beep(550, 10);
    }

    void Fruit() {
        Beep(500, 50);
        Beep(200, 10);
        Beep(500, 25);
        Beep(450, 25);
        Beep(150, 5);
        Beep(450, 12.5);
        Beep(300, 12.5);
        Beep(50, 2.5);
        Beep(300, 12.5);
    }

    void PhantomDie() {
        Beep(320, 50);
        Beep(200, 20);
        Beep(200, 20);
        Beep(320, 50);
        Beep(50, 75);
        Beep(250, 75);
    }

    void CrimsDie() {
        Beep(400, 100);
        Beep(300, 10);
        Beep(400, 50);
    }

    void Error() {
        Beep(400, 50);
        Beep(350, 100);
        Beep(300, 75);
    }

    void Bush() {
        Beep(210, 50);
        Beep(250, 32);
        Beep(280, 37);
    }

    void NoBush() {
        Beep(300, 75);
        Beep(250, 62);
        Beep(200, 37);
    }
};
Sounds sounds;

#pragma endregion




void Field_GameActive() {
    Modal modal;
    string text = "Game Playing";
    if (events.pause) text = "Game Paused";
    else if (!player.active) text = "Heh, and where";

    modals.game_active_pos.x = modals.field_pos.x + game.x - (size(text) / 2);
    modal.CreateModal(text, 1, 1, false, "LIGHT RED");

    SetConsoleCursorPosition(hand, { short(0), short(modals.game_active_pos.y) });
    for (int i = 0; i < modals.field_pos.x + game.x * 2; i++) cout << ' ';

    modal.OutContent(modals.game_active_pos.y, modals.game_active_pos.x);


    SetConsoleCursorPosition(hand, { short(modals.field_pos.x + 2), short(modals.field_pos.y - 2) });
    ForePrint("Score: " + Str(Round(game.score)), "LIGHT YELLOW");


    text = "";
    for (auto& i : Range(0, fruit.collected)) text += fruit.icon + " ";
    SetConsoleCursorPosition(hand, { short(game.x - 2), short(modals.game_active_pos.y - 2) });
    ForePrint(text, fruit.color);
}

void Field_Show_Pos() {
    if (setups.show_pos)
    {
        Modal modal;
        string point = Str((char)249);
        modal.CreateModal("\nPosition (x | y):\n", 1, 1, false, "LIGHT RED");
        modal.SetFrameColor("LIGHT RED");
        modal.In(point + " Player Pos: " + Str(player.pos.x) + " | " + Str(player.pos.y) + "\n");
        modal.In(point + " Crims Pos: " + Str(crims.pos.x) + " | " + Str(crims.pos.y) + "\n");
        modal.In(point + " Phantom Pos: " + Str(phantom.pos.x) + " | " + Str(phantom.pos.y) + "\n");

        modal.Out(modals.show_pos_pos.y, modals.show_pos_pos.x);
    }
}

void Field_Show_Params() {
    if (setups.show_params)
    {
        Modal modal;
        string point = Str((char)249);
        modal.CreateModal("\nParametrs:   \n", 1, 1, false, "LIGHT RED");
        modal.In(point + " Game Time: " + Str(game.timer) + "\n");
        modal.In(point + " Tokens: " + Str(game.objects.first[token.id].collected) + "\n");
        modal.In(point + " Tokens: " + Str(game.objects.first[fruit.id].collected) + "\n");
        modal.In(point + " Player Speed: " + Str(player.speed) + "\n");
        modal.In(point + " Crims Speed : " + Str(crims.speed) + "\n");
        modal.In(point + " Phantom Speed: " + Str(phantom.speed) + "\n");

        modal.Out(modals.show_params_pos.y, modals.show_params_pos.x);
    }
}

void FieldUpdate() {
    Field_Show_Pos();
    Field_Show_Params();
    Field_GameActive();
}

void Field_Out(int pick_x, int pick_y) {
    Field_GameActive();
    Modal field;
    string text;
    for (auto& i : Range(0, game.y + 1)) {
        for (auto& i : Range(0, game.x)) text += "  ";
        text += " \n";
    }
    field.CreateModal(text, 1, 2, true);
    field.OutFrame(modals.field_pos.y, modals.field_pos.x);

    for (int i = 0; i < game.y + 1; i++) {
        SetConsoleCursorPosition(hand, { short(1 + modals.field_pos.x), short(1 + modals.field_pos.y + i) });
        for (int j = 0; j < game.x + 1; j++) {
            if (events.pause) {
                Fore(game.field[i][j].color);
                if (pick_x == j and pick_y == i)
                {
                    Fore(game.field[i][j].color, "LIGHT RED");
                }
                else if (pick_x == j or pick_y == i)
                {
                    Fore(game.field[i][j].color, "LIGHT GREEN");
                }
            }
            else { Fore(game.field[i][j].color, game.field[i][j].back_color); }

            cout << game.field[i][j].icon;

            //Space Out
            if (j < game.x) {
                bool wall_isphantom = game.field[i][j].id == phantwall.id;
                bool wall_iswall = game.field[i][j].id == wall.id;
                bool right_wall_isphantom = game.field[i][j + 1].id == phantwall.id;
                bool right_wall_iswall = game.field[i][j + 1].id == wall.id;

                if (events.pause)
                {
                    Fore();
                }
                else if ((wall_iswall and right_wall_isphantom) or (wall_isphantom and right_wall_iswall))
                {
                    Fore("BLACK", wall.back_color);
                }
                else if (wall_iswall and right_wall_iswall)
                {
                    Fore("BLACK", wall.back_color);
                }
                else if (wall_isphantom and right_wall_isphantom)
                {
                    Fore("BLACK", phantwall.back_color);
                }
                else { Fore(); }
                cout << ' ';
            }
        }
        ForePrint("\n", "BLACK", "BLACK");
    }


    //ForePrint("\nScore: " + Str(Round(game.score)), "LIGHT YELLOW");
    //ForePrint("     ");
    //for (auto& i : Range(0, fruit.collected))
    //{
    //    ForePrint(Str(fruit.icon) + " ", fruit.color);
    //}
    //Fore(); cout << endl;

    if (events.pause)
    {
        ForePrint("\nGame Paused\n", "LIGHT RED");
    }
    else if (!player.active)
    {
        ForePrint("\nHeh, and where\n", "LIGHT RED");
    }
    Field_Show_Pos();
    Field_Show_Params();
}

void Field_eOut(int pick_x, int pick_y) {
    system("cls");

    if (events.pause)
    {
        Fore("LIGHT RED");
        cout << "  ";
        for (int i = 0; i < game.x + 1; i++)
        {
            cout << i % 10 << " ";
        }
        cout << endl;
    }
    else
    {
        Fore();
        for (int i = 0; i < game.x + 1; i++)
        {
            cout << "  ";
        }
        cout << endl;
    }

    for (int i = 0; i < game.y + 1; i++)
    {
        if (events.pause)
        {
            Fore("LIGHT RED");
            cout << i % 10 << " ";
        }
        else
        {
            ForePrint("  ", "BLACK", "BLACK");
        }

        for (int j = 0; j < game.x + 1; j++)
        {
            if (game.movfield[i][j].id != player.id and game.movfield[i][j].id != crims.id and game.movfield[i][j].id != phantom.id)
            {
                if (events.pause)
                {
                    Fore(game.field[i][j].color);
                    if (pick_x == j and pick_y == i)
                    {
                        Fore(game.field[i][j].color, "LIGHT RED");
                    }
                    else if (pick_x == j or pick_y == i)
                    {
                        Fore(game.field[i][j].color, "LIGHT GREEN");
                    }
                }
                else { Fore(game.field[i][j].color, game.field[i][j].back_color); }

                cout << game.field[i][j].icon;
            }
            else
            {
                ForePrint(Str(game.movfield[i][j].icon), game.movfield[i][j].color, game.field[i][j].back_color);
            }

            //���������� �������
            if (j < game.x)
            {
                bool wall_isphantom = game.field[i][j].id == phantwall.id;
                bool wall_iswall = game.field[i][j].id == wall.id;
                bool right_wall_isphantom = game.field[i][j + 1].id == phantwall.id;
                bool right_wall_iswall = game.field[i][j + 1].id == wall.id;

                if (events.pause)
                {
                    Fore();
                }
                else if ((wall_iswall and right_wall_isphantom) or (wall_isphantom and right_wall_iswall))
                {
                    Fore("BLACK", wall.back_color);
                }
                else if (wall_iswall and right_wall_iswall)
                {
                    Fore("BLACK", wall.back_color);
                }
                else if (wall_isphantom and right_wall_isphantom)
                {
                    Fore("BLACK", phantwall.back_color);
                }
                else { Fore(); }
                cout << " ";
            }
        }
        ForePrint("\n", "BLACK", "BLACK");
    }


    ForePrint("\nScore: " + Str(Round(game.score)), "LIGHT YELLOW");
    ForePrint("     ");
    for (auto& i : Range(0, fruit.collected))
    {
        ForePrint(Str(fruit.icon) + " ", fruit.color);
    }
    Fore(); cout << endl;

    if (events.pause)
    {
        ForePrint("\nGame Paused\n", "LIGHT RED");
    }
    else if (!player.active)
    {
        ForePrint("\nHeh, and where\n", "LIGHT RED");
    }
    Field_Show_Pos();
    if (setups.show_params)  Field_Show_Params();
}

void Light_Generate() {
    if (events.night)
    {
        for (int y = 0; y < game.y + 1; y++) for (int x = 0; x < game.x + 1; x++) {
            if ((game.field[y][x].light_source) or (game.movfield[y][x].light_source))
            {
                int light_range = game.field[y][x].light_power;
                if (game.movfield[y][x].light_source) light_range = game.movfield[y][x].light_power;

                for (int i = Collapse(y - light_range, { 0, game.y }); i < Collapse(y + light_range + 1, { 0, game.y }); i++)
                    for (int j = Collapse(x - light_range, { 0, game.x }); j < Collapse(x + light_range + 1, { 0, game.x }); j++) if (0 < i < game.y and 0 < j < game.x)
                    {
                        if (game.movfield[i][j].id == uplate.id) {
                            ForeEdit(game.field[i][j].icon, { Occur_y(i), Occur_x(j) }, game.field[i][j].color, game.field[i][j].back_color);
                        }
                        else {
                            ForeEdit(game.movfield[i][j].icon, { Occur_y(i), Occur_x(j) }, game.movfield[i][j].color, game.movfield[i][j].back_color);
                        }
                    }
            }
            else ForeEdit(' ', { Occur_y(y), Occur_x(x) });
        }
    }
}

void Infection() {
    for (int i = 0; i < game.y; i++)
    {
        for (int j = 0; j < game.x; j++)
        {
            if (game.field[i][j].virus and i != 0 and j != 0 and i != game.y and j != game.x)
            {
                Object virus = game.field[i][j];
                if (rand() % 100 <= virus.virus_chance)
                {
                    switch (rand() % 4)
                    {
                    case 0:
                        if ((game.field[i - 1][j].id < virus.id and virus.virus_rule == UnderId) or (game.field[i - 1][j].id > virus.id and virus.virus_rule == UpperId) or virus.virus_rule == All)
                            game.field[i - 1][j] = virus;
                        break;

                    case 1:
                        if ((game.field[i][j - 1].id < virus.id and virus.virus_rule == UnderId) or (game.field[i - 1][j].id > virus.id and virus.virus_rule == UpperId) or virus.virus_rule == All)
                            game.field[i][j - 1] = virus;
                        break;

                    case 2:
                        if ((game.field[i + 1][j].id < virus.id and virus.virus_rule == UnderId) or (game.field[i - 1][j].id > virus.id and virus.virus_rule == UpperId) or virus.virus_rule == All)
                            game.field[i + 1][j] = virus;
                        break;

                    case 3:
                        if ((game.field[i][j + 1].id < virus.id and virus.virus_rule == UnderId) or (game.field[i - 1][j].id > virus.id and virus.virus_rule == UpperId) or virus.virus_rule == All)
                            game.field[i][j + 1] = virus;
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }
}




Object ObjFindName(string name) {
    for (auto& i : game.objects.first)
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
        num = game.y;
    }
    else if (num < 0 and line == 'x')
    {
        num = game.x;
    }
    else if (num > game.y and line == 'y')
    {
        num = 0;
    }
    else if (num > game.x and line == 'x')
    {
        num = 0;
    }
    return num;
}

bool PosConside(Pos obj1, Pos obj2) {
    return (obj1.x == obj2.x and obj1.y == obj2.y);
}

void UpdateFieldObject(Object obj) {
    for (int i = 0; i < game.y + 1; i++)
    {
        for (int j = 0; j < game.x + 1; j++)
        {
            if (obj.id == game.field[i][j].id)
            {
                game.field[i][j] = obj;
            }
        }
    }
    game.objects.first[obj.id] = obj;
}

vector<int> Occurate(Pos pos) {
    return { pos.y + 1 + modals.field_pos.y, pos.x * 2 + 1 + modals.field_pos.x };
}




void CommandGenerate() {
    game.commands = {};


    for (auto& i : game.objects.first)
    {
        game.commands.push_back("spawn_" + i.name + "=[x,y]");
        game.commands.push_back("spawn_" + i.name + "_x" + "=[x]");
        game.commands.push_back("spawn_" + i.name + "_y" + "=[y]");
    }

    game.commands.push_back("replace_all=[replacement]");
    for (auto& i : game.objects.first)  game.commands.push_back("replace_" + i.name + "=" + "[replacer_name]");
    for (auto& i : game.objects.second)  game.commands.push_back("place_" + i.name + "=[x,y]");


    vector<string> active{ "freeze", "crims", "phantom", "player", "night" };
    for (auto& i : active)  game.commands.push_back("active_" + i + "=(true or false)");
    game.commands.push_back("active_mode=(pursuit or scatter or panic)");

    vector<string> set{ "tokens", "fruits", "speed", "player_speed", "crims_speed", "phantom_speed" };
    for (auto& i : set)  game.commands.push_back("set_" + i + "=[int]");

    game.commands.push_back("show_pos=(true or false)");
    game.commands.push_back("show_params=(true or false)");


    game.commands.push_back("mod_create=(true or false)");
    if (mods.create)
    {
        game.commands.push_back("mod_create_obj=(item, name, color, back_color)");
        for (auto& i : game.objects.first)
        {
            game.commands.push_back("mod_create_edit_light_" + i.name + "=" + "(lighting, light_power)");
            game.commands.push_back("mod_create_edit_avalb_" + i.name + "=" + "(pl_avalb cr_avalb, ph_avalb)");
            game.commands.push_back("mod_create_edit_virus_" + i.name + "=" + "(virus, virus_chance, virus_rule)");
            game.commands.push_back("mod_create_edit_cost_" + i.name + "=" + "(collectable, cost)");
            game.commands.push_back("mod_create_replace_id_" + i.name + "=" + "(replacer_name)");
        }
    }
}

void CommandTab(string command) {
    vector<string> vec = Split(Connect(Split(command, "="), "_"), "_");

    if (size(vec[size(vec) - 1]) != 0)
    {
        if (vec[0] == "spawn")
        {
            vector<string> params = Split(vec[size(vec) - 1], ",");
            if (size(params) == 1) { params.push_back("1000"); }

            Object spawned = ObjFindName(vec[1]);

            if (vec[2] == "x") {
                for (int i = 0; i < game.y + 1; i++) {
                    game.field[i][Int(params[0])] = spawned;
                }
            }
            else if (vec[2] == "y") {
                for (int i = 0; i < game.x + 1; i++) {
                    game.field[Int(params[0])][i] = spawned;
                }
            }
            else {
                game.field[Int(params[1])][Int(params[0])] = spawned;
            }

            Field_Out(Int(params[0]), Int(params[1]));
        }
        else if (vec[0] == "replace") {
            Object replaced = ObjFindName(vec[1]);
            Object replacer = ObjFindName(vec[size(vec) - 1]);

            for (int y = 0; y < game.y + 1; y++) {
                for (int x = 0; x < game.x + 1; x++) {
                    if (vec[1] == "all") {
                        game.field[y][x] = replacer;
                    }
                    else if (game.field[y][x].id == replaced.id) {
                        game.field[y][x] = replacer;
                    }
                }
            }
            if (vec[1] == "all") {
                player.point = plate;
                crims.point = plate;
                phantom.point = plate;
            }
            Field_Out();
        }
        else if (vec[0] == "place")
        {
            vector<string> params = Split(vec[size(vec) - 1], ",");

            if (vec[1] == "player") {
                game.movfield[player.pos.y][player.pos.x] = uplate;
                player.point = game.field[Int(params[0])][Int(params[1])];
                player.pos.x = Int(params[0]);
                player.pos.y = Int(params[1]);
                game.movfield[player.pos.y][player.pos.x] = player;
            }
            else if (vec[1] == "crims") {
                game.movfield[crims.pos.y][crims.pos.x] = uplate;
                crims.point = game.field[Int(params[0])][Int(params[1])];
                crims.pos.x = Int(params[0]);
                crims.pos.y = Int(params[1]);
                game.movfield[crims.pos.y][crims.pos.x] = crims;
            }
            else if (vec[1] == "phantom") {
                game.movfield[phantom.pos.y][phantom.pos.x] = uplate;
                phantom.point = game.field[Int(params[0])][Int(params[1])];
                phantom.pos.x = Int(params[0]);
                phantom.pos.y = Int(params[1]);
                game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
            }

            Field_Out(Int(params[0]), Int(params[1]));
        }
        else if (vec[0] == "active")
        {
            string param = vec[size(vec) - 1];

            if (vec[1] == "mode")
            {
                int par = Pursuit;
                if (param == "scatter")
                {
                    par = Scatter;
                }
                else if (param == "panic")
                {
                    par = Panic;
                }
                events.mode = par;
            }
            else
            {
                bool par = Bool(param);
                if (vec[1] == "night")
                {
                    if (par == true)
                    {
                        events.EvNight();
                    }
                    else
                    {
                        events.EvUnNight();
                    }
                }
                else if (vec[1] == "freeze")
                {
                    events.freeze = par;
                }
                else if (vec[1] == "crims")
                {
                    crims.active = par;
                    if (par)
                    {
                        game.movfield[crims.pos.y][crims.pos.x] = crims;
                    }
                    else
                    {
                        game.movfield[crims.pos.y][crims.pos.x] = uplate;
                    }
                }
                else if (vec[1] == "phantom")
                {
                    phantom.active = par;
                    if (par)
                    {
                        game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
                    }
                    else
                    {
                        game.movfield[phantom.pos.y][phantom.pos.x] = uplate;
                    }
                }
                else if (vec[1] == "player")
                {
                    player.active = par;
                    if (par)
                    {
                        game.movfield[player.pos.y][player.pos.x] = player;
                    }
                    else
                    {
                        game.movfield[player.pos.y][player.pos.x] = uplate;
                    }
                }
            }
        }
        else if (vec[0] == "set")
        {
            if (vec[1] == "tokens")
            {
                token.collected = Int(vec[size(vec) - 1]);
                game.score = (token.collected * token.cost) / ((game.timer / 100000000) / 2);
                UpdateFieldObject(token);
            }
            else if (vec[1] == "fruits")
            {
                fruit.collected = Int(vec[size(vec) - 1]);
                game.score = (fruit.collected * fruit.cost) / ((game.timer / 100000000) / 2);
                UpdateFieldObject(fruit);
            }
            else if (vec[1] == "speed")
            {
                game.speed = Int(vec[size(vec) - 1]);
                player.speed = (game.speed / 100) * 25;
                crims.speed = (game.speed / 100) * 50;
                phantom.speed = (game.speed / 100) * 75;
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

            Field_Out();
        }
        else if (vec[0] == "show")
        {
            bool param = Bool(vec[size(vec) - 1]);

            if (vec[1] == "pos")
            {
                setups.show_pos = param;
                Field_Show_Pos();
            }
            else if (vec[1] == "params")
            {
                setups.show_params = param;
                Field_Show_Params();
            }
        }
        else if (vec[0] == "mod")
        {
            if (vec[1] == "create")
            {
                if (mods.create and vec[2] == "obj")
                {
                    vector<string> params = Split(vec[size(vec) - 1], ",");
                    Object block;

                    block.id = size(game.objects.first);
                    block.icon = Char(params[0]);
                    block.name = params[1];
                    block.color = params[2];
                    block.back_color = params[3];

                    block.virus = false;
                    block.light_source = false;
                    block.light_power = 0;

                    block.pl_avalb = false;
                    block.collectable = false;
                    block.cr_avalb = false;
                    block.ph_avalb = false;

                    game.objects.first.push_back(block);
                }
                else if (mods.create and vec[2] == "edit")
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

                        block.pl_avalb = Bool(params[0]);
                        block.collectable = Bool(params[1]);
                        block.cr_avalb = Bool(params[2]);
                        block.ph_avalb = Bool(params[3]);
                    }
                    else if (vec[3] == "virus") {
                        vector<string> params = Split(vec[size(vec) - 1], ",");
                        map<string, int> rules{ {"None", 0}, { "UnderId", 1 }, { "UpperId", 2 }, { "All", 3 }, };

                        block.virus = Bool(params[0]);
                        block.virus_chance = Int(params[1]);
                        block.virus_rule = rules[params[2]];
                    }
                    else if (vec[3] == "cost")
                    {
                        vector<string> params = Split(vec[size(vec) - 1], ",");

                        block.collectable = Bool(params[0]);
                        block.cost = Int(params[1]);
                    }

                    int num = 0;
                    for (int i = 0; i < size(game.objects.first); i++)
                    {
                        if (game.objects.first[i].name == vec[4])
                        {
                            num = i;
                        }
                    }
                    game.objects.first[num] = block;
                    UpdateFieldObject(block);
                }
                else if (mods.create and vec[2] == "replace" and vec[3] == "id")
                {
                    Object replaced;
                    int replaced_num;
                    Object replacer;
                    int replacer_num;
                    for (int i = 0; i < size(game.objects.first); i++)
                    {
                        if (game.objects.first[i].name == vec[4])
                        {
                            replaced = game.objects.first[i];
                            replaced_num = i;
                        }
                        else if (game.objects.first[i].name == vec[size(vec) - 1])
                        {
                            replacer = game.objects.first[i];
                            replacer_num = i;
                        }
                    }
                    int save_id = replacer.id;
                    game.objects.first[replaced_num] = replacer; replacer.id = replaced.id;
                    game.objects.first[replacer_num] = replaced; replaced.id = save_id;


                    UpdateFieldObject(replacer);
                    UpdateFieldObject(replaced);
                }
                else
                {
                    mods.create = Bool(vec[size(vec) - 1]);
                }

                CommandGenerate();
                Field_Out();
            }
        }
    }
}

void CommandInput() {
    SetConsoleCursorPosition(hand, { short(modals.field_pos.x), short(modals.field_pos.y + game.y + 3) });
    string command; ForePrint("Enter Command: ", "LIGHT RED");
    while (true)
    {
        if (_kbhit())
        {
            SetConsoleCursorPosition(hand, { short(modals.field_pos.x + size("Enter Command: ")), short(modals.field_pos.y + game.y + 3)});
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
                    vector<string> maybe = Find(game.commands, command);
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
            else if (button == '\b' and size(command) != 0)
            {
                command.pop_back();
            }
            else
            {
                command += button;
            }
            ForePrint(command, "LIGHT RED");

            vector<string> maybe = Find(game.commands, command);
            if (size(maybe) != 0)
            {
                Fore("GRAY"); cout << "  ~" << maybe[0] << endl;
                for (int i = 1; i < size(maybe); i++)
                {
                    SetConsoleCursorPosition(hand, { short(modals.field_pos.x + size("Enter Command: ") + size(command)), short(modals.field_pos.y + game.y + 2 + i) });
                    Fore("GRAY"); cout << "  ~" << maybe[i];
                    if (i == 4) { break; }
                }
            }
        }
    }
    CommandTab(command);
}




class CrimsMove {
public:
    void Move() {
        srand(time(NULL));
        path = { {'y', 0, -1, 0, game.field[game.y][crims.pos.x].cr_avalb}, {'x', 0, 0, -1, game.field[crims.pos.y][game.x].cr_avalb}, {'y', game.y, 1, 0, game.field[0][crims.pos.x].cr_avalb}, {'x', game.x, 0, 1, game.field[crims.pos.y][0].cr_avalb} };
        if (crims.die)
        {
            crims.target = { {'y', crims.start_pos.y}, {'x', crims.start_pos.x} };
        }
        else if (events.mode == Pursuit)
        {
            crims.target = { {'y', player.pos.y}, {'x', player.pos.x} };
        }
        else if (events.mode == Scatter)
        {
            crims.target = { {'y', 1}, {'x', 1} };
        }
        else if (events.mode == Panic)
        {
            Go(rand() % 4);
            if (PosConside(crims.pos, player.pos) and events.mode == Panic and !crims.die)  Die();
            if (PosConside(crims.pos, crims.start_pos) and crims.die) Restart();
            game.movfield[crims.pos.y][crims.pos.x] = crims;
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


        if (PosConside(crims.pos, player.pos) and events.mode == Panic)  Die();
        if (PosConside(crims.pos, crims.start_pos)) Restart();
        game.movfield[crims.pos.y][crims.pos.x] = crims;
    }

    void Die() {
        if (!crims.die)
        {
            crims.die = !crims.die;
            crims.speed /= 2;
            crims.color = "LIGHT RED";
            sounds.CrimsDie();
        }
    }

    void Restart() {
        if (crims.die)
        {
            crims.die = !crims.die;
            crims.speed *= 2;
            crims.color = "RED";
        }
    }

private:
    vector<vector<int>> path;
    int cycle = 0;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos;
        point_pos.y = NormLine(crims.pos.y + vec[2], 'y');
        point_pos.x = NormLine(crims.pos.x + vec[3], 'x');
        Object point = game.field[point_pos.y][point_pos.x];

        if ((point.cr_avalb or crims.die) and (!PosConside(crims.last_point, point_pos) or (cycle >= 4 and PosConside(crims.last_point, point_pos)))) {
            CrimsCursoreMove(point_pos, point); crims.point = point;
            game.movfield[crims.pos.y][crims.pos.x] = uplate;
            crims.pos.y = NormLine(crims.pos.y + vec[2], 'y');
            crims.pos.x = NormLine(crims.pos.x + vec[3], 'x');
            crims.last_point = { crims.pos.y - vec[2], crims.pos.x - vec[3] };
            cycle = 0;
        }
        else if (cycle >= 4) {}
        else { path_num += 1; path_num = Norm(path_num, { Up, Right }); cycle++;  Go(path_num); return; }
    }

    void CrimsCursoreMove(Pos point_pos, Object point) {
        ForeEdit(crims.point.icon, Occurate(crims.pos), crims.point.color, crims.point.back_color);
        ForeEdit(crims.icon, Occurate(point_pos), crims.color, point.back_color);
        FieldUpdate();
    }
};
CrimsMove crims_move;

class PhantomMove {
public:
    void Move() {
        srand(time(NULL));
        path = { {phantom.pos.y, 0, -1, 0}, {phantom.pos.x, 0, 0, -1}, {phantom.pos.y, game.y, 1, 0}, {phantom.pos.x, game.x, 0, 1} };

        if (phantom.die)
        {
            phantom.target = { {'y', phantom.start_pos.y}, {'x', phantom.start_pos.x} };
        }
        else if (events.mode == Pursuit)
        {
            phantom.target = { {'y', player.pos.y}, {'x', player.pos.x} };
        }
        else if (events.mode == Scatter)
        {
            phantom.target = { {'y', game.y - 1}, {'x', game.x - 1} };
        }
        else if (events.mode == Panic)
        {
            vector<vector<int>> corns{ {1, 1}, { game.y - 1, 1 }, { game.y - 1, game.x - 1 }, { 1, game.x - 1 } };
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


        if (PosConside(phantom.pos, player.pos) and events.mode == Panic and !phantom.die)  Die();
        if (PosConside(phantom.pos, phantom.start_pos)) Restart();
        game.movfield[phantom.pos.y][phantom.pos.x] = phantom;
    }

    void Die() {
        if (!crims.die)
        {
            phantom.speed /= 2, 5;
            phantom.color = "LIGHT MAGENTA";
            phantom.die = true;
        }
        sounds.PhantomDie();
    }

    void Restart() {
        if (crims.die)
        {
            phantom.speed *= 2, 5;
            phantom.color = "MAGENTA";
            phantom.die = false;
        }
    }

private:
    vector<vector<int>> path;
    int cycle = 0;
    void Go(int path_num) {
        vector<int> vec = path[path_num];
        Pos point_pos;
        point_pos.y = NormLine(phantom.pos.y + vec[2], 'y');
        point_pos.x = NormLine(phantom.pos.x + vec[3], 'x');
        Object point = game.field[point_pos.y][point_pos.x];

        if (point.ph_avalb)
        {
            PhantomCursoreMove(point_pos, point); phantom.point = point;
            game.movfield[phantom.pos.y][phantom.pos.x] = uplate;
            phantom.pos.y = NormLine(phantom.pos.y + vec[2], 'y');
            phantom.pos.x = NormLine(phantom.pos.x + vec[3], 'x');
        }
        else if (cycle >= 4) {}
        else { path_num += 1; path_num = Norm(path_num, { 0, 3 }); cycle++;  Go(path_num); return; }
    }

    void PhantomCursoreMove(Pos point_pos, Object point) {
        ForeEdit(phantom.point.icon, Occurate(phantom.pos), phantom.point.color, phantom.point.back_color);
        ForeEdit(phantom.icon, Occurate(point_pos), phantom.color, point.back_color);
        FieldUpdate();
    }
};
PhantomMove phantom_move;

class PlayerMove {
public:
    void Move(char dir) {
        if (!events.pause)
        {
            path = { {player.pos.y, 0, game.y, -1, 0}, {player.pos.x, 0, game.x, 0, -1}, {player.pos.y, game.y, 0, 1, 0}, {player.pos.x, game.x, 0, 0, 1} };

            int num = dir;
            if (num == 224) {}
            else if (num == 119 or num == 72 or num == -26 or num == 87)
            {
                Go(Up);
            }
            else if (num == 97 or num == 75 or num == -28 or num == 65)
            {
                Go(Left);
            }
            else if (num == 115 or num == 80 or num == -21 or num == 83)
            {
                Go(Down);
            }
            else if (num == 100 or num == 77 or num == -94 or num == 68)
            {
                Go(Right);
            }

            if (!crims.die) if (PosConside(crims.pos, player.pos) and events.mode == Panic and !crims.die)  crims_move.Die();
            if (!phantom.die) if (PosConside(phantom.pos, player.pos) and events.mode == Panic and !phantom.die)  phantom_move.Die();
            game.movfield[player.pos.y][player.pos.x] = player;
        }

        switch (dir)
        {
        case ' ':
            Field_GameActive();
            events.pause = !events.pause;
            break;

        case 'e':
            if (events.pause)
            {
                CommandInput();
            }
            break;

        default:
            break;
        }
    }

private:
    vector<vector<int>> path;
    void Go(int path_num) {
        vector<int> vec = path[path_num]; char vec0 = vec[0];
        Pos point_pos;
        point_pos.y = NormLine(player.pos.y + vec[3], 'y');
        point_pos.x = NormLine(player.pos.x + vec[4], 'x');
        Object* point = &game.field[point_pos.y][point_pos.x];
        if ((*point).pl_avalb)
        {
            PlayerCursoreMove(point_pos);
            game.movfield[player.pos.y][player.pos.x] = uplate;
            if (player.point.collectable)  game.field[player.pos.y][player.pos.x] = plate;
            player.pos.y = NormLine(player.pos.y + vec[3], 'y');
            player.pos.x = NormLine(player.pos.x + vec[4], 'x');
            Collect(*point);
            player.point = *point;
            player.last_point = point_pos;
        }
        else if ((*point).name == "error") sounds.Error();
    }

    void Collect(Object& point) {
        point.collected += 1;
        UpdateFieldObject(point);
        game.objects.first[token.id].collected = 50;
        game.score += point.cost * game.tick + point.cost;
        if (point.id == tabl.id) { events.EvPanic(); sounds.Tabl(); }
        else if (point.id == fruit.id) { events.EvPanic(); sounds.Fruit(); }
        else if (point.name == "error") sounds.Error();
        else if (point.id == bush.id) {
            events.EvScatter();
            if (game.field[player.last_point.y][player.last_point.x].id != bush.id) sounds.Bush();
        }
        if (point.id != bush.id and game.field[player.last_point.y][player.last_point.x].id == bush.id) { events.EvUnScatter(); sounds.NoBush(); }
    }

    void PlayerCursoreMove(Pos point_pos) {
        if (player.point.collectable) ForeEdit(plate.icon, Occurate(player.pos), plate.color, plate.back_color);
        else ForeEdit(player.point.icon, Occurate(player.pos), player.point.color, player.point.back_color);
        ForeEdit(player.icon, Occurate(point_pos), player.color, player.back_color);
        FieldUpdate();
    }
};
PlayerMove player_move;