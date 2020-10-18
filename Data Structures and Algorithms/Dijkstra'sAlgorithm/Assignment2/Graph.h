#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

class Graph
{
public:
	// constructor based on the airport names.
	Graph(std::vector <std::string> inAirportList);

	// deconstructor
	~Graph();

	// insert edges between two airports with the weight as distance
	void insertEdge(std::string airport1, std::string airport2, int distance);

	// Decide the shortest path.
	// RECOMMENDATION: call this function after all vertices and edges are inserted.
	void dijkstra(std::string source, std::string destination);
private:

	// number of vertices
	int maxVertices;

	// List of airport names
	std::vector <std::string> airportNameList;

	// the adjacency matric implementation graph
	int **graph;

	// get the number of vertices
	const int getNumVertices();

	// get the index of the input airport name inside the list of airport names
	const int getAirportIndex(std::string airport);

	// Get the min distance in distance list and see if it is decided in sptSet.
	int minDistance(std::vector<int> distance, std::vector<bool> sptSet);

	// print the final result after find the shortest path.
	void printResult(int sourceIndex, int destinationIndex, std::vector<int> distance);
};
#pragma once