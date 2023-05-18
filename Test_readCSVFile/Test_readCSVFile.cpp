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
		TEST_METHOD(noRowsAndColumnsInCSVFile)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\noRowsAndColumnsInCSVFile.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(oneRowInCSVFile)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\oneRowInCSVFile.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(oneColumnInCSVFile)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\oneColumnInCSVFile.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(moreColumnsThanRowsInTable)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\moreColumnsThanRowsInTable.csv";

			Vertex* v1 = new Vertex("X1");
			Vertex* v2 = new Vertex("X2");
			Vertex* v3 = new Vertex("X3");
			v1->adjacentVertices = { v2, v3 };
			v2->adjacentVertices = { v1, v3 };

			std::vector<Vertex*> exp_graph = {
				v1, v2, v3
			};
			std::vector<Vertex*>res_graph;
			readCSVFile(filePath.string(), res_graph);

			compareGraphs(exp_graph, res_graph);
		}
		TEST_METHOD(fewerColumnsThanRowsInTable)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\fewerColumnsThanRowsInTable.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(unnamedVertexInHorizontalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\unnamedVertexInHorizontalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(unnamedVertexInVerticalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\unnamedVertexInVerticalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(vertexWithWhitespaceNameInHorizontalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\vertexWithWhitespaceNameInHorizontalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(vertexWithWhitespaceNameInVerticalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\vertexWithWhitespaceNameInVerticalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(whitespaceBeforeVertexName)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\whitespaceBeforeVertexName.csv";

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
		TEST_METHOD(whitespaceAfterVertexName)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\whitespaceAfterVertexName.csv";

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
		TEST_METHOD(whitespaceInVertexName)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\whitespaceInVertexName.csv";

			Vertex* v1 = new Vertex("X\\t1");
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
		TEST_METHOD(whitespaceBeforeAndAfterVertexName)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\whitespaceBeforeAndAfterVertexName.csv";

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
		TEST_METHOD(whitespaceBeforeAfterAndInVertexName)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\whitespaceBeforeAfterAndInVertexName.csv";

			Vertex* v1 = new Vertex("X    1");
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
		TEST_METHOD(duplicateVerticesInHorizontalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\duplicateVerticesInHorizontalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(duplicateVerticesInVerticalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\duplicateVerticesInVerticalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(mismatchedOrderOfVerticesBetweenHeaders)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\mismatchedOrderOfVerticesBetweenHeaders.csv";

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
		TEST_METHOD(emptyCellsInTableBody)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\emptyCellsInTableBody.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(cellsWithWhitespaceInTableBody)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\cellsWithWhitespaceInTableBody.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(cellsWithNonBinaryTextInTableBody)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\cellsWithNonBinaryTextInTableBody.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(cyclesInGraphDefinedInTableBody)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\cyclesInGraphDefinedInTableBody.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(tableBodyWidthGreaterThanHorizontalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\tableBodyWidthGreaterThanHorizontalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(tableBodyWidthLessThanHorizontalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\tableBodyWidthLessThanHorizontalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(tableBodyHeightGreaterThanVerticalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\tableBodyHeightGreaterThanVerticalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
		TEST_METHOD(tableBodyHeightLessThanVerticalHeader)
		{
			std::filesystem::path filePath = currentPath / "Test_readCSVFile\\input_files\\tableBodyHeightLessThanVerticalHeader.csv";

			bool exceptionThrown = false;
			try {
				std::vector<Vertex*>res_graph;
				readCSVFile(filePath.string(), res_graph);
			}
			catch (const InvalidGraphAssignment&) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Expected InvalidGraphAssignment to be thrown.");
		}
	};
}
