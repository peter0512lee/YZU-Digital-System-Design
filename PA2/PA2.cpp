#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct position//用來記錄圈的圖形的座標
{
	int x;
	int y;
};

struct Circle
{
	int type;//圈的圖形形狀
	string minterm;
	vector < position > pos; //在KMap上的座標
};

void set(Circle &c, int t, string w, vector< position > &p)
{
	c.type = t;
	c.minterm = w;
	c.pos = p;
}

bool duplicate(Circle &c, char map[4][4], int usetimes[4][4])
{
	for (size_t i = 0; i < c.pos.size(); i++)
	{
		if (map[c.pos[i].x][c.pos[i].y] == '1' && usetimes[c.pos[i].x][c.pos[i].y] == 1)
		{
			return false;
		}
				
	}
	return true;
}

bool sixteen(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	bool have_1; //是否有1

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '0') //只要有一個0就不能圈了，直接跳出
			return false;
		else if (map[i / 4][i % 4] == '1') //有1就記錄下來
			have_1 = true;

	if (!have_1) //都沒有1，也就是全2，直接跳出
		return true;

	for (int i = 0; i < 16; i++) //每個數都被圈一次
		usetimes[i / 4][i % 4]++;

	Circle c;
	vector< position > pos;
	position p;
	p.x = 0;
	p.y = 0;
	pos.push_back(p);
	set(c, 44, " 2 2 2 2", pos);

	answer.push_back(c); //儲存答案

	return true; //圈了且整張圖都圈完了
}

bool eight(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	//---------------2 x 4---------------

	bool have_1; //紀錄是否有1

	for (int i = 0; i < 4; i++) //每2層2層看，要看4次
	{
		have_1 = false;
		for (int j = 0; j < 8; j++) //上、下排各4格，共8格
		{
			if (mapEX[i + j / 4][j % 4] == '0') //有一個0就不能圈了
				break;
			else if (mapEX[i + j / 4][j % 4] == '1') //有1，記錄下來
				have_1 = true;

			if (j == 7 && have_1) //有1才做
			{
				for (int k = 0; k < 8; k++) //使用次數增加
					usetimes[(i + k / 4) % 4][k % 4]++; //% 4 是因為是跨邊界的圈法，譬如第一排跟最後一排圈

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 8; k++) //圈起來的格子的每一格位置
				{
					p.x = (i + k / 4) % 4;//x
					p.y = k % 4;//y
					pos.push_back(p);//x, y
				}
				if (i == 0)
					set(c, 24, " 0 2 2 2", pos);
				else if (i == 1)
					set(c, 24, " 2 1 2 2", pos);
				else if (i == 2)
					set(c, 24, " 1 2 2 2", pos);
				else if (i == 3)
					set(c, 24, " 2 0 2 2", pos);

				answer.push_back(c);
			}
		}
	}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 24 && duplicate(answer[i], map, usetimes)) //為 2 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------4 x 2---------------

	for (int i = 0; i < 4; i++) //每2層2層看，要看4次
	{
		have_1 = false;
		for (int j = 0; j < 8; j++) //左、右排各4，共8
		{
			if (mapEX[j / 2][i + j % 2] == '0') //有一個0就不能圈了
				break;
			else if (mapEX[j / 2][i + j % 2] == '1') //有1，記錄下來
				have_1 = true;

			if (j == 7 && have_1) //有1才做
			{
				for (int k = 0; k < 8; k++) //使用次數增加
					usetimes[k / 2][(i + k % 2) % 4]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 8; k++) //圈起來的格子的每一格位置
				{
					p.x = k / 2;//x
					p.y = ((i + k) % 2) % 4;//y
					pos.push_back(p);//x, y
				}
				if (i == 0)
					set(c, 42, " 2 2 0 2", pos);
				else if (i == 1)
					set(c, 42, " 2 2 2 1", pos);
				else if (i == 2)
					set(c, 42, " 2 2 1 2", pos);
				else if (i == 3)
					set(c, 42, " 2 2 2 0", pos);

				answer.push_back(c);
			}
		}
	}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 42 && duplicate(answer[i], map, usetimes)) //為 2 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
	{
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //有為1卻沒被圈到的就代表尚未完成
			return false;
	}
	return true; //1的都圈到了，完成了
}

