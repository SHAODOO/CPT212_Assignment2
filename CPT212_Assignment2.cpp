//======================================================================================================
// CPT212 Assignment 2
// Author for the code of class City and class Graph
// Name       	: AdjacencyMatrixGraphImp.cpp
// Author      	: Amritpal Singh
// Copyright   	: arrayed.net
// Description 	: Array based Adjacency Matrix Graph Implementation
// Cities	  	: Manila, Philippines; Sydney, Australia; Chongqing, China; Rome, Italy; Taipei, Taiwan
// Distance		: MS: 6255		MC: 2237	MR: 10403	MT: 1171
//				: SM: 6255		SC: 8470	SR: 16321	ST: 7262
//				: CM: 2237		CS: 8470	CR: 8178	CT: 1553
//				: RM: 10403 	RS: 16321	RC: 8178	RT: 9606
//				: TM: 1171		TS: 7262	TC: 1553	TR: 9606 
//=======================================================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <cstdlib>
#include <windows.h> 
#include <ctime>
#include <set>
#include <conio.h>

using namespace std;

class Color{ 
  public: 
         Color(int desiredColor){ 
             consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
             color = desiredColor; 
         } 
 
         friend ostream& operator<<(ostream& ss, Color obj){ 
             SetConsoleTextAttribute(obj.consoleHandle, obj.color); 
             return ss; 
         } 
  private: 
         int color; 
         HANDLE consoleHandle; 
}; 

class city
{
	public:
		string title;

		city(string name)
		{
			title = name;
		}
};

class WeightedGraph
{
	private:
		static const int NULL_EDGE = 0;
		vector<city*> cities;
		vector<bool> marks;			// marks[i] is mark for cities[i]
		int nmbCities;
		int maxCities;
		vector< vector<int> > edges;
		
	public:
		// constructor
		WeightedGraph(int size)
		{
			nmbCities = 0;
			maxCities = size;

			cities.resize(size);
			for (int i=0;i<size;i++)	// init cities
				cities[i] = NULL;

			marks.resize(size);

			int rows = size;
			int columns = size;
			edges.resize(rows, vector<int>(columns, 0));
		}
		
		// to clear all the cities and edges of the graph
		void initialization(int size)
		{
			nmbCities = 0;
			maxCities = size;

			cities.resize(size);
			for (int i=0;i<maxCities;i++)	// init cities
				cities[i] = NULL;

			marks.resize(size);

			int rows = size;
			int columns = size;
			edges.resize(rows, vector<int>(columns, 0));

			for (int i=0;i<maxCities;i++)
			{
	            for (int j=0;j<maxCities;j++)
	                edges[i][j]=NULL_EDGE;
	        }
		}

		void add_city(city* aCity)
		{
			cities[nmbCities] = aCity;
			for (int i=0; i<maxCities; i++)
			{
				edges[nmbCities][i] = NULL_EDGE;
				edges[i][nmbCities] = NULL_EDGE;

			}

			nmbCities++;
		}

		void add_edge(int fromCity, int toCity)
		{
			int distance[5][5] = {	{0, 6255, 2237, 10403, 1171}, 
									{6255, 0, 8470, 16321, 7262},
									{2237, 8470, 0, 8178, 1533},
									{10403, 16321, 8178, 0, 9606},
									{1171, 7262, 1533, 9606, 0}};
									
			int row;
			int column;

			row = index_is(cities[fromCity]);
			column = index_is(cities[toCity]);
			edges[row][column] = distance[row][column];
		}
		
		void remove_edge(int fromCity, int toCity)
		{
			edges[fromCity][toCity] = 0;
		}

		int weight_is(int fromCity, int toCity)
			// If edge from fromCity to toCity exists, returns the weight of edge;
			// otherwise, returns a special ??null-edge?? value.
		{
			int row;
			int column;

			row = index_is(cities[fromCity]);
			column = index_is(cities[toCity]);
			return edges[row][column];
		}

		int index_is(city* aCity)
		{
			int i = 0;
			while (i < nmbCities)
			{
				if (cities[i] == aCity)
					return i;
				i++;
			}
			return -1;
		}


		void clear_marks()
		{
			for (int i=0;i<maxCities;i++)
				marks[i] = false;
		}

		void mark_city(city* aCity)
		{
			int ix = index_is(aCity);
			marks[ix] = true;
		}

		bool is_marked(city* aCity)
		// Returns true if city is marked; otherwise, returns false.
		{
			int index = index_is(aCity);
			if (marks[index] == true)
				return true;
			else
				return false;
		}

		city* get_unmarked()
		{
			for (int i=0; i<nmbCities; i++)
			{
				if (marks[i] == false)
					return cities[i];
			}
			return NULL;
		}

		city* getCity(int index)
		{
		    return cities[index];
		}
		
		bool DFS(city* aCity)
		{
			int ix,ix2;
			if (aCity == NULL)
			    return false;

			cout << aCity->title << " ";
			ix = index_is(aCity);
			marks[ix] = true;
			
			for (int i=0; i<nmbCities; i++)
			{
				ix2 = index_is(cities[i]);
				if (edges[ix][ix2] != NULL_EDGE)	// if adj city
				{
					if (marks[i] == false){
						DFS(cities[i]);}
				}
			}

			for (int i=0; i<nmbCities; i++)
			{
				if (marks[i] == false){
					return false;}
			}

			return true;
		}
		
