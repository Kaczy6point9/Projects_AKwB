// AKwB_Project_ZADIII.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>


using namespace std;



void prase_qual(fstream& file)
{
	fstream parsed;
	string line;
	int line_num = 1;
	parsed.open("parsed.qual", ios::out);

	while(file)
	{
		getline(file, line);

        if(line_num % 2 == 0) 
        {
            parsed << line << endl;
        }
        line_num++; 
	}
	parsed.close();
}

class Sequence
{
protected:
	int len;
	int index;
	string nucleotides;
	vector <int> qual;

public:
	void add_sequence(string seq)
	{

		this->nucleotides.append(seq);
		this->len = nucleotides.size();
	}

	void set_index(int size)
	{
		this->index = size;
	}

	void qual_add(int qual)
	{
		this->qual.push_back(qual);
	}

	void resize_qual()
	{
		this->qual.resize(this->len);
	}

	int get_len()
	{
		return this->len;
	}

	int get_index()
	{
		return this->index;
	}

	string get_seq()
	{
		return this->nucleotides;
	}

	int get_one_qual(int index)
	{
		return this->qual[index];
	}

	void print()
	{
		cout << this->index << " " << this->len << endl << this->nucleotides << endl;
		for (int i = 0; i < len; i++)
		{
			cout << this->qual[i] << " ";
		}
		cout << endl;
	}

};

class Instance
{

protected:
	vector<Sequence*> sequences;

public:
	void add_seq(fstream& file)
	{
		string line;
		while (file)
		{
			getline(file, line);
			if (line.size())
			{
				if (line[0] == '>')
				{
					Sequence *v = new Sequence();
					v->set_index(sequences.size());
					getline(file, line);
					v->add_sequence(line);
					sequences.push_back(v);
				}

			}

		}

	}

	void add_qual(fstream& file)
	{

		int seq_num = 0;
		int seq_len;
		int qual;
		while (file)
		{

			seq_len = sequences[seq_num]->get_len();
			for (int i = 0; i < seq_len; i++)
			{
				file >> qual;
				sequences[seq_num]->qual_add(qual);
			}
			seq_num++;
			if (seq_num >= sequences.size())
				break;

		}


	}

	int get_size()
	{
		return sequences.size();
	}

	void show_vector()
	{

		for (int i = 0; i < sequences.size(); i++)
		{
			sequences[i]->print();
		}
		cout << endl;

	}

	int get_len_seq(int id_seq)
	{
		return sequences[id_seq]->get_len();
	}

	int get_index_seq(int id_seq)
	{
		return sequences[id_seq]->get_index();
	}

	string get_seq_seq(int id_seq)
	{
		return sequences[id_seq]->get_seq();
	}

	int get_qual_seq(int id_seq, int index)
	{
		return sequences[id_seq]->get_one_qual(index);
	}


};

class Vertex
{
protected:
	string label; //podicąg - nasza etykieta w grafie
	int position;
	int seq_index;
	int degree;
	vector<int> label_qual; //jakosc podciagu

public:
	void add_info(int index, string label, int degree, int position)
	{
		this->seq_index = index;
		this->label = label;
		this->degree = degree;
		this->position = position;

	}

	void qual_add(int qual)
	{
		this->label_qual.push_back(qual);
	}

	string get_label()
	{
		return this->label;
	}

	int get_seq_index()
	{
		return this->seq_index;
	}

	int get_position()
	{
		return this->position;
	}

	int get_degree()
	{
		return this->degree;
	}

	int get_qual_nucl(int index)
	{
		return this->label_qual[index];
	}

	void change_degree(int degree)
	{
		this->degree = degree;
	}

	void print()
	{
		cout << this->seq_index << " " << this->position << " " << this -> degree << endl << this->label << endl;
		for (int i = 0; i < label_qual.size(); i++)
		{
			cout << this->label_qual[i] << " ";
		}
		cout << endl;
	}


};



class Graph
{
protected:
	vector <Vertex*> vertices;
	vector <int> max_found_clique;
	vector <vector <int> > clique_series;
	

public:
	
	Graph(Instance* new_instance, int window)
	{
		int seq_num;
		seq_num = new_instance->get_size();
		for(int sequence = 0; sequence < seq_num; sequence++)
		{
			for(int i = 0; i < new_instance->get_len_seq(sequence) - window + 1; i++)
			{
				Vertex *new_vertex = new Vertex();
				new_vertex->add_info(new_instance->get_index_seq(sequence), new_instance->get_seq_seq(sequence).substr(i, window), 0, i);
				for (int j = 0; j < window; j++)
				{
					new_vertex->qual_add(new_instance->get_qual_seq(sequence, i + j));
				}
				vertices.push_back(new_vertex);
			}
		}
	}

	int get_verticies_size()
	{
		return this->vertices.size();
	}

