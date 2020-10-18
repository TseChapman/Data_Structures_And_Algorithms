#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"

// read the file from parameters and calculate the shortest path based on user inputed source and destination.
void readFiles(const int NUM_FILES, std::vector<std::string> fileName, std::vector<std::string> airportNames);

// read the file from parameters and calculate the shortest path based on user inputed source and destination.
void readFiles(const int NUM_FILES, std::vector<std::string> fileName, std::vector<std::string> airportNames)
{
	// define airport1, airport2, and distance indices.
	const int airportOneIndex = 0;
	const int aiportTwoIndex = 1;
	const int distanceIndex = 2;

	for (int fileIndex = 0; fileIndex < NUM_FILES; fileIndex++)
	{
		// Open files one by one.
		std::ifstream file(fileName[fileIndex] + ".csv");

		std::string line;
		if (file.is_open())
		{
			// Initialize Graph by the names of the airports.
			Graph airports(airportNames);
			int airportNumbers = airportNames.size();

			while (std::getline(file,line))
			{
				// Get source, destination, and distance from a line.
				std::stringstream stream(line);
				std::string word;
				std::vector<std::string> departureInfo;
				while (std::getline(stream, word, ','))
				{
					departureInfo.push_back(word);
				}
				int distance = std::stoi(departureInfo[distanceIndex]);
				
				// Input the info into the graph.
				airports.insertEdge(departureInfo[airportOneIndex], departureInfo[aiportTwoIndex], distance);

			}
			file.close();

			// Get source and destination name from user.
			std::cout << "Enter valid source and valid destination" << std::endl;
			// print out available aiports
			std::cout << "Airport names: " << std::endl;
			for (int i = 0; i < airportNumbers; i++)
			{
				std::cout << airportNames[i] << " ";
			}
			std::cout << "" << std::endl;

			// Get source and destination from user.
			std::string source;
			std::string destination;
			std::cout << "Enter valid source" << std::endl;
			std::cin >> source;
			std::cout << "Enter valid destination" << std::endl;
			std::cin >> destination;

			// Determine the shortest path and print out result. Including printing result.
			airports.dijkstra(source, destination);
		}
		else
		{
			std::cout << "Unable to open file: " << fileName[fileIndex] << ".csv" << std::endl;
		}
	}
}

int main()
{
	const int NUM_FILES = 1; // Number of files
	std::vector<std::string> fileName = { "AirportDistances" }; // file name

	// name of all airports
	std::vector<std::string> airportNames = {"OLM", "BOI", "HLN", "EKO", "SAF", 
											 "LAS", "SLC", "BIS", "DEN", "FOE", 
											 "LIT", "BTR", "AUS", "TLH", "CVG",
											 "RDU", "LCK", "PIT", "LAN", "STL",
											 "DSM", "OKC", "XMD", "LNK", "AUM",
											 "PIR"};
	// begin the reading process.
	readFiles(NUM_FILES, fileName, airportNames);

	return 0;
}