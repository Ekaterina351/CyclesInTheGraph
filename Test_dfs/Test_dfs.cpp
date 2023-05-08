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

			std::set<Vertex*> input_visited;
			std::map<std::string, std::vector<Vertex*>> input_cycles = {
				{"12", {}}, {"13", {}}
			};

			std::string exp_name = "123";
			bool exp_search_res = true;

			std::vector<Vertex*> res_recStack;
			bool search_res = dfs(v1, res_recStack, input_visited, input_cycles);
			std::string res_name = getCorrectCycleName(res_recStack);

			Assert::AreEqual(exp_search_res, search_res);
			Assert::AreEqual(exp_name, res_name);
		}
	};
}