		// Function 2: Print Cycle detected
		void printCycles(int& counting, int sequenceArr[])
        {
            cout << "\tThe detected cycle : " << getCity(sequenceArr[0])->title << " -> ";
            for (int k = counting; k > 0; k--)
                cout << getCity(sequenceArr[k])->title << " -> ";
            cout << getCity(sequenceArr[0])->title << endl << endl;
        }

        // Function 2: Print Cycle detected
		bool isGraphCyclic(int& counting, int sequenceArr[])
		{
		    int color[nmbCities]={0}; //color to mark the condition of cities, not visited/partially visited/completely visited
		    int previousCollect[nmbCities]; //Array to collect all the previous cities
		    int previousCity=-1; //Get previous city

		    for (int i=0; i<nmbCities;i++)
            {
                //initialize all to false state
                clear_marks();
            }

            //test for all the cities as the start city
            for (int i=0; i < nmbCities; i++)
            {
                if(DFS_for_cycle(cities[i],previousCity,color, previousCollect,counting,sequenceArr))
                {
                    return true; //Have cycle in the graph
                }
            }
            return false; //No cycle in the graph
		}

		// Function 2: Print Cycle detected
		bool DFS_for_cycle(city* aCity,int previous, int color[],int previousCollect[],int& counting, int sequenceArr[])
		{
			int ix,ix2; //ix and ix2 hold index of cities

			if (aCity == NULL) //If city not exist
			    return false;

			ix = index_is(aCity);

			if(color[ix]==1) //color of this node is 1, partially visited/visited before and currently visit again
            {
                counting++;
                sequenceArr[counting] = ix;
                int cur = previous;

                while (cur != ix) //for cities that are members of the cycle
                {
                    counting++;
                    sequenceArr[counting] = cur;
                    cur = previousCollect[cur];
                }
                return true; //cycle detected, members marked, end DFS with true
            }
            else if(color[ix]==2) //if Completely visited city
                return false;

            if(marks[ix] == false) //if the city not yet visited
            {
                marks[ix] = true; //mark the city as visited

                previousCollect[ix] = previous; //array mark the previous city adjacent to it
                color[ix] = 1; //partially visited, potential to become member of cycle

                //Modified DFS for cycle, recursive call for all the adj city
                for (int i =0; i<nmbCities; i++)
                {
                    ix2 = index_is(cities[i]);
                    if(edges[ix][ix2]!=NULL_EDGE) //If the edge exist
                    {
                        if(DFS_for_cycle(cities[i],ix,color,previousCollect,counting,sequenceArr))
                        {
                            return true;
                        }
                    }
                }
                color[ix]=2; //completely visited
            }
            return false; //checked all cities but there is no cycle detected, return false
		}

		// Function 3: Check available path
		bool checkPath(int src, int dest) {
				
			stack<int> s;
			int ix,ix2;

			for (int i=0; i<nmbCities;i++) {
				//initialize marks
                clear_marks();
			}

			s.push(src);
			ix = src;

			if (marks[ix] == false)
				marks[ix] = true;

			while(!s.empty())								// While the stack is not empty
			{
				int k = s.top();							// Save the top element before popping it off
				s.pop();

				if(k == dest)								// Break out of the loop if we've reached our destination
				{
					return true;
				}

				for(int i=0; i<nmbCities; i++)						// For all adjacent cities
				{
					ix2 = i;
					if(edges[k][ix2]!=NULL_EDGE && !marks[ix2])	// If they're connected and we haven't visited it yet
					{
						s.push(ix2);						// Add it to our stack, and mark that we've visited it
						marks[ix2] = true;
					}
				}
			}
			
		}

		// Function 3: Shortest Path
		void printPath(int parent[], int src, int dest){
			int current = dest;
			vector <int> print;

			while (current!=src) {
				print.push_back(current);
				current = parent[current];
			}

			cout << getCity(src)->title;

			for (int j = print.size()-1; j >= 0; j--) {
				int k = print[j];
				cout << " -> " << getCity(k)->title;
			}

		}

		int removeMin(int dist[], bool sptSet[], int p[], int dest)
		{
		    // Initialize min value
		    int min = INT_MAX, min_index;

		    for (int v = 0; v < nmbCities; v++)
		        if (sptSet[v] == false && dist[v] <= min)
		            min = dist[v], min_index = v;

		  	// Remove from queue
		  	p[min_index] = INT_MAX;

		    return min_index;
		}

		bool is_empty(int queue[]){
			for (int i = 0; i < nmbCities; i++) {
				if (queue[i] != INT_MAX)
					return false;
			}
			return true;
		}