bool four(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	bool have_1; //紀錄是否有1

	//---------------1 x 4---------------

	for (int i = 0; i < 4; i++) //每1層1層看，要看4次
	{
		have_1 = false;
		for (int j = 0; j < 4; j++) //一排4個
		{
			if (mapEX[i][j] == '0') //有一個0就不能圈了
				break;
			else if (mapEX[i][j] == '1') //有1，記錄下來
				have_1 = true;

			if (j == 3 && have_1) //有1才做
			{
				for (int k = 0; k < 4; k++) //使用次數增加
					usetimes[i][k]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 4; k++) //圈起來的格子的每一格位置
				{
					p.x = i;//x
					p.y = k;//y
					pos.push_back(p);//x, y
				}
				if (i == 0)
					set(c, 14, " 0 0 2 2", pos);
				else if (i == 1)
					set(c, 14, " 0 1 2 2", pos);
				else if (i == 2)
					set(c, 14, " 1 1 2 2", pos);
				else if (i == 3)
					set(c, 14, " 1 0 2 2", pos);

				answer.push_back(c);
			}
		}
	}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 14 && duplicate(answer[i], map, usetimes)) //為 1 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------4 x 1---------------
	
	for (int i = 0; i < 4; i++) //每1層1層看，要看4次
	{
		have_1 = false;
		for (int j = 0; j < 4; j++) //一排4個
		{
			if (mapEX[j][i] == '0') //有一個0就不能圈了
				break;
			else if (mapEX[j][i] == '1') //有1，記錄下來
				have_1 = true;

			if (j == 3 && have_1) //有1才做
			{
				for (int k = 0; k < 4; k++) //使用次數增加
					usetimes[k][i]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 4; k++) //圈起來的格子的每一格位置
				{
					p.x = k;//x
					p.y = i;//y
					pos.push_back(p);//x, y
				}
				if (i == 0)
					set(c, 41, " 2 2 0 0", pos);
				else if (i == 1)
					set(c, 41, " 2 2 0 1", pos);
				else if (i == 2)
					set(c, 41, " 2 2 1 1", pos);
				else if (i == 3)
					set(c, 41, " 2 2 1 0", pos);

				answer.push_back(c);
			}
		}
	}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 41 && duplicate(answer[i], map, usetimes)) //為 1 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------2 x 2---------------
	
	for (int i = 0; i < 4; i++) //每2層2層看，要看4次，由上到下
		for (int j = 0; j < 4; j++) //每2層2層看，要看4次，由左到右
		{
			have_1 = false;
			for (int k = 0; k < 4; k++) //上下排各2，共4
			{
				if (mapEX[i + k / 2][j + k % 2] == '0') //有一個0就不能圈了
					break;
				else if (mapEX[i + k / 2][j + k % 2] == '1') //有1，記錄下來
					have_1 = true;

				if (k == 3 && have_1) //有1才做
				{
					for (int k = 0; k < 4; k++) //使用次數增加
						usetimes[(i + k / 2) % 4][(j + k % 2) % 4]++;
										
					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 4; k++) //圈起來的格子的每一格位置
					{
						p.x = (i + k / 2) % 4;//x
						p.y = (j + k % 2) % 4;//y
						pos.push_back(p);//x, y
					}

					if (i == 0 && j == 0)
						set(c, 22, " 0 2 0 2", pos);
					else if (i == 0 && j == 1)
						set(c, 22, " 0 2 2 1", pos);
					else if (i == 0 && j == 2)
						set(c, 22, " 0 2 1 2", pos);
					else if (i == 0 && j == 3)
						set(c, 22, " 0 2 2 0", pos);

					else if (i == 1 && j == 0)
						set(c, 22, " 2 1 0 2", pos);
					else if (i == 1 && j == 1)
						set(c, 22, " 2 1 2 1", pos);
					else if (i == 1 && j == 2)
						set(c, 22, " 2 1 1 2", pos);
					else if (i == 1 && j == 3)
						set(c, 22, " 2 1 2 0", pos);

					else if (i == 2 && j == 0)
						set(c, 22, " 1 2 0 2", pos);
					else if (i == 2 && j == 1)
						set(c, 22, " 1 2 2 1", pos);
					else if (i == 2 && j == 2)
						set(c, 22, " 1 2 1 2", pos);
					else if (i == 2 && j == 3)
						set(c, 22, " 1 2 2 0", pos);

					else if (i == 3 && j == 0)
						set(c, 22, " 2 0 0 2", pos);
					else if (i == 3 && j == 1)
						set(c, 22, " 2 0 2 1", pos);
					else if (i == 3 && j == 2)
						set(c, 22, " 2 0 1 2", pos);
					else if (i == 3 && j == 3)
						set(c, 22, " 2 0 2 0", pos);

					answer.push_back(c);
				}
			}
		}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 22 && duplicate(answer[i], map, usetimes)) //為 1 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //有為1卻沒被圈到的就代表尚未完成
			return false;
	return true; //1的都圈到了，完成了
}

