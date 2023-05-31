#include "pch.h"
#include "CppUnitTest.h"
#include "../CyclesInTheGraph/CyclesInTheGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testdfs
{
	TEST_CLASS(Testdfs)
	{
	public:
		
		TEST_METHOD(sampleTest)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v2, v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {
				{"12", {}}, {"13", {}}
			};

			std::string exp_name = "123";
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(singleVertexGraph)
		{
			Vertex* v1 = new Vertex("1");

			std::map<std::string, std::vector<Vertex*>> input_cycles = {};

			std::string exp_name = "";
			bool exp_search_res = false;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(vertexWithNoOutgoingEdges)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {};

			std::string exp_name = "";
			bool exp_search_res = false;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(vertexWithSingleEdge)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v2 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {
				{"12", {}}
			};

			std::string exp_name = "123";
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(vertexWithSingleCycle)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {};

			std::string exp_name = "13";
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(vertexWithNoMissingCycles)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v2, v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {
				{"12", {}}, {"13", {}}, {"123", {}}
			};

			std::string exp_name = "";
			bool exp_search_res = false;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
		TEST_METHOD(noCyclesFound)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v2, v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {};

			std::set<std::string> exp_names = { "12", "13", "123" };
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);

			std::string msg = "Expected cycle name doesn't found: " + res_name;
			std::wstring wideMsg(msg.begin(), msg.end());

			Assert::IsTrue(exp_names.contains(res_name), wideMsg.c_str());
		}
		TEST_METHOD(singleVertexInCycle)
		{
			Vertex* v1 = new Vertex("1");
			Vertex* v2 = new Vertex("2");
			Vertex* v3 = new Vertex("3");
			v1->adjacentVertices = { v1, v2, v3 };
			v2->adjacentVertices = { v1, v3 };
			v3->adjacentVertices = { v1 };

			std::map<std::string, std::vector<Vertex*>> input_cycles = {
				{"12", {}}, {"123", {}}, {"13", {}}
			};

			std::string exp_name = "1";
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
	};
}