		void findPath(int src, int dest)
		{
		    int INF = INT_MAX;
			int D[nmbCities]; // hold the shortest distance from src to i
		    bool sptSet[nmbCities]; // sptSet[i] will be true if city i is included in shortest path tree or shortest distance from src to i is finalized

		  	// Priority queue as array
		    int priority[nmbCities];

		  	// Vector to store paths
		  	vector<int> path;
		  	vector<int> shortestPath;

		    // Initialize all distances as INFINITE and stpSet[] as false
		    for (int i = 0; i < nmbCities; i++) {
				D[i] = INF;
				sptSet[i] = false;
			}

		    int parent[nmbCities];

		    // Distance of source city from itself is always 0
		    D[src] = 0;

		    //Insert all distances as keys to priority queue with index as cities
		    for (int i=0; i < nmbCities; i++) {
		    	priority[i] = D[i];
			}

		  	while (!is_empty(priority)) {
		  		int u = removeMin(D, sptSet, priority, dest);

		  		// Mark the picked city as processed
		        sptSet[u] = true;

		        // Update D value of the adjacent cities of the picked city.
		        for (int v = 0; v < nmbCities; v++) {
		            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
		            if (!sptSet[v] && edges[u][v] && D[u] != INF && D[u] + edges[u][v] < D[v]) {
		                D[v] = D[u] + edges[u][v];
						priority[v] = D[v];
						parent[v] = u;
					}
				}
			}
			Sleep(300);
		    cout << "\n\nShortest Path: ";
		    Sleep(300);
		    printPath(parent, src, dest);
		    Sleep(300);
			cout << "\nDistance: ";
			Sleep(300);
			cout << D[dest] << endl << endl;
		}

		void BFS(city* aCity)
		{
			int ix, ix2;
			queue <city*> que;
			ix = index_is(aCity);
			marks[ix] = true;
			que.push(aCity);

			while (!que.empty())
			{
				city* node = que.front();
				que.pop();
				ix = index_is(node);
				cout << node->title << " ";
				for (int i=0; i<nmbCities; i++)
				{
					ix2 = index_is(cities[i]);
					if (edges[ix][ix2] != NULL_EDGE)	// if adj city
					{
						if (marks[i] == false)
						{
							marks[i] = true;
							que.push(cities[i]);
						}
					}
				}
			}
		}

	    void displayGraph()
	    {
	        cout << left;

	        // to display the nodes (first row)
			cout << endl << " " << setw(20) << "";
	        for (int i=0 ; i<nmbCities ; i++){
	            cout << setw(25) << getCity(i)->title;
	        }

	        cout << endl << " " << setw(20) << "" << "------------------------------------------------------------------------------------------------------------------" << endl;

	        // to display the nodes (first column)
	        for (int i=0 ; i<nmbCities ; i++)
	        {
	            cout << " " << setw(20) << getCity(i)->title << "|"
					 << "      ";
	            // to display the edges
				for (int j=0 ; j<nmbCities ; j++)
	            {
	                cout << setw(25) << edges[i][j];
	            }

	            cout << endl;
	        }
	    }
		
		bool checkEdge(int src, int dest)
		{
			if(edges[src][dest] != 0)
				return true;

			else
				return false;
		}
		
		//Destructor
		~WeightedGraph()
		{
			for (int i=0;i<nmbCities;i++)
			{
				delete cities[i];
			}
		}
};

void defaultCity(WeightedGraph&, int);							// To set the cities of the graph to default
void defaultEdge(WeightedGraph&); 								// To set the edges of the graph to default
void initializeGraph (WeightedGraph&, int); 					// To initialize the graph into the default graph
void addRandomEdge (WeightedGraph&, int); 						// To generate a random edge between random cities of the graph
void transposeGraph (WeightedGraph&, WeightedGraph&, int); 		// To transpose the graph
void strongConnectivity(WeightedGraph&, int); 					// Strong Connectivity
void cycle(WeightedGraph&, int); 								// Cycle Detection
void shortestPath(WeightedGraph&, int); 						// Shortest Path
void removeEdge(WeightedGraph& , int); 							// Remove edge from the graph
void printTY(); 												// To print Thank you banner
void printSP();													// To print Shortest Path banner
void printCD();													// To print Cycle Detection banner
void printDG();													// To print Default Graph banner
void printMST();												// To print Minimal Spanning Tree
void printRE();													// To print Remove Edge
void printSC();													// To print Strong Connectivity
void printMB();													// To print Menu Banner

int main()
{
    // Declaring variables
	int vNum = 5;
    int opt;
    WeightedGraph Graph(vNum);
	initializeGraph (Graph, vNum); // To set the graph as the default graph

	// Menu
	do{
	    system ("cls");
	    system ("Color 0E");
	    printMB();
	    Graph.displayGraph();
	    
		cout << "\n\nPlease select the function : " << endl
	    	 << " 	1. Strong Connectivity" << endl
	    	 << "	2. Cycle Detection" << endl
	    	 << "	3. Shortest path" << endl
			 << "	4. Reset graph" << endl
			 << "	5. Minimum Spanning Tree" << endl
			 << "	6. Remove edge" << endl
			 << "	7. Exit" << endl << endl
			 << "Option : " ;
		cin >> opt;

		if(opt<1 || opt>7 || cin.fail()){
	    	cerr << "\n **Invalid option. Please try again..." << endl;
	    	system ("pause");
	    	cin.clear();
			cin.ignore();
			continue;
		}

		system ("cls");
		switch (opt){
			case 1: system("Color 0D");
					printSC();
					strongConnectivity(Graph, vNum);
					break;

			case 2: system("Color 0A");
					printCD();
					Sleep(300);
					cycle(Graph, vNum);
					break;

			case 3: system("Color 0B"); 
					printSP();
					Sleep(300);
					shortestPath(Graph, vNum);
					break;

			case 4: system("Color 0C");
					printDG();
					Sleep(300);
					initializeGraph (Graph, vNum);
					Graph.displayGraph();
					Sleep(300);
					cout << "\n\aThe graph has been successfully reset.\n" << endl;
					system ("pause");
					break;
			
			case 5: system("Color 06");
					printMST();
					Sleep(300);
					system ("pause");
					break;
									
			case 6: system("Color 03");
					printRE();
					Sleep(300);
					removeEdge(Graph, vNum);
					break;

			case 7: system ("Color 09");
					printTY();
					getch();
		}

	} while(opt!=7 || cin.fail());

	return 0;
}

