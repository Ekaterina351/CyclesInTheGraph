#include "pch.h"
#include "CppUnitTest.h"
#include "../CyclesInTheGraph/CyclesInTheGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestgetCorrectCycleName
{
	TEST_CLASS(TestgetCorrectCycleName)
	{
	public:
		
		TEST_METHOD(sampleTest)
		{
			std::vector<Vertex*> input_cycle = {
				new Vertex("x3"),
				new Vertex("x2"),
				new Vertex("x3")
			};
			std::string exp_name = "233xxx";

			std::string res_name = getCorrectCycleName(input_cycle);
			Assert::AreEqual(exp_name, res_name);
		}
	};
}