	void show_vector()
	{

		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i]->print();
		}
		cout << endl;

	}

	

	void connect_verticies(int deletion_parametr, int window, int **matrix)
	{
		string nucleotide1, nucleotide2;
		int deletion_counter = 0;
		int marker;
		int max_deletion_inside = window/2 - 1;
		int graph_size = this->vertices.size();

		for(int i = 0; i < graph_size; i++)
		{
			for(int j = 0; j < graph_size; j++)
			{
				deletion_counter = 0;
				marker=0;

				if(this->vertices[i]->get_seq_index() == this->vertices[j]->get_seq_index())
					continue;
				if(this->vertices[i]->get_label() == this->vertices[j]->get_label())
				{
					matrix[i][j] = 1;
					matrix[j][i] = 1;
					continue;
				}
				string tmp_lable = vertices[i]->get_label();
				int counter = 0;
				for(int k = 0; counter < tmp_lable.size(); k++)
				{
					deletion_counter = k -counter;
					if(deletion_counter > max_deletion_inside)
					{
						marker = 1;
						break;
					}
					
					nucleotide1 = tmp_lable.substr(counter, 1);
					nucleotide2 = vertices[j]->get_label().substr(counter, 1);

					if(nucleotide1 != nucleotide2)
					{
						if(vertices[i]->get_qual_nucl(k) < deletion_parametr)
						{
							tmp_lable.erase(counter, 1);
						}
						else
						{
							marker = 1;
							break;
						}
					}
					else
						counter++;
				}
				if(marker == 0)
				{
					matrix[i][j] = 1;
					matrix[j][i] = 1;
				}
			}
		}
	}

	void change_degree(int **matrix)
	{
		int degree = 0;
		for(int i = 0; i < this->vertices.size(); i++)
		{
			for(int j = 0; j < this->vertices.size(); j++)
			{
				degree = degree + matrix[i][j];
			}
			vertices[i]->change_degree(degree);
			degree=0;
		}
	}
	
	vector <int> look_for_neighbors(int vertex_index, int **matrix)
	{
		vector <int> neighbors;
		for(int i = 0; i < this->vertices.size(); i++)
		{
			if(matrix[vertex_index][i] == 1)
				neighbors.push_back(i);
		}
		return neighbors;
	}

	vector <int> best_neighbors(int vertex_index, int degree, int **matrix)
	{
		vector <int> best_neighbors;

		for(int i = 0; i < this->vertices.size(); i++)
		{
			if(matrix[vertex_index][i] == 1 && vertices[i]->get_degree() >= degree)
				best_neighbors.push_back(i);
		}
		return best_neighbors;
	}

	vector <int> find_common_neighbors(vector <int> selectec_neighbours, vector <int> best_degree_vertex_neighbours)
	{
		vector <int> common_neighbors;
		set_intersection(selectec_neighbours.begin(), selectec_neighbours.end(), best_degree_vertex_neighbours.begin(), best_degree_vertex_neighbours.end(), back_inserter(common_neighbors));

		return common_neighbors;
	}

	int find_best_degree_vertex(int **matrix, vector<int> neighbors)
	{
		int max_degree_vertex = 0;

		for (int i = 0; i < neighbors.size(); i++)
		{
			int tmp_index = neighbors[i];
			if(vertices[tmp_index]->get_degree() > max_degree_vertex)
				max_degree_vertex = tmp_index;
		}

		return max_degree_vertex;
	}

	vector <int> &clique(vector <int> &candidates, vector<int> neighbors, int size, int degree, int **matrix)
	{
		if(neighbors.empty())
		{
			if(size > degree)
			{
				return candidates;
			}
		}
		
		int max_degree_vertex = find_best_degree_vertex(matrix, neighbors);
		candidates.push_back(max_degree_vertex);
		
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (neighbors[i] == max_degree_vertex)
				neighbors.erase(neighbors.begin() + i);
		}

		vector <int> neighbors_of_max_degree_vertex = best_neighbors(max_degree_vertex, degree, matrix);
		vector <int> common_neighbors = find_common_neighbors(neighbors, neighbors_of_max_degree_vertex);
		clique(candidates, common_neighbors, size + 1, degree, matrix);

		return candidates;
	}

	void max_clique(int **matrix, int degree)
	{
		vector <int> candidates;
		for (int i = 0; i < this->vertices.size(); i++)
		{
			candidates.push_back(i);
			if(vertices[i]->get_degree() >= degree)
			{
				vector<int> selected_neighbours;
				vector<int> neighbors = look_for_neighbors(i, matrix);

				for (int j = 0; j < neighbors.size(); j++)
				{
					int tmp_index = neighbors[j];
					if(vertices[i]->get_degree() >= degree)
						selected_neighbours.push_back(tmp_index);
				}

				vector<int> clique_now = clique(candidates, selected_neighbours, 1, degree, matrix);
				if (clique_now.size() > this->max_found_clique.size())
					this->max_found_clique = clique_now;

			}
			candidates.clear();
		}
	}

	int max_clique_size()
	{
		return max_found_clique.size();
	}

	void create_clique_series()
	{
		this->clique_series.push_back(max_found_clique);
	}

	void look_left(int **matrix)
	{
		for (int i = 0; i < this->clique_series[0].size(); i++)
		{
			if(this->clique_series[0][i] == 0)
				return;
			if (this->vertices[this->clique_series[0][i]]->get_seq_index() != this->vertices[this->clique_series[0][i] - 1]->get_seq_index())
				return;
			for (int j = i + 1; j < this->clique_series[0].size(); j++)
			{
				if (matrix[this->clique_series[0][i] - 1][this->clique_series[0][j] - 1] != 1)
					return;
			}
		}
		vector <int> tmp_series;
		for (int i = 0; i < this->clique_series[0].size(); i++)
		{
			tmp_series.push_back(this->clique_series[0][i] - 1);
		}
		this->clique_series.insert(this->clique_series.begin(), tmp_series);
		look_left(matrix);
		return;
	}

	void look_right(int **matrix)
	{
		for (int i = 0; i < this->clique_series[this->clique_series.size() - 1].size(); i++)
		{
			if (clique_series[this->clique_series.size() - 1][i] == this->vertices.size() - 1)
				return;
			if(this->vertices[this->clique_series[this->clique_series.size() - 1][i]]->get_seq_index() != this->vertices[this->clique_series[this->clique_series.size() - 1][i]+1]->get_seq_index())
				return;
			for (int j = i + 1; j < this->clique_series[this->clique_series.size() - 1].size(); j++)
				{
					if (matrix[this->clique_series[this->clique_series.size() - 1][i] + 1][this->clique_series[this->clique_series.size() - 1][j] + 1] != 1)
						return;
				}
		}
		vector <int> tmp_series;
		for (int i = 0; i < this->clique_series[this->clique_series.size() - 1].size(); i++)
		{
			tmp_series.push_back(this->clique_series[this->clique_series.size() - 1][i] + 1);
		}
		
		this->clique_series.push_back(tmp_series);
		look_right(matrix);
		return;

	}

	void print_found_labels(Instance *new_instance, int window)
	{
		int seq_num = 0;
		int begining = 0;
		int ending = 0;
		int len = 0;

		for(int i = 0; i < this->clique_series[0].size(); i++)
		{
			seq_num = vertices[clique_series[0][i]]->get_seq_index();
			cout << "In sequence number: " << seq_num << ": ";
			begining = vertices[clique_series[0][i]]->get_position();
			ending = vertices[clique_series[0][i]]->get_position() + window - 1;
			cout << "Starting at position: " << begining << " ending at position: " << ending << ":  ";
			len = ending - begining + 1;
			cout << (new_instance->get_seq_seq(seq_num).substr(begining, len)) << endl;
		}
	}

};






