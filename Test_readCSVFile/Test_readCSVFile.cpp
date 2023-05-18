#include "pch.h"
#include "CppUnitTest.h"
#include <filesystem>
#include "../CyclesInTheGraph/CyclesInTheGraph.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


void compareGraphs(std::vector<Vertex*>exp_graph, std::vector<Vertex*>res_graph) {
	for (Vertex* v : res_graph) {
		bool found = false;
		for (Vertex* exp_v : exp_graph) {
			if (exp_v->name == v->name) {
				found = true;
				for (Vertex* adj_v : v->adjacentVertices) {
					bool found_adj = false;
					for (Vertex* exp_adj_v : exp_v->adjacentVertices) {
						if (exp_adj_v->name == adj_v->name) {
							found_adj = true;
							break;
						}
					}
					Assert::IsTrue(found_adj, L"Some adjacent vertex doesnt found.");
				}
				Assert::IsFalse(exp_v->adjacentVertices.size() != v->adjacentVertices.size(), L"Some adjacent vertex missed.");
				break;
			}
		}
		Assert::IsTrue(found, L"Some vertex doesnt found.");
	}
	Assert::IsFalse(exp_graph.size() != res_graph.size(), L"Some vertex missed in result graph");
}

namespace TestreadCSVFile
{
	TEST_CLASS(TestreadCSVFile)
	{
	private:
		std::filesystem::path currentPath = std::filesystem::current_path().parent_path().parent_path();
	public:
		
		TEST_METHOD(sampleTest)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\sampleTest.csv";

			Vertex* v1 = new Vertex("X1");
			Vertex* v2 = new Vertex("X2");
			Vertex* v3 = new Vertex("X3");
			v1->adjacentVertices = { v2, v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1, v2 };

			std::vector<Vertex*> exp_graph = {
				v1, v2, v3
			};
			std::vector<Vertex*>res_graph;
			readCSVFile(filePath.string(), res_graph);

			compareGraphs(exp_graph, res_graph);
		}
	};
}