bool two(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	bool have_1;

	//---------------1 x 2---------------
	
	for (int i = 0; i < 4; i++) //每1層1層看，要看4次，由上到下
		for (int j = 0; j < 4; j++) //每1層1層看，要看4次，由左到右
		{
			have_1 = false;
			for (int k = 0; k < 2; k++) //左右各一，共2
			{
				if (mapEX[i][j + k] == '0') //有一個0就不能圈了
					break;
				else if (mapEX[i][j + k] == '1') //有1，記錄下來
					have_1 = true;

				if (k == 1 && have_1) //有1才做
				{
					for (int k = 0; k < 2; k++) //使用次數增加
						usetimes[i][(j + k) % 4]++;

					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 2; k++) //圈起來的格子的每一個位置
					{
						p.x = i;//x
						p.y = (j + k) % 4;//y
						pos.push_back(p);//x, y
					}

					if (i == 0 && j == 0)
						set(c, 12, " 0 0 0 2", pos);
					else if (i == 0 && j == 1)
						set(c, 12, " 0 0 2 1", pos);
					else if (i == 0 && j == 2)
						set(c, 12, " 0 0 1 2", pos);
					else if (i == 0 && j == 3)
						set(c, 12, " 0 0 2 0", pos);

					else if (i == 1 && j == 0)
						set(c, 12, " 0 1 0 2", pos);
					else if (i == 1 && j == 1)
						set(c, 12, " 0 1 2 1", pos);
					else if (i == 1 && j == 2)
						set(c, 12, " 0 1 1 2", pos);
					else if (i == 1 && j == 3)
						set(c, 12, " 0 1 2 0", pos);

					else if (i == 2 && j == 0)
						set(c, 12, " 1 1 0 2", pos);
					else if (i == 2 && j == 1)
						set(c, 12, " 1 1 2 1", pos);
					else if (i == 2 && j == 2)
						set(c, 12, " 1 1 1 2", pos);
					else if (i == 2 && j == 3)
						set(c, 12, " 1 1 2 0", pos);

					else if (i == 3 && j == 0)
						set(c, 12, " 1 0 0 2", pos);
					else if (i == 3 && j == 1)
						set(c, 12, " 1 0 2 1", pos);
					else if (i == 3 && j == 2)
						set(c, 12, " 1 0 1 2", pos);
					else if (i == 3 && j == 3)
						set(c, 12, " 1 0 2 0", pos);

					answer.push_back(c);
				}
			}
		}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 12 && duplicate(answer[i], map, usetimes)) //為 1 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------2 x 1---------------
	
	for (int i = 0; i < 4; i++) //每1層1層看，要看4次，由上到下
		for (int j = 0; j < 4; j++) //每1層1層看，要看4次，由左到右
		{
			have_1 = false;
			for (int k = 0; k < 2; k++) //上下各一，共2
			{
				if (mapEX[i + k][j] == '0') //有一個0就不能圈了
					break;
				else if (mapEX[i + k][j] == '1') //有1就記錄下來
					have_1 = true;

				if (k == 1 && have_1) //有1才做
				{
					for (int k = 0; k < 2; k++) //使用次數增加
						usetimes[(i + k) % 4][j]++;

					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 2; k++) //圈起來的格子的每一格位置
					{
						p.x = (i + k) % 4;//x
						p.y = j;//y
						pos.push_back(p);//x, y
					}

					if (i == 0 && j == 0)
						set(c, 21, " 0 2 0 0", pos);
					else if (i == 0 && j == 1)
						set(c, 21, " 0 2 0 1", pos);
					else if (i == 0 && j == 2)
						set(c, 21, " 0 2 1 1", pos);
					else if (i == 0 && j == 3)
						set(c, 21, " 0 2 1 0", pos);

					else if (i == 1 && j == 0)
						set(c, 21, " 2 1 0 0", pos);
					else if (i == 1 && j == 1)
						set(c, 21, " 2 1 0 1", pos);
					else if (i == 1 && j == 2)
						set(c, 21, " 2 1 1 1", pos);
					else if (i == 1 && j == 3)
						set(c, 21, " 2 1 1 0", pos);

					else if (i == 2 && j == 0)
						set(c, 21, " 1 2 0 0", pos);
					else if (i == 2 && j == 1)
						set(c, 21, " 1 2 0 1", pos);
					else if (i == 2 && j == 2)
						set(c, 21, " 1 2 1 1", pos);
					else if (i == 2 && j == 3)
						set(c, 21, " 1 2 1 0", pos);

					else if (i == 3 && j == 0)
						set(c, 21, " 2 0 0 0", pos);
					else if (i == 3 && j == 1)
						set(c, 21, " 2 0 0 1", pos);
					else if (i == 3 && j == 2)
						set(c, 21, " 2 0 1 1", pos);
					else if (i == 3 && j == 3)
						set(c, 21, " 2 0 1 0", pos);

					answer.push_back(c);
				}
			}
		}

	for (int i = 0; i < answer.size(); i++) //確認是否有沒必要圈的
		if (answer[i].type == 21 && duplicate(answer[i], map, usetimes)) //為 1 x 4 且重複的
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //確認重複了，被圈次數全部減一
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //有1卻沒被圈到代表尚未完成
			return false;
	return true; //1的都圈到了，結束
}

