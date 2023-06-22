#pragma once //Python V1.2.5
/*
* SetConsoleCursorPosition - x, y
* field - y, x
*/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <map>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <tuple>
using namespace std;
HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
void Fore(string color = "BLACK", string background = "BLACK");
map<string, int> colors = {
	{"BLACK", 0}, {"BLUE", 1}, {"GREEN", 2}, {"CYAN", 3}, {"RED", 4}, {"MAGENTA", 5}, {"YELLOW", 6}, {"WHITE", 7},
	{"GRAY", 8}, {"LIGHT BLUE", 9}, {"LIGHT GREEN", 10}, {"LIGHT CYAN", 11}, {"LIGHT RED", 12}, {"LIGHT MAGENTA", 13}, {"LIGHT YELLOW", 14}, {"LIGHT WHITE", 15} };
vector<string> reversed_colors = { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "YELLOW", "WHITE", "GRAY", "LIGHT BLUE", "LIGHT GREEN", "LIGHT CYAN", "LIGHT RED", "LIGHT MAGENTA", "LIGHT YELLOW", "LIGHT WHITE" };
int base_color = 0;

vector<string> Split(string text, string dived);
bool isnumeric(string in);



void SetWindow(int Width, int Height)
{
	SetWindowPos(GetConsoleWindow(), HWND_TOP, -4, -4, Width, Height, NULL);
}

void SetConsoleFont(int sym_x = 11, int sym_y = 22)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = sym_x;
	cfi.dwFontSize.Y = sym_y;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void SetBooferWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

void SetShowCursor(bool param) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = param;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void BaseConsoleGameInit() {
	srand(time(NULL));
	SetBooferWindow(100, 50);
	SetWindow(1500, 1000);
	SetConsoleFont(15, 24);
	SetShowCursor(false);

	Fore("LIGHT RED", "BLACK");
}


string Open(string file) {
	string out = ""; ifstream xfile; string strin = "";
	xfile.open(file, ios::app);
	if (xfile.is_open()) {
		while (getline(xfile, strin))
		{
			out += strin;
		}
	}
	return out;
}

template<typename inp>
void Drop(inp text, string file) {
	ofstream xfile;
	xfile.open(file);
	xfile << text;
	xfile.close();
}


class Pos {
public:
	int x;
	int y;

	bool Conside(Pos obj2) {
		return (x == obj2.x and y == obj2.y);
	}

	void Set() {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, { short(x), short(y) });
	}
};


#pragma region ReType

int Int(string num) {
	double ant = 0;
	int x = 0;
	map<char, int> nums = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9} };

	for (int i = 0; i < size(num); i++)
	{
		double power = pow(10, ((size(num) - 1) - x));
		ant += nums[num[i]] * power;
		x += 1;
	}
	return ant;
}

double Float(string num) {
	string num1 = "";
	string num2 = "";
	int y = 0;
	for (int i = 0; i < size(num); i++)
	{
		if (num[i] != '.' and y == 0) { num1 += num[i]; }
		else if (y == 1) { num2 += num[i]; }
		else { y = 1; }
	}

	double ant1 = Int(num1);
	double ant2 = Int(num2);

	return ant1 + (ant2 / (size(num2) * 10));
}

char Char(string in) {
	char a = ' ';
	if (size(in) == 1)
	{
		for (auto& i : in) { a = i; }
	}
	return a;
}

bool Bool(string text) {
	bool swit = false;
	if (text == "true")
	{
		swit = true;
	}
	else if (text == "false")
	{
		swit = false;
	}
	else if (size(text) >= 1)
	{
		swit = true;
	}
	else if (size(text) == 0)
	{
		swit = false;
	}
	return swit;
}

template<typename in>
string Str(in obj) {
	string none = Open("python_string_replicator.txt");
	Drop(none, "python_string_replicator.txt");
	Drop(obj, "python_string_replicator.txt");
	string out = Open("python_string_replicator.txt");
	return out;
}

Pos Posit(vector<int> vec) {
	Pos pos;
	pos.x = vec[1];
	pos.y = vec[0];
	return pos;
}

#pragma endregion

template<typename input>
string Type(input in) {
	return typeid(in).name();
}




void Fore(string color, string background) {
	int brush = (16 * colors[background]) + colors[color];

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, brush);

	base_color = brush;
	cerr << "";
}

template<typename anytext>
void ForePrint(anytext text, string color = "BLACK", string background = "BLACK") {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int brush = (16 * colors[background]) + colors[color];

	SetConsoleTextAttribute(handle, brush);
	cerr << text;
	SetConsoleTextAttribute(handle, base_color);
}

//y,x
void ForeEdit(char obj, vector<int> vec, string color = "BLACK", string background = "BLACK") {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { short(vec[1]), short(vec[0]) }); //x,y
	ForePrint(Str(obj), color, background);
}

void Edit(char obj, vector<int> vec) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { short(vec[1]), short(vec[0]) });
	cerr << obj;
}


