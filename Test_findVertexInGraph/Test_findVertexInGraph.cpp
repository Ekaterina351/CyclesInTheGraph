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
        TEST_METHOD(emptyGraph)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = { };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }
        TEST_METHOD(singleTargetVertexGraph)
        {
            std::string target_name = "x1";

            Vertex* exp_vertex = new Vertex("x1");
            std::vector<Vertex*> graph = {
                exp_vertex,
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsTrue(exp_vertex == res_vertex);
        }
        //
        TEST_METHOD(oneNonMatchingVertex)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(targetVertexFirstInGraph)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x1"),
                new Vertex("x2"),
                new Vertex("x3")
            };
            Vertex* exp_vertex = graph[0];

            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsTrue(exp_vertex == res_vertex);
        }

        TEST_METHOD(targetVertexMiddleInGraph)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x1"),
                new Vertex("x3")
            };
            Vertex* exp_vertex = graph[1];
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsTrue(exp_vertex == res_vertex);
        }

        TEST_METHOD(similarVertexWithDifferentCase)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("X1")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithExtraCharactersBeforeName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("xx1")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithExtraCharactersAfterName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("x11")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithExtraCharactersInName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("xz1")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithWhitespaceBeforeName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("  x1")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithWhitespaceAfterName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("x1\t")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(similarVertexWithWhitespaceInName)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("x 1")
            };
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsNull(res_vertex);
        }

        TEST_METHOD(duplicateTargetVertexOnceInArray)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x1"),
                new Vertex("x3"),
                new Vertex("x1")
            };
            Vertex* exp_vertex = graph[1];
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsTrue(exp_vertex == res_vertex);
        }

        TEST_METHOD(duplicateTargetVertexMultipleTimesInArray)
        {
            std::string target_name = "x1";

            std::vector<Vertex*> graph = {
                new Vertex("x2"),
                new Vertex("x1"),
                new Vertex("x3"),
                new Vertex("x1"),
                new Vertex("x1"),
                new Vertex("x1")
            };
            Vertex* exp_vertex = graph[1];
            Vertex* res_vertex = findVertexInGraph(target_name, graph);
            Assert::IsTrue(exp_vertex == res_vertex);
        }
	};
}