int _tmain(int argc, _TCHAR* argv[])
{
	Instance new_instance;
	fstream fasta;
	fstream qual;
	int window;
	int deletion_parametr;
	int **matrix;
	

	cout << "Podaj wielkosc okna jaka ma byc sprawdzana: ";
	cin >> window;
	cout << endl;
	cout << "Podaj parametr delecji: ";
	cin >> deletion_parametr;
	cout << endl;


	fasta.open("instance1.fasta", ios::in);
	if(fasta)
	{
		new_instance.add_seq(fasta);
		fasta.close();
	}
	else
	{
		cout << "Can't open the fasta file" << endl;
	}
	qual.open("instance1.qual", ios::in);
	if(qual)
	{
		prase_qual(qual);
		qual.close();
	}
	else
	{
		cout << "Can't open the qual file" << endl;
	}
	qual.open("parsed.qual", ios::in);
	if(qual)
	{
		new_instance.add_qual(qual);
		qual.close();
	}
	else
	{
		cout << "Can't open the qual file" << endl;
	}
	Graph *new_graph = new Graph(&new_instance, window);

		matrix = new int *[new_graph->get_verticies_size()];
		for (int i = 0; i < new_graph->get_verticies_size(); i++)
		{
			matrix[i] = new int[new_graph->get_verticies_size()];
			for (int j = 0; j < new_graph->get_verticies_size(); j++)
				matrix[i][j] = 0;
		}
	


	
	new_graph->connect_verticies(deletion_parametr, window, matrix);
	new_graph->change_degree(matrix);
	new_graph->max_clique(matrix, 3);
	new_graph->create_clique_series();
	new_graph->look_left(matrix);
	new_graph->look_right(matrix);
	new_graph->print_found_labels(&new_instance, window);
	//new_graph->show_vector();
	//new_instance.show_vector();

	system("PAUSE");
	return 0;
}

