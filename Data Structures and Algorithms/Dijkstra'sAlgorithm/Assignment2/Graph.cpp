#include "Graph.h"

// constructor based on the airport names.
Graph::Graph(std::vector <std::string> inAirportList)
{
	airportNameList = inAirportList;
	maxVertices = airportNameList.size();

	// intialize graph
	graph = new int* [maxVertices]; // number of rows
	for (int i = 0; i < maxVertices; i++)
	{
		graph[i] = new int [maxVertices]; // number of columns

		// Initial weight as 0
		for (int j = 0; j < maxVertices; j++)
		{
			graph[i][j] = 0;
		}
	}
}

Graph::~Graph()
{

}

// insert edges between two airports with the weight as distance
void Graph::insertEdge(std::string airport1, std::string airport2, int distance)
{
	// Determine the indexes of the airports
	int airportOneIndex = getAirportIndex(airport1);
	int airportTwoIndex = getAirportIndex(airport2);
	
	// Applying weight for both airports
	graph[airportOneIndex][airportTwoIndex] = distance;
	graph[airportTwoIndex][airportOneIndex] = distance;
}

// Decide the shortest path.
// RECOMMENDATION: call this function after all vertices and edges are inserted.
void Graph::dijkstra(std::string source, std::string destination)
{
	std::vector<int> distance; // output vector.

	std::vector<bool> sptSet; //path shortest distance from sources to i is finalized.

	// Initialize all distances as "Infinity" and sptSet as false;
	for (int i = 0; i < getNumVertices(); i++)
	{
		distance.push_back(INT_MAX), sptSet.push_back(false);
	}

	// Set distance of source vertex to itself equal to 0.
	distance[getAirportIndex(source)] = 0;

	// Find the shortest path for all vertices.
	for (int count = 0; count < getNumVertices() - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices
		// that is not processed.
		int minIndex = minDistance(distance, sptSet);

		// Mark the picked vertex as processed
		sptSet[minIndex] = true;

		for (int vertexIndex = 0; vertexIndex < getNumVertices(); vertexIndex++)
		{
			// Update distance[vertexIndex] if vertex is not in sptSet, there is
			// an edge from vertex to minIndex, and toal weight of path from
			// source to vertex through minIndex is maller than current value
			// of distance[vertexIndex]
			if (!sptSet[vertexIndex] && graph[minIndex][vertexIndex] && distance[minIndex] != INT_MAX &&
				distance[minIndex] + graph[minIndex][vertexIndex] < distance[vertexIndex])
			{
				distance[vertexIndex] = distance[minIndex] + graph[minIndex][vertexIndex];
			}
		}
	}

	// Search for destination distance
	printResult(getAirportIndex(source), getAirportIndex(destination), distance);
}

// get the number of vertices
const int Graph::getNumVertices()
{
	return maxVertices;
}

// get the index of the input airport name inside the list of airport names
const int Graph::getAirportIndex(std::string airport)
{
	int index;

	// find the index of input airport in the airport name list
	std::vector<std::string>::iterator it = std::find(airportNameList.begin(), 
													  airportNameList.end(), 
													  airport);
	if (it != airportNameList.end())
		index = std::distance(airportNameList.begin(), it);
	else
	{
		std::cout << "Graph::getAirportIndex : airport not found" << std::endl;
	}
	return index;
}

// Get the min distance in distance list and see if it is decided in sptSet.
int Graph::minDistance(std::vector<int> distance, std::vector<bool> sptSet)
{
	int min = INT_MAX, minIndex;

	// go through the list and find min index
	for (int i = 0; i < getNumVertices(); i++)
	{
		if (sptSet[i] == false && distance[i] <= min)
			min = distance[i], minIndex = i;
	}

	return minIndex;
}

// print the final result after find the shortest path.
void Graph::printResult(int sourceIndex, int destinationIndex, std::vector<int> distance)
{
	std::cout << "From " << airportNameList[sourceIndex]
		      << " To " << airportNameList[destinationIndex]
		      << " : " << distance[destinationIndex] << std::endl;
}