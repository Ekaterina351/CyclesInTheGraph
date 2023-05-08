#include "pch.h"
#include "CppUnitTest.h"
#include "../CyclesInTheGraph/CyclesInTheGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


void compareFoundCycles(std::set<std::string>& exp_cycles, std::map<std::string, std::vector<Vertex*>>& res_cycles)
{
	for (const auto& [cycleName, cycleVector] : res_cycles) {
		if (!exp_cycles.contains(cycleName)) {
			std::string msg = "Expected cycle name doesn't found: " + cycleName;
			std::wstring wideMsg(msg.begin(), msg.end());
			Assert::Fail(wideMsg.c_str());
		}
		exp_cycles.erase(cycleName);
	}
	Assert::IsFalse(exp_cycles.size(), L"Not all cycles are found.");
}


namespace TestfindCycles
{
	TEST_CLASS(TestfindCycles)
	{
	public:
		
		TEST_METHOD(sampleTest)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			v2->adjacentVertices.push_back(v1);
			v2->adjacentVertices.push_back(v3);
			v3->adjacentVertices.push_back(v1);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "123", "12" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(emptyGraph)
		{
			std::vector<Vertex*> input_graph = { };

			bool exp_search_res = false;
			std::set<std::string> exp_cycles = { };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(singleVertexGraph)
		{
			Vertex* v1 = new Vertex("1");
			std::vector<Vertex*> input_graph = { v1 };

			bool exp_search_res = false;
			std::set<std::string> exp_cycles = { };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(noEdgesGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = false;
			std::set<std::string> exp_cycles = { };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(singleEdgeGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = false;
			std::set<std::string> exp_cycles = { };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(singleCycleGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			v2->adjacentVertices.push_back(v3);
			v3->adjacentVertices.push_back(v1);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "123" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(partialVerticesInSingleCycleGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			v2->adjacentVertices.push_back(v1);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "12" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(partialVerticesInMultipleCyclesGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			v1->adjacentVertices.push_back(v3);
			v2->adjacentVertices.push_back(v1);
			v3->adjacentVertices.push_back(v1);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "12", "13" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(allVerticesInSingleCycleAndPartialVerticesInMultipleCyclesGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v2);
			v1->adjacentVertices.push_back(v3);
			v2->adjacentVertices.push_back(v1);
			v2->adjacentVertices.push_back(v3);
			v3->adjacentVertices.push_back(v1);
			v3->adjacentVertices.push_back(v2);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "12", "13", "23", "123" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
		TEST_METHOD(selfLoopGraph)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices.push_back(v1);
			v1->adjacentVertices.push_back(v2);
			v2->adjacentVertices.push_back(v1);
			v2->adjacentVertices.push_back(v3);
			v3->adjacentVertices.push_back(v1);
			std::vector<Vertex*> input_graph = { v1, v2, v3 };

			bool exp_search_res = true;
			std::set<std::string> exp_cycles = { "12", "1", "123" };

			std::map<std::string, std::vector<Vertex*>> res_cycles;
			bool search_res = findCycles(input_graph, res_cycles);

			Assert::AreEqual(exp_search_res, search_res);
			compareFoundCycles(exp_cycles, res_cycles);
		}
	};
}
