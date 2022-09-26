#include <iostream>
#include <list>
#include<vector>
#include<chrono>
using namespace std;

//Fatima Rahimova 150180905

//Class is useful for creating undirected graphs
class UndirectedGraph
{
	int vertices; // number of nodes in the graph
	vector<vector<int>> adjacency_list; // vector of vector 
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

	vector<int> graph_coloring()
	{
		vector<int> final_graph(vertices, -1); //creating vector that stores int value
		// size of this vector is equal to the value (the number of) of vertices
		// all values in this vector is equal to -1
		final_graph[0] = 0; //coloring vertex1 with color1

		vector<bool> remaining_colors(vertices, false); // creating remaining colors vector
		// keeps available colors for vertices
		//its size is equal to the value (the number of) vertices
		// all values in it is equal to false

		//coloring whole graph
		for (int u = 1; u < vertices; u++) {

			//iterating all adjacent nodes
			for (int& i : adjacency_list[u]) {
				if (final_graph[i] != -1)
					remaining_colors[final_graph[i]] = true;
			}
			// assigning color to the nodes 
			// and converting all colors to "false" again for following iterations

			for (int color = 0; color < vertices; color++)
			{
				if (!remaining_colors[color])
				{
					final_graph[u] = color;
					for (int& i : adjacency_list[u]) {
						if (final_graph[i] != -1)
							remaining_colors[final_graph[i]] = false;
					}
					break;
				}
			}
		}

		return final_graph;
	}

};
// function for printing necessary info
void printColors(vector<int> final_graph)
{
	int num_of_Colors = final_graph[0]; // represent min num of colors for coloring graph
	for (int u = 0; u < final_graph.size(); u++) { // for all vertices

		cout << "Vertex " << u + 1 << " ---> Color "
			<< (final_graph[u] + 1) << endl; // printing vertex and assigned color as intended in hw booklet
		if (final_graph[u] > num_of_Colors) // in order to find what is maximum color number assigned to vertices
		{
			num_of_Colors = final_graph[u]; // assigned this value to min number of colors for printing
		}
	}
	cout << "Number of different colors : " << num_of_Colors + 1 << endl;
}

int main()
{
	// starting time 
	auto start_time = chrono::high_resolution_clock::now();
	// creating graph
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


	// coloring graph
	auto final_graph = g1.graph_coloring();
	//stopping time
	auto stop_time = chrono::high_resolution_clock::now();
	//calculating duration between start and end time
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);
	// printing required information
	printColors(final_graph);
	//printing duration
	cout << "Time: " << duration.count() << endl;

	return 0;
}