#pragma region Easy Python Functions

int Factor(int num) {
	if (num == 1) return num;
	return num * Factor(num - 1);
}

int Norm(int num, vector<int> range) {
	if (num < range[0])
	{
		num = range[1];
	}
	else if (num > range[1])
	{
		num = range[0];
	}
	return num;
}

int Collapse(int num, vector<int> range) {
	if (num < range[0]) num = range[0];
	else if (num > range[1]) num = range[1];
	return num;
}

int Mod(int num) {
	int a;
	if (num >= 0) { a = num; }
	else { a = -num; }
	return a;
}

int Round(double num) {
	int a;
	int numer = num;
	if (num - numer > 0.5)
	{
		a = numer + 1;
	}
	else
	{
		a = numer;
	}

	return a;
}

string Input(string text) {
	string a; cerr << text << " ";  getline(cin, a);
	return a;
}

#pragma endregion


template<typename any>
any Choice(vector<any> vec) {
	return vec[Randint(size(vec))];
}

template<typename any1>
any1 RandSnetch(vector<any1> vec) {
	int num = Randint(size(vec));
	any1 elem = vec[num];
	vec = vec.errase(num);
	return elem;
}


vector<int> VecGenerator(int x, int range) {
	srand(time(NULL));
	vector<int> vec;
	for (int i = 0; i < x; i++) { vec.push_back(rand() % range); }
	return vec;
}

vector<vector<int>> Vec2DGenerator(int x, int y, int range) {
	srand(time(NULL));
	vector<vector<int>> vec;
	for (int i = 0; i < y; i++) {
		vector<int> temp;
		for (int j = 0; j < x; j++) { temp.push_back(rand() % range); }
		vec.push_back(temp);
	}
	return vec;
}

vector<vector<vector<int>>> Vec3DGenerator(int x, int y, int z, int range) {
	srand(time(NULL));
	vector<vector<vector<int>>> vec;
	for (int i = 0; i < y; i++) {
		vector<vector<int>> temp;
		for (int j = 0; j < x; j++)
		{
			vector<int> temp2;
			for (int h = 0; h < z; h++)
			{
				temp2.push_back(rand() % range);
			}
			temp.push_back(temp2);
		}
		vec.push_back(temp);
	}
	return vec;
}

vector<int> Range(int start, int end = 0, int step = 1) {
	vector<int> vec;
	if (start < end)
	{
		for (int i = start; i < end; i++)
		{
			vec.push_back(i);
		}
	}
	else if (start > end)
	{
		for (int i = start; i < end; i--)
		{
			vec.push_back(i);
		}
	}
	return vec;
}

bool isnumeric(string in) {
	bool out = false;
	if (size(in) == 1)
	{
		char char_sym = Char(in);
		int num = char_sym;
		if ((47 < num && num < 58) or char_sym == '.')
		{
			out = true;
		}
	}
	else if (size(in) > 1)
	{
		int count = 0;
		for (auto& i : in)
		{
			int num = i;
			if ((47 < num && num < 58) or i == '.')
			{
				count++;
			}
		}
		if (count == size(in))
		{
			out = true;
		}
	}
	return out;
}

bool isalpha(string in) {
	bool out = false;
	if (size(in) == 1)
	{
		int num = Char(in);
		if ((191 < num && num < 256) or (96 < num && num < 123))
		{
			out = true;
		}
	}
	else if (size(in) > 1)
	{
		int count = 0;
		for (auto& i : in)
		{
			int num = i;
			if ((191 < num && num < 256) or (96 < num && num < 123))
			{
				count++;
			}
		}
		if (count == size(in))
		{
			out = true;
		}
	}
	return out;
}

vector<string> Find(vector<string> vec, string item) {
	vector<string> out;
	for (auto& i : vec)
	{
		string temp = "";
		for (int h = 0; h < size(item); h++)
		{
			for (auto& j : i)
			{
				if (j == item[h])
				{
					temp += j;
					h++;
				}
			}
		}
		if (size(temp) >= size(item))
		{
			out.push_back(i);
		}
	}
	return out;
}

vector<string> Split(string text, string dived) {
	char sym;
	vector<string> vec;
	string box = "";
	if (size(dived) == 1 and dived != " ")
	{
		sym = Char(dived);
		text += sym;
		for (auto& i : text) {
			if (i != sym) box += i;
			else if (box != "") { vec.push_back(box); box = ""; }
		}
	}
	else if (dived == "numeric")
	{
		for (auto& i : text) {
			string a; a += i;
			if (isnumeric(a) and box != "") { vec.push_back(box); box = ""; }
			else if (isnumeric(a)) box = "";
			else box += i;
		}
	}
	else if (dived == "alpha")
	{
		for (auto& i : text) {
			if (isalpha(i) and box != "") { vec.push_back(box); box = ""; }
			else if (isalpha(i)) box = "";
			else box += i;
		}
	}
	else if (size(dived) > 1 or dived == " ")
	{
		text += dived;
		for (int i = 0; i < size(text); i++) {
			if (text[i] != dived[0]) box += text[i];
			else if (text[i] == dived[0])
			{
				int count = 1;
				for (int j = 1; j < size(dived); j++) if (dived[j] == text[i + j]) count++;
				if (count == size(dived) and box != "")
				{
					vec.push_back(box);
					box = "";
					i += size(dived) - 1;
				}
			}
		}
	}
	return vec;
}