void one(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	//---------------1 x 1---------------
	
	for (int i = 0; i < 4; i++) //每1個1個看，要看4次，由上到下
		for (int j = 0; j < 4; j++) //每1個1個看，要看4次，由左到右
			if (mapEX[i][j] == '1' && usetimes[i][j] == 0) //有1才做
			{
				usetimes[i][j]++; //使用次數增加

				Circle c;
				vector< position > pos;
				position p;				
				p.x = i;//x
				p.y = j;//y
				pos.push_back(p);//x, y
				

				if (i == 0 && j == 0)
					set(c, 11, " 0 0 0 0", pos);
				else if (i == 0 && j == 1)
					set(c, 11, " 0 0 0 1", pos);
				else if (i == 0 && j == 2)
					set(c, 11, " 0 0 1 1", pos);
				else if (i == 0 && j == 3)
					set(c, 11, " 0 0 1 0", pos);

				else if (i == 1 && j == 0)
					set(c, 11, " 0 1 0 0", pos);
				else if (i == 1 && j == 1)
					set(c, 11, " 0 1 0 1", pos);
				else if (i == 1 && j == 2)
					set(c, 11, " 0 1 1 1", pos);
				else if (i == 1 && j == 3)
					set(c, 11, " 0 1 1 0", pos);

				else if (i == 2 && j == 0)
					set(c, 11, " 1 1 0 0", pos);
				else if (i == 2 && j == 1)
					set(c, 11, " 1 1 0 1", pos);
				else if (i == 2 && j == 2)
					set(c, 11, " 1 1 1 1", pos);
				else if (i == 2 && j == 3)
					set(c, 11, " 1 1 1 0", pos);

				else if (i == 3 && j == 0)
					set(c, 11, " 1 0 0 0", pos);
				else if (i == 3 && j == 1)
					set(c, 11, " 1 0 0 1", pos);
				else if (i == 3 && j == 2)
					set(c, 11, " 1 0 1 1", pos);
				else if (i == 3 && j == 3)
					set(c, 11, " 1 0 1 0", pos);

				answer.push_back(c);
			}
}

void execute(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	//把它變成5 x 5，方便跑迴圈
	for (size_t i = 0; i < 16; i++)
	{
		mapEX[i / 4][i % 4] = map[i / 4][i % 4];
	}
	for (size_t i = 0; i < 4; i++)
	{
		mapEX[i][4] = map[i][0];
		mapEX[4][i] = map[0][i];
	}
	mapEX[4][4] = mapEX[0][0];

	//從大的開始找，依序找下去
	if (!sixteen(map, mapEX, usetimes, answer))
	{
		if (!eight(map, mapEX, usetimes, answer))
		{
			if (!four(map, mapEX, usetimes, answer))
			{
				if (!two(map, mapEX, usetimes, answer))
				{
					one(map, mapEX, usetimes, answer);
				}
			}
		}
	}
}

int main()
{
	//-----------------------------------read file----------------------------------------//

	string data;

	ifstream infile("Case1", ios::in);
	if (!infile.good())
	{
		infile.close();
		cout << " open fail!!";
	}
	for (string s; !infile.eof(); )
	{
		infile >> s;
		data += s;
	}
	infile.close();

	//-----------------------------------read file----------------------------------------//

	int caseNumber = data[0] - '0';
	int caseCount = 0;

	for (; caseNumber--; caseCount++)
	{
		char map[4][4];
		char mapEX[5][5];
		int usetimes[4][4] = { 0 };
		vector< Circle > answer;

		for (size_t i = 0, k = 1 + caseCount * 16; i < 4; i++, k += 4)
			for (size_t j = 0; j < 4; j++)
				map[i][j] = data[k + j];

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
				cout << map[i][j];
			cout << endl;
		}

		cout << endl;

		cout << " #" << caseCount + 1 << endl;
		
		execute(map, mapEX, usetimes, answer);

		for (int i = 0; i < answer.size(); i++)
		{
			cout << answer[i].minterm << endl;
		}
		cout << endl;

		//-----------------------------------write file----------------------------------------//

		ofstream outfile("Answer", ios::app);
		if (!outfile.good())
		{
			outfile.close();
			std::cout << "Answer" << " write fail!!";
		}
		outfile << " #" << caseCount + 1 << endl;
		for (int i = 0; i < answer.size(); i++)
		{
			outfile << answer[i].minterm << endl;
		}
		
		outfile << endl;
		outfile.close();

		//-----------------------------------write file----------------------------------------//
	}

	system("pause");
	return 0;
}