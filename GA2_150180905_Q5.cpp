#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <utility>
#include <algorithm>

using namespace std;

//Fatima Rahimova 150180905

//Class is useful for creating undirected graphs
class UndirectedGraph
{
private:
	int vertices; // number of nodes in the graph
	vector<vector<int>> adjacency_list;  // vector of vector 

	struct node //struct node that keeps vertices in our graph
	{
		int id; // id or number of the node
		int degree; //degree of the node
		int color; //color of the node

		node(int id, int degree) //constructor
			: id(id), degree(degree), color(-1) {}

		bool operator<(const node& other) const // overloading < operator
		{
			return (this->degree < other.degree) || (this->degree == other.degree && this->id > other.id);
		}
	};
public:
	//constructor
	UndirectedGraph(int vertices)
		: vertices(vertices), adjacency_list(vertices)
	{ }
	//adding edge between 2 nodes
	void create_edge(int node1, int node2)
	{
		adjacency_list[node1].push_back(node2);
		adjacency_list[node2].push_back(node1);
	}
	
	vector<int> degreeColoring()
	{
		vector<node> degree_list; //creating degree_list as intended in hw booklet
		//adding nodes to degree_list
		for (int i = 0; i < adjacency_list.size(); i++)
		{
			degree_list.emplace_back(i, adjacency_list[i].size());
			// degree_list.push_back(node(i, adjacency_list[i].size()));
			// this commented line is exactly same with the first line in the for loop
			// but emplace_back is much more fast
		}
		//sorting degree_list in descending order of degrees
		std::sort(degree_list.begin(), degree_list.end(),
			[](node& left, node& right) {
				return right < left; // I already overloaded < operator
			}
		);
		int colored = 0;
		int color = 0;
		while (colored < degree_list.size()) {
			color++; // increasing color by 1
			vector<int> printing; // it stores dropped vertices
			vector<node*> copied_list; // is created for copying degree_list inside it
			// copying degree_list to copied_list
			for (int i = 0; i < degree_list.size(); i++)
			{
				copied_list.push_back(&degree_list[i]);
			}
			// if node is already clored delete it from copied list
			copied_list.erase(remove_if(copied_list.begin(), copied_list.end(),
				[&](node* el) {
					if (el->color + 1 == color) {
						printing.push_back(el->id);
						if (printing.front() != printing.back()) 

							//printing dropped vertices
							// +1 added because node1 is represented as node0 in code
							// so for example, instead of printing node0 we should print node 1
							cout << "Vertices " << printing.front() + 1 << ", " << printing.back() + 1 << " are dropped!!" << endl;
						
					}
					
					return el->color != -1;
				}),
				copied_list.end()
					);
			while (true) {
				colored++; // increasing color by 1
				copied_list[0]->color = color; // making first vertex colored
				auto neighs = adjacency_list[copied_list[0]->id];
				cout << "Checking " << (copied_list[0]->id) + 1 << " ---> true" << endl;

				cout << "Vertex " << (copied_list[0]->id) + 1 << " ---> Color" << color << endl;
				copied_list.erase(copied_list.begin());
				// deleting vertex' adjacent nodes from list
				copied_list.erase(remove_if(copied_list.begin(), copied_list.end(),
					[&](node* el) {
						for (auto n : neighs) {
							if (n == el->id)
							{
								cout << "Checking " << (el->id + 1) << " ---> " << "false" << endl;
								return true;
							}
						}
						return false;
					}),
					copied_list.end());
				if (copied_list.size() == 0) // check the size of copied_list
					// if there is any element go to making first element colored
					// I explained this pseudo code in my report as well
					break;
			}

		}

		vector<int> results(vertices); // final result list is derived from degree_list
		for (const node& n : degree_list)
			results[n.id] = n.color;
		cout << "Min color num:" << color << endl; //printing minimum number of the color

		return results;
	}

};

int main()
{
	//starting time
	auto start_time = chrono::high_resolution_clock::now();
	//creating graph
	UndirectedGraph g1(35);
	g1.create_edge(0, 1);
	// there is edge between node 1 and node 2 in the graph
	// 1 is subtracted from node numbers
	g1.create_edge(0, 6);
	g1.create_edge(1, 5);
	g1.create_edge(1, 2);
	g1.create_edge(2, 3);
	g1.create_edge(3, 4);
	g1.create_edge(3, 10);
	g1.create_edge(3, 11);
	g1.create_edge(4, 5);
	g1.create_edge(5, 6);
	g1.create_edge(5, 9);
	g1.create_edge(6, 7);
	g1.create_edge(6, 8);
	g1.create_edge(7, 8);
	g1.create_edge(7, 20);
	g1.create_edge(8, 9);
	g1.create_edge(8, 19);
	g1.create_edge(9, 10);
	g1.create_edge(9, 17);
	g1.create_edge(9, 19);
	g1.create_edge(10, 11);
	g1.create_edge(10, 16);
	g1.create_edge(11, 12);
	g1.create_edge(12, 13);
	g1.create_edge(12, 15);
	g1.create_edge(13, 14);
	g1.create_edge(14, 15);
	g1.create_edge(14, 26);
	g1.create_edge(15, 16);
	g1.create_edge(15, 26);
	g1.create_edge(16, 17);
	g1.create_edge(16, 24);
	g1.create_edge(16, 25);
	g1.create_edge(17, 18);
	g1.create_edge(17, 31);
	g1.create_edge(18, 22);
	g1.create_edge(18, 23);
	g1.create_edge(19, 20);
	g1.create_edge(19, 21);
	g1.create_edge(20, 21);
	g1.create_edge(21, 22);
	g1.create_edge(21, 33);
	g1.create_edge(21, 34);
	g1.create_edge(22, 23);
	g1.create_edge(22, 32);
	g1.create_edge(23, 31);
	g1.create_edge(23, 32);
	g1.create_edge(24, 25);
	g1.create_edge(24, 29);
	g1.create_edge(25, 26);
	g1.create_edge(25, 29);
	g1.create_edge(26, 29);
	g1.create_edge(26, 27);
	g1.create_edge(27, 28);
	g1.create_edge(28, 29);
	g1.create_edge(28, 30);
	g1.create_edge(29, 31);
	g1.create_edge(30, 29);
	g1.create_edge(30, 31);
	g1.create_edge(31, 32);
	g1.create_edge(32, 33);
	g1.create_edge(33, 34);



	auto res = g1.degreeColoring();
	//stopping time
	auto stop_time = chrono::high_resolution_clock::now();
	//calculating duration between start and end time
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);
	// printing duration time
	cout << "Time: " << duration.count() << endl;

	return 0;
}
