#pragma once
#include "Python.h"
void FieldOut(int pick_x = 1000, int pick_y = 1000);
void FieldUpdate();
void CommandInput();
void BakeLight();
void SetFieldPos(int y, int x);

enum Dirs {
    Up = 0,
    Left = 1,
    Down = 2,
    Right = 3
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
enum Line {
    X = 1,
    Y = 0
};

vector<string> commands;



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

    bool collectable = false;
    int cost = 0;
    int collected = 0;

    bool light_source = false;
    int light_power = 0;

    int wall = 0;
    bool pl_avalb = false;
    bool cr_avalb = false;
    bool ph_avalb = false;


    bool lighted = false;


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
        wall = walls[iname];
        cr_avalb = cr_avalbs[iname];
        ph_avalb = ph_avalbs[iname];
    }
private:
    map<string, int> ids{ {"plate", 0},       {"token", 1},     {"fruit", 2},     {"tabl", 3},     {"bush", 4},     {"phantwall", 5},     {"wall", 6},     {"torch", 7} };
    map<string, char> icons{ {"plate", ' '}, { "token", 249 }, { "fruit", 15 }, { "tabl", 4 }, { "bush", 177 }, { "phantwall", 254 }, { "wall", 254 }, { "torch", 5 } };
    map<string, string> back_colors{ {"plate", "BLACK"}, { "token", "BLACK" }, { "fruit", "BLACK" }, { "tabl", "BLACK" }, { "bush", "BLACK" }, { "phantwall", "LIGHT RED" }, { "wall", "LIGHT BLUE" }, { "torch", "BLACK" } };
    map<string, string> colors{ {"plate", "BLACK"}, { "token", "LIGHT YELLOW" }, { "fruit", "LIGHT RED" }, { "tabl", "WHITE" }, { "bush", "LIGHT CYAN" }, { "phantwall", "LIGHT RED" }, { "wall", "LIGHT BLUE" }, { "torch", "YELLOW" } };

    map<string, bool> viruses{ {"plate", false}, { "token", true }, { "fruit", false }, { "tabl", false }, { "bush", true }, { "phantwall", false }, { "wall", false }, { "torch", false } };
    map<string, int> virus_chances{ {"plate", 0}, { "token", 10 }, { "fruit", 0 }, { "tabl", 0 }, { "bush", 50 }, { "phantwall", 0 }, { "wall", 0 }, { "torch", 0 } };

    map<string, bool> collectables{ {"plate", false}, { "token", true }, { "fruit", true }, { "tabl", true }, { "bush", false }, { "phantwall", false }, { "wall", false }, { "torch", false } };
    map<string, int> costs{ {"plate", 0}, { "token", 1 }, { "fruit", 20 }, { "tabl", 0 }, { "bush", 0 }, { "phantwall", 0 }, { "wall", 0 }, { "torch", 0 } };

    map<string, bool> light_sources{ {"plate", false}, { "token", false }, { "fruit", false }, { "tabl", false }, { "bush", false }, { "phantwall", false }, { "wall", false }, { "torch", true } };
    map<string, int> light_powers{ {"plate", 0}, { "token", 0 }, { "fruit", 0 }, { "tabl", 0 }, { "bush", 0 }, { "phantwall", 0 }, { "wall", 0 }, { "torch", 5 } };

    map<string, int> walls{ {"plate", 0}, { "token", 0 }, { "fruit", 0 }, { "tabl", 0 }, { "bush", 3 }, { "phantwall", 1 }, { "wall", 2 }, { "torch", 0 } };
    map<string, bool> pl_avalbs{ {"plate", true}, { "token", true }, { "fruit", true }, { "tabl", true }, { "bush", true }, { "phantwall", false }, { "wall", false }, { "torch", false } };
    map<string, bool> cr_avalbs{ {"plate", true}, { "token", true }, { "fruit", true }, { "tabl", true }, { "bush", true }, { "phantwall", true }, { "wall", false }, { "torch", false } };
    map<string, bool> ph_avalbs{ {"plate", true}, { "token", true }, { "fruit", true }, { "tabl", true }, { "bush", true }, { "phantwall", true }, { "wall", true }, { "torch", false } };
};

class Entity {
public:
    int id = 0;
    char icon = 1;
    string name = "noob";
    string color = "YELLOW";
    string back_color = "BLACK";

    int speed = 0;

    bool active = true;
    bool die = false;

    Pos pos;
    Pos start_pos;
    Pos last_point;

    Object point;
    map<char, int> target;
};

Object plate, token, fruit, tabl, bush, phantwall, wall, torch;
Entity uplate, player, crims, phantom;

#pragma endregion


struct Game {
public:
    pair<vector<Object>, vector<Entity>> objects;

    vector<vector<Object>> field;
    vector<vector<Entity>> movfield;