string Connect(vector<string> vec, string connect = "") {
	string text = "";
	for (int i = 0; i < size(vec); i++)
	{
		if (i == size(vec) - 1) { text += vec[i]; }
		else (text += vec[i] + connect);
	}
	return text;
}



class Modal {
public:
	void CreateModal(string text, int wide, int num_wide, bool numeric, string color = "LIGHT RED", string back_color = "BLACK") {
		FrameInit();
		this->wide = wide;
		this->num_wide = num_wide;
		this->numeric = numeric;
		content = Split(text, "\n");
		y = size(content);
		x = size(content[0]); for (auto& i : content) if (x < size(i)) x = size(i);
		this->color = color;
		this->back_color = back_color;
	}
	void SetFrame(vector<char> corns, vector<char> sides) {
		frame.corners = corns;
		frame.side_vertical = sides[0];
		frame.side_horizontal = sides[1];
	}
	void SetFrameColor(string collor = "LIGHT RED", string back_collor = "BLACK") {
		frame.color = collor;
		frame.back_color = back_collor;
	}
	void Out(int in_y, int in_x) {

		ForeEdit(frame.corners[0], { in_y, in_x }, frame.color, frame.back_color);
		if (!numeric) for (int i = 0; i < x * wide; i++) ForePrint(Str(frame.side_horizontal), frame.color, frame.back_color);
		else for (int i = 0; i < x * wide; i++)
			if (i % num_wide == 0) ForePrint(Str(i / num_wide % 10), frame.color, frame.back_color);
			else ForePrint(Str(frame.side_horizontal), frame.color, frame.back_color);
		ForePrint(Str(frame.corners[1]), frame.color, frame.back_color);


		for (auto& k : Range(0, y))
		{
			ForeEdit(frame.side_vertical, { in_y + 1 + k, in_x }, frame.color, frame.back_color);
			for (auto& h : Range(0, x* wide))
				if (size(content[k]) <= h) ForePrint(Str(' '), color, back_color);
				else ForePrint(Str(content[k][h]), color, back_color);
			ForePrint(Str(frame.side_vertical), frame.color, frame.back_color);
		}


		ForeEdit(frame.corners[2], { in_y + y + 1, in_x }, frame.color, frame.back_color);
		for (int i = 0; i < x * wide; i++) ForePrint(Str(frame.side_horizontal), frame.color, frame.back_color);
		ForePrint(Str(frame.corners[3]), frame.color, frame.back_color);
	}
	void OutFrame(int in_y, int in_x) {

		ForeEdit(frame.corners[0], { in_y, in_x }, frame.color);
		for (int i = 0; i < x; i++) ForePrint(Str(frame.side_horizontal), frame.color);

		ForePrint(Str(frame.corners[1]), frame.color);

		for (auto& k : Range(0, y)) {
			ForeEdit(frame.side_vertical, { in_y + 1 + k, in_x }, frame.color);
			ForeEdit(frame.side_vertical, { in_y + 1 + k, in_x + x + 1 }, frame.color);
		}

		ForeEdit(frame.corners[2], { in_y + y + 1, in_x }, frame.color);
		for (int i = 0; i < x; i++) ForePrint(Str(frame.side_horizontal), frame.color);

		ForePrint(Str(frame.corners[3]), frame.color);
	}
	void OutContent(int in_y, int in_x) {

		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		for (auto& k : Range(0, y)) {
			SetConsoleCursorPosition(handle, { short(in_x), short(in_y + k) });
			ForePrint(content[k], color, back_color);
		}
		cerr << endl;
	}
	void In(string text) {
		vector<string> vec = Split(text, "\n");
		y += size(vec);
		for (auto& i : vec) content.push_back(i);
		x = size(content[0]); for (auto& i : content) if (x < size(i)) x = size(i);
	}

private:
	vector<string> content = {};
	int y = 0;
	int x = 0;
	int wide = 1;
	int num_wide = 1;
	bool numeric = false;
	class Frame {
	public:
		vector<char> corners;
		char side_horizontal;
		char side_vertical;
		string color = "LIGHT RED";
		string back_color = "BLACK";
	};
	Frame frame;
	string color;
	string back_color;

	void FrameInit() {
		frame.corners = { corn1, corn2, corn3, corn4 };
		frame.side_horizontal = 205;
		frame.side_vertical = 186;
		frame.color = "LIGHT RED";
		frame.back_color = "BLACK";
	}
	char corn1 = 201;
	char corn2 = 187;
	char corn3 = 200;
	char corn4 = 188;
};