// To add default cities to the graph
void defaultCity (WeightedGraph& g, int N)
{
    city* pCity;
    g.initialization(N);

	// Add cities in memory
	pCity = new city("Manila, Philippines");// 0
	g.add_city(pCity);
	pCity = new city("Sydney, Australia");	// 1
	g.add_city(pCity);
	pCity = new city("Chongqing, China");	// 2
	g.add_city(pCity);
	pCity = new city("Rome, Italy");		// 3
	g.add_city(pCity);
	pCity = new city("Taipei, Taiwan");		// 4
	g.add_city(pCity);

}

// To add default edges to the graph
void defaultEdge (WeightedGraph& g)
{
	
	// Add edges into memory
	g.add_edge(0, 1);
	g.add_edge(0, 4);
	g.add_edge(2, 1);
	g.add_edge(2, 3);
	g.add_edge(4, 3);
}

// To initialize the graph with default cities and edges
void initializeGraph(WeightedGraph& g, int N){
	defaultCity(g, N);
	defaultEdge(g);
}

// To generate a random edge betwenn random cities
void addRandomEdge(WeightedGraph& g, int N)
{
    int start, end;
	bool added = false;

	do
	{
		srand (time(0));
		//weight = rand()%20+1; //generate a random weight between 1 and 20 for the edge
		start = rand()% N; //generate a random value as the index of origin city
		end = rand()% N; //generate a random value as the index of destination city

		if (start!=end && g.weight_is(start, end) == 0)
		{
			g.add_edge(start, end);
			added = true;
			cout << "\t\tAdded edge : "<< g.getCity(start)->title << " -> "
			     << g.getCity(end)->title << "\n\t\tDistance : "
			     << g.weight_is(start, end) << endl;
		} // end if

	} while (added==false);
}

// To transpose the graph (reverse the edges of the graph)
void transposeGraph (WeightedGraph& graph, WeightedGraph& tgraph, int N)
{
	for (int i=0 ; i<N ; i++)
	{
	    for (int j=0 ; j<N ; j++)
	    {
	        if (graph.weight_is(i,j) != 0)
	            tgraph.add_edge(j, i);

	    } // end of inner for loop
	} // end of outer for loop
}

// Strong Connectivity
void strongConnectivity(WeightedGraph& g, int N)
{
	city* start;
	bool havePath = false;
	bool allVisited = false; // To check if all the cities are visited during DFS traversals
	bool edgeAdded = false; // To check if new edge is being added during DFS traversal of the graph

	WeightedGraph TGraph(N); // The transpose of the graph
	defaultCity(TGraph, N); // The transpose of the graph contains the same cities as the graph

	Sleep(300);
	cout << "\n The graph : " << endl;
	Sleep(300);
	g.displayGraph();
	Sleep(300);
	cout << "\n\n First DFS Traversal on the Graph...";

	// Run first DFS traversal on the graph from a chosen city, start (the first city, AU).
	// If there is a city that is not visited, add random edges until all cities are visited.
	start = g.getCity(0);
	cout << "\n\n\t DFS from City 1 (" << start-> title << ") :  " ;
	g.clear_marks();
	allVisited = g.DFS(start);
	cout << endl;
	
	
	if (allVisited == false)
	{
		cout << "\t (The traversal does not visit all the other cities, random edges will be added...)" << endl;
		edgeAdded = true;
	}

	while (allVisited == false)
	{
		cout << "\n";
		addRandomEdge(g, N);
		cout << "\n\t DFS from City 1 (" << start-> title << ") :  " ;
		g.clear_marks();
		allVisited= g.DFS(start);

	}

	if (allVisited == true)
		cout << "\n\t (The traversal visits all the other cities!)" << endl;

	if (edgeAdded == true)
	{
		cout << "\n\n\n The New Graph (with new edges added during the first traversal) : " << endl;
		g.displayGraph();
	}

	else
		cout << "\n\n\n **No new edge is added to the graph during the second traversal." << endl;
	
	transposeGraph(g, TGraph, N); // To transpose the graph by reversing the direction of all the edges in the graph
	Sleep(300);
	cout << "\n\n The Transposed New Graph : " << endl;
	TGraph.displayGraph();

	// Run second DFS traversal on the tranposed graph from the same city, start (the first city, AU).
	// If there is a city that is not visited, add random edges until all cities are visited.
	cout << "\n\n Second DFS Traversal on the Transposed New Graph..." << endl;
	start = TGraph.getCity(0);
	cout << "\n\t DFS from City 1 (" << start-> title << ") : " ;
	edgeAdded = false;
	TGraph.clear_marks();
	allVisited = TGraph.DFS(start);
	cout << endl;

	if (allVisited == false)
	{
		cout << "\t (The traversal does not visit all the other cities, random edges will be added...)" << endl;
		edgeAdded = true;
	}

	while (allVisited == false)
	{
		cout << "\n";
		addRandomEdge(TGraph, N);
		cout << "\n\t DFS from City 1 (" << start-> title << ") :  " ;
		TGraph.clear_marks();
		allVisited= TGraph.DFS(start);
	}

	if (allVisited == true)
		cout << "\n\t (The traversal visits all the other cities!)" << endl;

	if (edgeAdded == true)
	{
		Sleep(300);
		cout << "\n\n The Transposed Graph (with new edges added during the second traversal) : " << endl;
		Sleep(300);
		TGraph.displayGraph();
	}

	else
		cout << "\n\n **No new edge is added to the graph during the second traversal." << endl;

	transposeGraph(TGraph, g, N);
	Sleep(300);
	cout << "\n\n\n\a The final Strongly Connected Graph : " << endl;
	Sleep(300);
	g.displayGraph();
	cout << "\n\n ";
	system ("pause");
}

