#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct position//�ΨӰO���骺�ϧΪ��y��
{
	int x;
	int y;
};

struct Circle
{
	int type;//�骺�ϧΧΪ�
	string minterm;
	vector < position > pos; //�bKMap�W���y��
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
	bool have_1; //�O�_��1

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '0') //�u�n���@��0�N�����F�A�������X
			return false;
		else if (map[i / 4][i % 4] == '1') //��1�N�O���U��
			have_1 = true;

	if (!have_1) //���S��1�A�]�N�O��2�A�������X
		return true;

	for (int i = 0; i < 16; i++) //�C�ӼƳ��Q��@��
		usetimes[i / 4][i % 4]++;

	Circle c;
	vector< position > pos;
	position p;
	p.x = 0;
	p.y = 0;
	pos.push_back(p);
	set(c, 44, " 2 2 2 2", pos);

	answer.push_back(c); //�x�s����

	return true; //��F�B��i�ϳ��駹�F
}

bool eight(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	//---------------2 x 4---------------

	bool have_1; //�����O�_��1

	for (int i = 0; i < 4; i++) //�C2�h2�h�ݡA�n��4��
	{
		have_1 = false;
		for (int j = 0; j < 8; j++) //�W�B�U�ƦU4��A�@8��
		{
			if (mapEX[i + j / 4][j % 4] == '0') //���@��0�N�����F
				break;
			else if (mapEX[i + j / 4][j % 4] == '1') //��1�A�O���U��
				have_1 = true;

			if (j == 7 && have_1) //��1�~��
			{
				for (int k = 0; k < 8; k++) //�ϥΦ��ƼW�[
					usetimes[(i + k / 4) % 4][k % 4]++; //% 4 �O�]���O����ɪ���k�AĴ�p�Ĥ@�Ƹ�̫�@�ư�

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 8; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 24 && duplicate(answer[i], map, usetimes)) //�� 2 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------4 x 2---------------

	for (int i = 0; i < 4; i++) //�C2�h2�h�ݡA�n��4��
	{
		have_1 = false;
		for (int j = 0; j < 8; j++) //���B�k�ƦU4�A�@8
		{
			if (mapEX[j / 2][i + j % 2] == '0') //���@��0�N�����F
				break;
			else if (mapEX[j / 2][i + j % 2] == '1') //��1�A�O���U��
				have_1 = true;

			if (j == 7 && have_1) //��1�~��
			{
				for (int k = 0; k < 8; k++) //�ϥΦ��ƼW�[
					usetimes[k / 2][(i + k % 2) % 4]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 8; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 42 && duplicate(answer[i], map, usetimes)) //�� 2 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
	{
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //����1�o�S�Q��쪺�N�N��|������
			return false;
	}
	return true; //1�������F�A�����F
}

bool four(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	bool have_1; //�����O�_��1

	//---------------1 x 4---------------

	for (int i = 0; i < 4; i++) //�C1�h1�h�ݡA�n��4��
	{
		have_1 = false;
		for (int j = 0; j < 4; j++) //�@��4��
		{
			if (mapEX[i][j] == '0') //���@��0�N�����F
				break;
			else if (mapEX[i][j] == '1') //��1�A�O���U��
				have_1 = true;

			if (j == 3 && have_1) //��1�~��
			{
				for (int k = 0; k < 4; k++) //�ϥΦ��ƼW�[
					usetimes[i][k]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 4; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 14 && duplicate(answer[i], map, usetimes)) //�� 1 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------4 x 1---------------
	
	for (int i = 0; i < 4; i++) //�C1�h1�h�ݡA�n��4��
	{
		have_1 = false;
		for (int j = 0; j < 4; j++) //�@��4��
		{
			if (mapEX[j][i] == '0') //���@��0�N�����F
				break;
			else if (mapEX[j][i] == '1') //��1�A�O���U��
				have_1 = true;

			if (j == 3 && have_1) //��1�~��
			{
				for (int k = 0; k < 4; k++) //�ϥΦ��ƼW�[
					usetimes[k][i]++;

				Circle c;
				vector< position > pos;
				position p;
				for (int k = 0; k < 4; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 41 && duplicate(answer[i], map, usetimes)) //�� 1 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------2 x 2---------------
	
	for (int i = 0; i < 4; i++) //�C2�h2�h�ݡA�n��4���A�ѤW��U
		for (int j = 0; j < 4; j++) //�C2�h2�h�ݡA�n��4���A�ѥ���k
		{
			have_1 = false;
			for (int k = 0; k < 4; k++) //�W�U�ƦU2�A�@4
			{
				if (mapEX[i + k / 2][j + k % 2] == '0') //���@��0�N�����F
					break;
				else if (mapEX[i + k / 2][j + k % 2] == '1') //��1�A�O���U��
					have_1 = true;

				if (k == 3 && have_1) //��1�~��
				{
					for (int k = 0; k < 4; k++) //�ϥΦ��ƼW�[
						usetimes[(i + k / 2) % 4][(j + k % 2) % 4]++;
										
					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 4; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 22 && duplicate(answer[i], map, usetimes)) //�� 1 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //����1�o�S�Q��쪺�N�N��|������
			return false;
	return true; //1�������F�A�����F
}

bool two(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	bool have_1;

	//---------------1 x 2---------------
	
	for (int i = 0; i < 4; i++) //�C1�h1�h�ݡA�n��4���A�ѤW��U
		for (int j = 0; j < 4; j++) //�C1�h1�h�ݡA�n��4���A�ѥ���k
		{
			have_1 = false;
			for (int k = 0; k < 2; k++) //���k�U�@�A�@2
			{
				if (mapEX[i][j + k] == '0') //���@��0�N�����F
					break;
				else if (mapEX[i][j + k] == '1') //��1�A�O���U��
					have_1 = true;

				if (k == 1 && have_1) //��1�~��
				{
					for (int k = 0; k < 2; k++) //�ϥΦ��ƼW�[
						usetimes[i][(j + k) % 4]++;

					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 2; k++) //��_�Ӫ���l���C�@�Ӧ�m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 12 && duplicate(answer[i], map, usetimes)) //�� 1 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	//---------------2 x 1---------------
	
	for (int i = 0; i < 4; i++) //�C1�h1�h�ݡA�n��4���A�ѤW��U
		for (int j = 0; j < 4; j++) //�C1�h1�h�ݡA�n��4���A�ѥ���k
		{
			have_1 = false;
			for (int k = 0; k < 2; k++) //�W�U�U�@�A�@2
			{
				if (mapEX[i + k][j] == '0') //���@��0�N�����F
					break;
				else if (mapEX[i + k][j] == '1') //��1�N�O���U��
					have_1 = true;

				if (k == 1 && have_1) //��1�~��
				{
					for (int k = 0; k < 2; k++) //�ϥΦ��ƼW�[
						usetimes[(i + k) % 4][j]++;

					Circle c;
					vector< position > pos;
					position p;
					for (int k = 0; k < 2; k++) //��_�Ӫ���l���C�@���m
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

	for (int i = 0; i < answer.size(); i++) //�T�{�O�_���S���n�骺
		if (answer[i].type == 21 && duplicate(answer[i], map, usetimes)) //�� 1 x 4 �B���ƪ�
		{
			for (int j = 0; j < answer[i].pos.size(); j++) //�T�{���ƤF�A�Q�馸�ƥ�����@
				usetimes[answer[i].pos[j].x][answer[i].pos[j].y]--;
			answer.erase(answer.begin() + i);
			i--;
		}

	for (int i = 0; i < 16; i++)
		if (map[i / 4][i % 4] == '1' && usetimes[i / 4][i % 4] == 0) //��1�o�S�Q���N��|������
			return false;
	return true; //1�������F�A����
}

void one(char map[4][4], char mapEX[5][5], int usetimes[4][4], vector< Circle > &answer)
{
	//---------------1 x 1---------------
	
	for (int i = 0; i < 4; i++) //�C1��1�ӬݡA�n��4���A�ѤW��U
		for (int j = 0; j < 4; j++) //�C1��1�ӬݡA�n��4���A�ѥ���k
			if (mapEX[i][j] == '1' && usetimes[i][j] == 0) //��1�~��
			{
				usetimes[i][j]++; //�ϥΦ��ƼW�[

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
	//�⥦�ܦ�5 x 5�A��K�]�j��
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

	//�q�j���}�l��A�̧ǧ�U�h
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