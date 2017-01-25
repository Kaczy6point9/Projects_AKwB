// AKwB_Project_ZADIV.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <fstream>

using namespace std;

double start = 0; //time var
double end_t = 0; //time var


void generate_instance(int power, int cuts)
{
	/*code it*/
}

bool is_empty_vec(vector<int> v)
{
	int tmp;
	for (int i = 0; i < v.size(); i++)
	{
		tmp = v[i];
		if (tmp != 0)
			return false;
	}
	return true;
}


void print_vector(vector <int> printed)
{
	for (int i = 0; i < printed.size(); i++)
	{
		cout << i << ": ";
		cout << printed[i] << endl;
	}
	cout << endl;
}

double _time(clock_t time)
{
	return static_cast <double> (time) / CLOCKS_PER_SEC;
}

bool can_be_result(int index, vector <int> &result, vector <int> &to_use, vector <int> &used)
{
	int value = index;
	vector <int> tmp_to_use;
	tmp_to_use = to_use;
	vector <int> tmp_used;
	tmp_used = used;

	tmp_to_use[index]--;

	int searched = value;
	for (int i = result.size() - 1; i >= 0; i--)
	{
		searched = searched + result[i];
		if (searched < tmp_to_use.size() && tmp_to_use[searched] > 0)
		{
			tmp_to_use[searched]--;
			tmp_used.push_back(searched);
		}
		else
		{
			return false;
		}
	}
	result.push_back(value);
	to_use = tmp_to_use;
	used = tmp_used;

	return true;
}


int find_res(vector <int> &result, vector<int> to_use, int cut_count, vector <int> used)
{

	int tmp;
	for (int i = 1; i < to_use.size(); i++)
	{
		if (to_use[i] > 0)
		{
			if (can_be_result(i, result, to_use, used))
			{
				if (result.size() == (cut_count + 1) && is_empty_vec(to_use) == true)
				{
					cout << "Result is : ";
					print_vector(result);
					end_t = _time(clock());
					cout << "Time was: " << end_t - start << endl;
					system("PAUSE");
					exit(0);
				}
				else
				{
					find_res(result, to_use, cut_count, used);
					tmp = result[result.size() - 1];
					result.pop_back();
					to_use[tmp]++;
					for (int j = 0; j < result.size(); j++)
					{
						tmp = used[used.size() - 1];
						used.pop_back();
						to_use[tmp]++;
					}

				}
			}
		}
	}
	return 0;
}




int _tmain(int argc, _TCHAR* argv[])
{
	int cut_count;
	int tmp_var;
	cout << "Podaj ilosc ciec: ";
	cin >> cut_count;
	cout << endl;
	int multiset_power = ((cut_count + 2)* (cut_count + 1)) / 2;
	vector <int> instance;
	vector <int> result;
	vector <int> used;
	vector <int> to_use;
	srand(time(NULL));
	fstream read_instance;
	read_instance.open("ins-PDP-11a-asc.txt", ios::in);
	if (read_instance)
	{
		while (read_instance)
		{
			read_instance >> tmp_var;
			instance.push_back(tmp_var);
		}
	}
	else
	{
		cout << "Nie udalo sie otworzyc pliku!" << endl;
	}
	read_instance.close();
	instance.pop_back();


	if (instance.size() > multiset_power)
	{
		cout << "Za duzo elementow!" << endl;
	}
	else if (instance.size() < multiset_power)
	{
		cout << "Za malo elementow!" << endl;
	}
	else
	{
		sort(instance.begin(), instance.end());
		to_use.resize(instance[instance.size() - 1] + 1);
		for (int i = 0; i < to_use.size(); i++)
		{
			to_use[i] = 0;
		}
		for (int i = 0; i < instance.size(); i++)
		{
			tmp_var = instance[i];
			to_use[tmp_var]++;
		}
		int first_element = instance[instance.size() - 1] - instance[instance.size() - 2]; //pierwszy element wektora wynikowego
		result.push_back(first_element);
		to_use[first_element]--;

		start = _time(clock());
		find_res(result, to_use, cut_count, used);
		cout << "Brak rozwiazan";

	}
	//print_vector(result);
	system("PAUSE");
	return 0;
}

