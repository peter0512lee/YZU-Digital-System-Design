#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct SRNode
{	
	string input;
	string output;
	int present_state;
	int next_state;
};

class SR
{
public:
	SR(fstream& fin)
	{
		string buffer;
		SRNode temp;
		for (int i = 0; i < 4; i++)
		{
			getline(fin, buffer, '\n');
			if (buffer[0] == '#')
			{
				i--;
				comment.push_back(buffer);
				continue;
			}
			buffer.erase(0, 2);
			inputs_outputs_states_terms[i] = atoi(buffer.c_str());
		}
		getline(fin, reset_state, '\n');
		reset_state.erase(0, 3);
		while (true)
		{
			getline(fin, buffer, ' ');
			if (buffer[0] == '.')
				break;
			temp.input = buffer;
			getline(fin, buffer, ' ');
			buffer.erase(0, 1);
			temp.present_state = atoi(buffer.c_str());
			getline(fin, buffer, ' ');
			buffer.erase(0, 1);
			temp.next_state = atoi(buffer.c_str());
			getline(fin, buffer, '\n');
			temp.output = buffer;
			transition.push_back(temp);
		}
	}

	void execute()
	{		
		for (size_t i = 0; i < transition.size(); i++)
		{
			for (size_t j = i + 1; j < transition.size(); j++)
			{
				if (transition[i].input == transition[j].input &&
					transition[i].next_state == transition[j].next_state &&
					transition[i].output == transition[j].output)
				{
					transition.erase(transition.begin() + j);
					inputs_outputs_states_terms[2]--;
				}
				
			}
		}
	}

	

	void print_origin()
	{
		cout << endl;
		for (size_t i = 0; i < comment.size(); i++)
			cout << comment[i] << endl;
		cout <<
			".i " << inputs_outputs_states_terms[0] << endl <<
			".o " << inputs_outputs_states_terms[1] << endl <<
			".s " << inputs_outputs_states_terms[2] << endl <<
			".p " << inputs_outputs_states_terms[3] << endl <<
			".r " << reset_state << endl;
		for (size_t i = 0; i < transition.size(); i++)
		{
			cout <<
				transition[i].input << " " <<
				reset_state[0] << transition[i].present_state << " " <<
				reset_state[0] << transition[i].next_state << " " <<
				transition[i].output << endl;
		}
		cout << ".e" << endl << endl;
	}

	void print_afterSR()
	{
		cout << endl;
		for (size_t i = 0; i < comment.size(); i++)
			cout << comment[i] << endl;
		cout <<
			".i " << inputs_outputs_states_terms[0] << endl <<
			".o " << inputs_outputs_states_terms[1] << endl <<
			".s " << inputs_outputs_states_terms[2] << endl <<
			".p " << inputs_outputs_states_terms[3] << endl <<
			".r " << reset_state << endl;
		for (size_t i = 0; i < transition.size(); i++)
		{
			cout <<
				transition[i].input << " " <<
				reset_state[0] << transition[i].present_state << " " <<
				reset_state[0] << transition[i].next_state << " " <<
				transition[i].output << endl;
		}
		cout << ".e" << endl << endl;

	}

private:
	int inputs_outputs_states_terms[4];
	string reset_state;
	vector <string> comment;
	vector <SRNode> transition;
};