    int y = 0;
    int x = 0;

    vector<vector<int>> fruit_pos;

    int speed = 30000;
    double timer = 0;
    double tick = 0;
    double score = 0;
} game;

struct Modals {
public:
    Pos field_pos;
    Pos game_active_pos;
    Pos show_pos_pos;
    Pos show_params_pos;
    Pos command_wnd_pos;

    void Init() {
        field_pos.x = 4;
        field_pos.y = 5;
        game_active_pos.y = field_pos.y - 4;
        show_params_pos.x = field_pos.x + 0 + (game.x * 2) + 3;
        show_params_pos.y = field_pos.y;
        show_pos_pos.x = field_pos.x + (game.x * 2) + 3;
        show_pos_pos.y = show_params_pos.y + 9;
    }
} Modals;


void BaseObjectsInit() {
    plate.Init("plate");
    token.Init("token");
    fruit.Init("fruit");
    tabl.Init("tabl");
    bush.Init("bush");
    phantwall.Init("phantwall");
    wall.Init("wall");
    torch.Init("torch");
}

void BaseEntityInit() {
    player.id = 5;
    player.icon = 1;
    player.name = "player";
    player.color = "YELLOW";
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
void OFE(Object obj, vector<int> vec, bool paint = false);
void ReplaceObj(int y, int x, Object obj);
void SpaceOut(int x, int y, bool pause = false);
void SpaceOneObj(int y, int x, bool pause = false);


struct Event {
public:
    int mode = Pursuit;
    bool pause = false;
    bool fruits_spawned = ZeroWave;

    bool freeze = false;
    bool night = false;


    bool ToUnPlayer(bool funny) {
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
        FieldOut();
        return !funny;
    }

    void ToSpawnFruit() {
        for (int i = 0; i < size(game.fruit_pos); i++)
        {
            game.field[game.fruit_pos[i][0]][game.fruit_pos[i][1]] = fruit;
            OFE(fruit, { game.fruit_pos[i][0], game.fruit_pos[i][1] });
        }
        fruits_spawned += 1;
    }

    void ToScatter() {
        if (mode != Panic)
        {
            mode = Scatter;
        }
    }

    void ToUnScatter() {
        if (mode != Panic)
        {
            mode = Pursuit;
        }
    }

    void ToPanic() {
        if (mode != Panic)
        {
            mode = Panic;
            crims.speed *= 1, 5;
            phantom.speed /= 1, 5;
            crims.color = "BLUE";
            phantom.color = "BLUE";
        }
    }

    void ToUnPanic() {
        if (mode == Panic)
        {
            mode = Pursuit;
            crims.speed /= 1, 5;
            phantom.speed *= 1, 5;
            crims.color = "RED";
            phantom.color = "MAGENTA";
        }
    }

    void ToNight() {
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
            BakeLight();
            FieldOut();
        }
    }

    void ToUnNight() {
        if (night)
        {
            night = false;
            BakeLight();
            FieldOut();
        }
    }
} Event;

struct Setups {
public:
    bool show_pos = false;
    bool show_params = false;
} Setups;

struct Mods {
public:
    bool create = false;
} Mods;

struct Sounds {
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

    void GameStart() {
        Beep(550, 300);
        Beep(500, 100);
        Beep(500, 100);
        Beep(600, 50);
    }
} Sounds;



/*void OldOut(int pick_x, int pick_y) {
    system("cls");

    if (Event.pause)
    {
        Fore("LIGHT RED");
        cerr << "  ";
        for (int i = 0; i < game.x + 1; i++)
        {
            cerr << i % 10 << " ";
        }
        cerr << endl;
    }
    else
    {
        Fore();
        for (int i = 0; i < game.x + 1; i++)
        {
            cerr << "  ";
        }
        cerr << endl;
    }

    for (int i = 0; i < game.y + 1; i++)
    {
        if (Event.pause)
        {
            Fore("LIGHT RED");
            cerr << i % 10 << " ";
        }
        else
        {
            ForePrint("  ", "BLACK", "BLACK");
        }

        for (int j = 0; j < game.x + 1; j++)
        {
            if (game.movfield[i][j].id != player.id and game.movfield[i][j].id != crims.id and game.movfield[i][j].id != phantom.id)
            {
                if (Event.pause)
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

                cerr << game.field[i][j].icon;
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

                if (Event.pause)
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
                cerr << " ";
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
    Fore(); cerr << endl;

    if (Event.pause)
    {
        ForePrint("\nGame Paused\n", "LIGHT RED");
    }
    else if (!player.active)
    {
        ForePrint("\nHeh, and where\n", "LIGHT RED");
    }
    Field_Show_Pos();
    if (Setups.show_params)  Field_Show_Params();
}*/
