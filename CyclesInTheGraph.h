#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>


using namespace std;

struct Vertex {
	std::string name;
	std::vector<Vertex*> adjacentVertices;

	explicit Vertex(const std::string& vertexName) : name(vertexName) {}
};


std::string getCorrectCycleName(const std::vector<Vertex*>& cycle);


bool dfs(Vertex* viewedVertex, std::vector<Vertex*>& recStack, std::set<Vertex*> visited, 
	const std::map<std::string, std::vector<Vertex*>>& cycles);


bool findCycles(const std::vector<Vertex*>& graph, std::map<std::string, std::vector<Vertex*>>& cycles);


Vertex* findVertexInGraph(const std::string& vertexName, const std::vector<Vertex*>& graph);


void readCSVFile(const std::string& input_file_path, std::vector<Vertex*>& graph, const char delimiter = ';');