// Cycle Detection
void cycle(WeightedGraph& graph, int numOfCities)
{
    int sequenceArr[numOfCities];
    int counting = -1;

	Sleep(300);
    cout << "\nThe graph :\n\n";
    Sleep(300);
    graph.displayGraph();
    cout << "\n\n ";

    cout << "The graph HAVE CYCLE? : ";

    if(graph.isGraphCyclic(counting, sequenceArr))
    {
        cout << "YES, The graph has a cycle" << endl << endl;
        graph.printCycles(counting,sequenceArr);
    }
    else
    {
        cout << "NO, The graph has no cycle" << endl;
        cout << endl << endl;
        cout << "\tRandom edges will be added until there is a cyclic graph...\n\n";

        while(!graph.isGraphCyclic(counting, sequenceArr))
        {
            addRandomEdge(graph, numOfCities);
            cout << endl;
        }
        graph.printCycles(counting, sequenceArr);

        Sleep(300);
		cout << "\t\aThe New Graph (The graph has cycle):" << endl << endl;
        Sleep(300);
		graph.displayGraph();
        cout << endl;
    }

    system("Pause");
}

// Shortest Path
void shortestPath(WeightedGraph& graph, int verNum) {
	int source, destination;
	bool pathAvailable;

	cout << endl << endl;
    graph.displayGraph();

	do {
		Sleep(300);
		cout << "\nSelect a starting city and destination city: " << endl
			<< "1 - Manila, Philippines\n2 - Sydney, Australia\n3 - Chongqing, China\n4 - Rome, Italy\n5 - Taipei, Taiwan\n"	<< endl
			<< "Start: ";
		cin >> source;
		cout << "Destination: ";
		cin >> destination;

		if (source > 5 || source < 1 || destination > 5 || destination < 1){
			cout << "Error 1: Source or destination does not exist" << endl;
		}
		
		if (source == destination){
			cout << "Error 2: Souce and destination cannot be same." << endl;
		}

	} while (source > 5 || source < 1 || destination > 5 || destination < 1 || source == destination);

	system("cls");
	string loading = "Checking for available path.........";
	for (int i = 0; i < loading.size(); i++){
		cout << loading[i];
		Sleep(20);
	}
	
	pathAvailable = graph.checkPath(source - 1, destination - 1);
	
	if ((pathAvailable == false))
		cout << "\n\nNo path reaching destination.\nRandom edges will be added until a path exists...\n" << endl;

	while (pathAvailable == false) {		
			addRandomEdge(graph, verNum);
			pathAvailable = graph.checkPath(source - 1, destination - 1);
	}

	Sleep(300);
	cout << "\n\n\aPath to destination found. Latest graph: \n";
	Sleep(300);
	graph.displayGraph();

	graph.findPath(source - 1, destination - 1);
	Sleep(500);

	system("pause");
}

