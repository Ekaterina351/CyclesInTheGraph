#include "pch.h"
#include "CppUnitTest.h"
#include "../CyclesInTheGraph/CyclesInTheGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestfindVertexInGraph
{
	TEST_CLASS(TestfindVertexInGraph)
	{
	public:
		
		TEST_METHOD(sampleTest)
		{
			std::string target_name = "x1";

			std::vector<Vertex*> graph = {
				new Vertex("x2"),
				new Vertex("x3"),
				new Vertex("x1")
			};
			Vertex* exp_vertex = graph[2];

			Vertex* res_vertex = findVertexInGraph(target_name, graph);
			Assert::IsTrue(exp_vertex == res_vertex);
		}
	};
}