// To print Thank You banner
void printTY(){
	cout << "  ::::::::::: :::    :::     :::     ::::    ::: :::    :::       :::   :::  ::::::::  :::    :::" << endl
		 << "     :+:     :+:    :+:   :+: :+:   :+:+:   :+: :+:   :+:        :+:   :+: :+:    :+: :+:    :+: " << endl
		 << "    +:+     +:+    +:+  +:+   +:+  :+:+:+  +:+ +:+  +:+          +:+ +:+  +:+    +:+ +:+    +:+  " << endl
		 << "   +#+     +#++:++#++ +#++:++#++: +#+ +:+ +#+ +#++:++            +#++:   +#+    +:+ +#+    +:+   " << endl
		 << "  +#+     +#+    +#+ +#+     +#+ +#+  +#+#+# +#+  +#+            +#+    +#+    +#+ +#+    +#+    " << endl
		 << " #+#     #+#    #+# #+#     #+# #+#   #+#+# #+#   #+#           #+#    #+#    #+# #+#    #+#     " << endl
		 << "###     ###    ### ###     ### ###    #### ###    ###          ###     ########   ########       " << endl << endl << endl;
		 
	cout << ":::8888888888888888888888888888888P""""""48888888888888888888888::::88888888" << endl
		 << "::::8888888888888888888888P   ____.------.____   488888888888888:::888" << endl
		 << "::::88888888888888888P __.--""      _._          ""--.__ 4888888888:::8888" << endl
		 << ":::::888888888888P _.-         .-~ | ~-.              -._ 488888:::888" << endl
		 << ":::::888888888P _-             |   |   |                  -_ 488::8888" << endl
		 << "::::::888888P ,'               |  _:_  |                    .-:~--.._8" << endl
		 << "8:::::88888 ,'            .  .- ~~ | ~~ -.                .~  |      |" << endl
		 << "88:::::88P /_.-~:.   .   :   |     |     |       .        |   |      |" << endl
		 << "888::::8P /|    | `.o    !   |     |     |        :       |   |      |" << endl
		 << "8P_..--~:-.|    |  |    d    |     |     | .       o      |   |      |" << endl
		 << "8|      |  ~.   |  |    o    |  __.:.__  | ;       b      |   |      |" << endl
		 << "8|      |   |   |  |   d8  .- ~~   |   ~~ -.o       8     |   |      |" << endl
		 << "8|      |   |  _|.--~:-98  |       |       |8b      8.:~-.|   |      |" << endl
		 << "8|      A   | |      |  ~. |       |   _.-:~--._   .' |   |   |      |" << endl
		 << "8|      M   | |      |   | |       |  |   |     |  |  |   |   |      |" << endl
		 << "8|      C   | |      |   | |       |  |   |     |  |  |   |   O      |" << endl
		 << "8|      |   | |      |   | |       |  |   |     |  |  |   |   j      |" << endl
		 << "8|      9   | |      |   | |       |  |   |     |  |  |   |   o      |" << endl
		 << "8|      9   | |      |   | |       |  |   |     |  |  |   |   |      |" << endl
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl; 
}

// To print Shortest Path banner
void printSP(){
	cout << "..######..##.....##..#######..########..########.########..######..########....########.....###....########.##.....##" << endl
	     << ".##....##.##.....##.##.....##.##.....##....##....##.......##....##....##.......##.....##...##.##......##....##.....##" << endl
	     << ".##.......##.....##.##.....##.##.....##....##....##.......##..........##.......##.....##..##...##.....##....##.....##" << endl
	     << "..######..#########.##.....##.########.....##....######....######.....##.......########..##.....##....##....#########" << endl
	     << ".......##.##.....##.##.....##.##...##......##....##.............##....##.......##........#########....##....##.....##" << endl
	     << ".##....##.##.....##.##.....##.##....##.....##....##.......##....##....##.......##........##.....##....##....##.....##" << endl
	     << "..######..##.....##..#######..##.....##....##....########..######.....##.......##........##.....##....##....##.....##" << endl;
}

// To print Cycle Detection banner
void printCD(){
	cout << ":'######::'##:::'##::'######::'##:::::::'########::::'########::'########:'########:'########::'######::'########:'####::'#######::'##::: ##:" << endl
		 << "'##... ##:. ##:'##::'##... ##: ##::::::: ##.....::::: ##.... ##: ##.....::... ##..:: ##.....::'##... ##:... ##..::. ##::'##.... ##: ###:: ##:" << endl
		 << " ##:::..:::. ####::: ##:::..:: ##::::::: ##:::::::::: ##:::: ##: ##:::::::::: ##:::: ##::::::: ##:::..::::: ##::::: ##:: ##:::: ##: ####: ##:" << endl
		 << " ##:::::::::. ##:::: ##::::::: ##::::::: ######:::::: ##:::: ##: ######:::::: ##:::: ######::: ##:::::::::: ##::::: ##:: ##:::: ##: ## ## ##:" << endl
		 << " ##:::::::::: ##:::: ##::::::: ##::::::: ##...::::::: ##:::: ##: ##...::::::: ##:::: ##...:::: ##:::::::::: ##::::: ##:: ##:::: ##: ##. ####:" << endl
		 << " ##::: ##:::: ##:::: ##::: ##: ##::::::: ##:::::::::: ##:::: ##: ##:::::::::: ##:::: ##::::::: ##::: ##:::: ##::::: ##:: ##:::: ##: ##:. ###:" << endl
		 << ". ######::::: ##::::. ######:: ########: ########:::: ########:: ########:::: ##:::: ########:. ######::::: ##::::'####:. #######:: ##::. ##:" << endl
		 << ":......::::::..::::::......:::........::........:::::........:::........:::::..:::::........:::......::::::..:::::....:::.......:::..::::..::" << endl;
}

// To print Strongly Connectivity banner
void printSC(){
	cout << ":'######::'########:'########:::'#######::'##::: ##::'######:::::::'######:::'#######::'##::: ##:'##::: ##:'########::'######::'########:'####:'##::::'##:'####:'########:'##:::'##:" << endl
		 << "'##... ##:... ##..:: ##.... ##:'##.... ##: ###:: ##:'##... ##:::::'##... ##:'##.... ##: ###:: ##: ###:: ##: ##.....::'##... ##:... ##..::. ##:: ##:::: ##:. ##::... ##..::. ##:'##::" << endl
		 << " ##:::..::::: ##:::: ##:::: ##: ##:::: ##: ####: ##: ##:::..:::::: ##:::..:: ##:::: ##: ####: ##: ####: ##: ##::::::: ##:::..::::: ##::::: ##:: ##:::: ##:: ##::::: ##:::::. ####:::" << endl
		 << ". ######::::: ##:::: ########:: ##:::: ##: ## ## ##: ##::'####:::: ##::::::: ##:::: ##: ## ## ##: ## ## ##: ######::: ##:::::::::: ##::::: ##:: ##:::: ##:: ##::::: ##::::::. ##::::" << endl
		 << ":..... ##:::: ##:::: ##.. ##::: ##:::: ##: ##. ####: ##::: ##::::: ##::::::: ##:::: ##: ##. ####: ##. ####: ##...:::: ##:::::::::: ##::::: ##::. ##:: ##::: ##::::: ##::::::: ##::::" << endl
		 << "'##::: ##:::: ##:::: ##::. ##:: ##:::: ##: ##:. ###: ##::: ##::::: ##::: ##: ##:::: ##: ##:. ###: ##:. ###: ##::::::: ##::: ##:::: ##::::: ##:::. ## ##:::: ##::::: ##::::::: ##::::" << endl
		 << ". ######::::: ##:::: ##:::. ##:. #######:: ##::. ##:. ######::::::. ######::. #######:: ##::. ##: ##::. ##: ########:. ######::::: ##::::'####:::. ###::::'####:::: ##::::::: ##::::" << endl
		 << ":......::::::..:::::..:::::..:::.......:::..::::..:::......::::::::......::::.......:::..::::..::..::::..::........:::......::::::..:::::....:::::...:::::....:::::..::::::::..:::::" << endl;
}

// To print Default Graph banner
void printDG(){
	cout << "'########::'########:'########::::'###::::'##::::'##:'##:::::::'########:::::'######:::'########:::::'###::::'########::'##::::'##:" << endl
		 << " ##.... ##: ##.....:: ##.....::::'## ##::: ##:::: ##: ##:::::::... ##..:::::'##... ##:: ##.... ##:::'## ##::: ##.... ##: ##:::: ##:" << endl
		 << " ##:::: ##: ##::::::: ##::::::::'##:. ##:: ##:::: ##: ##:::::::::: ##::::::: ##:::..::: ##:::: ##::'##:. ##:: ##:::: ##: ##:::: ##:" << endl
		 << " ##:::: ##: ######::: ######:::'##:::. ##: ##:::: ##: ##:::::::::: ##::::::: ##::'####: ########::'##:::. ##: ########:: #########:" << endl
		 << " ##:::: ##: ##...:::: ##...:::: #########: ##:::: ##: ##:::::::::: ##::::::: ##::: ##:: ##.. ##::: #########: ##.....::: ##.... ##:" << endl
		 << " ##:::: ##: ##::::::: ##::::::: ##.... ##: ##:::: ##: ##:::::::::: ##::::::: ##::: ##:: ##::. ##:: ##.... ##: ##:::::::: ##:::: ##:" << endl
		 << " ########:: ########: ##::::::: ##:::: ##:. #######:: ########:::: ##:::::::. ######::: ##:::. ##: ##:::: ##: ##:::::::: ##:::: ##:" << endl
		 << "........:::........::..::::::::..:::::..:::.......:::........:::::..:::::::::......::::..:::::..::..:::::..::..:::::::::..:::::..::" << endl;
}

// To print Minimal Spanning Tree banner
void printMST(){
	cout << "'##::::'##:'####:'##::: ##:'####:'##::::'##:'##::::'##:'##::::'##:::::'######::'########:::::'###::::'##::: ##:'##::: ##:'####:'##::: ##::'######::::::'########:'########::'########:'########:" << endl
		 << " ###::'###:. ##:: ###:: ##:. ##:: ###::'###: ##:::: ##: ###::'###::::'##... ##: ##.... ##:::'## ##::: ###:: ##: ###:: ##:. ##:: ###:: ##:'##... ##:::::... ##..:: ##.... ##: ##.....:: ##.....::" << endl
		 << " ####'####:: ##:: ####: ##:: ##:: ####'####: ##:::: ##: ####'####:::: ##:::..:: ##:::: ##::'##:. ##:: ####: ##: ####: ##:: ##:: ####: ##: ##:::..::::::::: ##:::: ##:::: ##: ##::::::: ##:::::::" << endl
		 << " ## ### ##:: ##:: ## ## ##:: ##:: ## ### ##: ##:::: ##: ## ### ##::::. ######:: ########::'##:::. ##: ## ## ##: ## ## ##:: ##:: ## ## ##: ##::'####::::::: ##:::: ########:: ######::: ######:::" << endl
		 << " ##. #: ##:: ##:: ##. ####:: ##:: ##. #: ##: ##:::: ##: ##. #: ##:::::..... ##: ##.....::: #########: ##. ####: ##. ####:: ##:: ##. ####: ##::: ##:::::::: ##:::: ##.. ##::: ##...:::: ##...::::" << endl
		 << " ##:.:: ##:: ##:: ##:. ###:: ##:: ##:.:: ##: ##:::: ##: ##:.:: ##::::'##::: ##: ##:::::::: ##.... ##: ##:. ###: ##:. ###:: ##:: ##:. ###: ##::: ##:::::::: ##:::: ##::. ##:: ##::::::: ##:::::::" << endl
		 << " ##:::: ##:'####: ##::. ##:'####: ##:::: ##:. #######:: ##:::: ##::::. ######:: ##:::::::: ##:::: ##: ##::. ##: ##::. ##:'####: ##::. ##:. ######::::::::: ##:::: ##:::. ##: ########: ########:" << endl
		 << "..:::::..::....::..::::..::....::..:::::..:::.......:::..:::::..::::::......:::..:::::::::..:::::..::..::::..::..::::..::....::..::::..:::......::::::::::..:::::..:::::..::........::........::" << endl;
}

// To print Remove Edge banner
void printRE(){
	cout << "'########::'########:'##::::'##::'#######::'##::::'##:'########::::'########:'########:::'######:::'########:" << endl
		 << " ##.... ##: ##.....:: ###::'###:'##.... ##: ##:::: ##: ##.....::::: ##.....:: ##.... ##:'##... ##:: ##.....::" << endl
		 << " ##:::: ##: ##::::::: ####'####: ##:::: ##: ##:::: ##: ##:::::::::: ##::::::: ##:::: ##: ##:::..::: ##:::::::" << endl
		 << " ########:: ######::: ## ### ##: ##:::: ##: ##:::: ##: ######:::::: ######::: ##:::: ##: ##::'####: ######:::" << endl
		 << " ##.. ##::: ##...:::: ##. #: ##: ##:::: ##:. ##:: ##:: ##...::::::: ##...:::: ##:::: ##: ##::: ##:: ##...::::" << endl
		 << " ##::. ##:: ##::::::: ##:.:: ##: ##:::: ##::. ## ##::: ##:::::::::: ##::::::: ##:::: ##: ##::: ##:: ##:::::::" << endl
		 << " ##:::. ##: ########: ##:::: ##:. #######::::. ###:::: ########:::: ########: ########::. ######::: ########:" << endl
		 << "..:::::..::........::..:::::..:::.......::::::...:::::........:::::........::........::::......::::........::" << endl; 
}

// To print Menu Banner
void printMB(){
	cout << "      ::::::::  :::::::::      :::     :::::::::  :::    :::              :::     :::        ::::::::   ::::::::  :::::::::  ::::::::::: ::::::::::: :::    :::   :::   :::    ::::::::" << endl
	    	 << "    :+:    :+: :+:    :+:   :+: :+:   :+:    :+: :+:    :+:            :+: :+:   :+:       :+:    :+: :+:    :+: :+:    :+:     :+:         :+:     :+:    :+:  :+:+: :+:+:  :+:    :+:" << endl
	    	 << "   +:+        +:+    +:+  +:+   +:+  +:+    +:+ +:+    +:+           +:+   +:+  +:+       +:+        +:+    +:+ +:+    +:+     +:+         +:+     +:+    +:+ +:+ +:+:+ +:+ +:+        " << endl
	    	 << "  :#:        +#++:++#:  +#++:++#++: +#++:++#+  +#++:++#++          +#++:++#++: +#+       :#:        +#+    +:+ +#++:++#:      +#+         +#+     +#++:++#++ +#+  +:+  +#+ +#++:++#++  " << endl
	    	 << " +#+   +#+# +#+    +#+ +#+     +#+ +#+        +#+    +#+          +#+     +#+ +#+       +#+   +#+# +#+    +#+ +#+    +#+     +#+         +#+     +#+    +#+ +#+       +#+        +#+   " << endl
	    	 << "#+#    #+# #+#    #+# #+#     #+# #+#        #+#    #+#          #+#     #+# #+#       #+#    #+# #+#    #+# #+#    #+#     #+#         #+#     #+#    #+# #+#       #+# #+#    #+#    " << endl
	    	 << "########  ###    ### ###     ### ###        ###    ###          ###     ### ########## ########   ########  ###    ### ###########     ###     ###    ### ###       ###  ########      " << endl << endl;
}

// To remove edge from the graph
void removeEdge(WeightedGraph& sp, int verNum)
{
	int source, destination;
	bool edgeAvailable;

	Sleep(300);
    sp.displayGraph();

	do {
		Sleep(300);
		cout << "\n\nSelect a starting city and destination city: " << endl
			<< "1 - Manila, Philippines\n2 - Sydney, Australia\n3 - Chongqing, China\n4 - Rome, Italy\n5 - Taipei, Taiwan\n"	<< endl
			<< "Start: ";
		cin >> source;
		//cin.ignore();
		cout << "Destination: ";
		cin >> destination;
		//cin.ignore();

		if (source>5 || source<1 || destination>5 || destination<1) {
			cout << "\nInvalid input. Please try again.\n" << endl;
			system ("pause");
			system ("cls");
		}

	} while (source>5 || source<1 || destination>5 || destination<1);

	edgeAvailable = false;

	cout << "\nChecking for available edge...";
	edgeAvailable = sp.checkEdge(source-1, destination-1);

	if (edgeAvailable == false) {
		cout<< "\nNo edge between "<< sp.getCity(source-1)->title<< " and "<< sp.getCity(destination-1)->title<<".";
	}

	else {
		cout << "\n\nEdge between " << sp.getCity(source-1)->title << " and " << sp.getCity(destination-1)->title << " found. \n";
		cout << "Removing..." << endl;
		sp.remove_edge(source-1, destination-1);
	}

	Sleep(300);
	cout << "\nLatest graph: \n";
	Sleep(300);
	sp.displayGraph();
	cout << "\a\nThe edge has successfully removed";
	cout << "\n\n";
	system("pause");
}
