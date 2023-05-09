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
        TEST_METHOD(emptyCycle)
        {
            std::vector<Vertex*> input_cycle = {};
            std::string exp_name = "";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(singleVertexInCycle)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("x3")
            };
            std::string exp_name = "3x";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithDigitsOnly)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("3"),
                new Vertex("2"),
                new Vertex("3")
            };
            std::string exp_name = "233";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithLettersOnly)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("z"),
                new Vertex("y"),
                new Vertex("x"),
                new Vertex("z")
            };
            std::string exp_name = "xyzz";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithSpecialCharactersOnly)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("%"),
                new Vertex("/"),
                new Vertex("#"),
                new Vertex("%")
            };
            std::string exp_name = "#%%/";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithWhitespaceCharactersOnly)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("\t"),
                new Vertex(" "),
                new Vertex("\n"),
                new Vertex("\t")
            };
            std::string exp_name = "\t\t\n ";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithDigitsAndSpecialCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("1%"),
                new Vertex("2#"),
                new Vertex("3*"),
                new Vertex("1%")
            };
            std::string exp_name = "#%%*1123";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithDigitsAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("3\n"),
                new Vertex("\t2"),
                new Vertex("3\n"),
                new Vertex("3\n")
            };
            std::string exp_name = "\t\n\n\n2333";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithLettersAndSpecialCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("x%"),
                new Vertex("y#"),
                new Vertex("z*"),
                new Vertex("x%")
            };
            std::string exp_name = "#%%*xxyz";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithLettersAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("z\t"),
                new Vertex("y "),
                new Vertex("\nx"),
                new Vertex("z\t")
            };
            std::string exp_name = "\t\t\n xyzz";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }

        TEST_METHOD(vertexNamesWithSpecialCharactersAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("$\t"),
                new Vertex("@ "),
                new Vertex("\n&"),
                new Vertex("$\t")
            };
            std::string exp_name = "\t\t\n $$&@";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithDigitsLettersAndSpecialCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("3x%"),
                new Vertex("z0-"),
                new Vertex("(9y"),
                new Vertex("3x%")
            };
            std::string exp_name = "%%(-0339xxyz";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithDigitsLettersAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("8o\t"),
                new Vertex(" y1"),
                new Vertex("8\nu"),
                new Vertex("8o\t")
            };
            std::string exp_name = "\t\t\n 1888oouy";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithLettersSpecialCharactersAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("x^\t"),
                new Vertex("\n;z"),
                new Vertex("№y "),
                new Vertex("x^\t")
            };
            std::string exp_name = "№\t\t\n ;^^xxyz";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(vertexNamesWithDigitsLettersSpecialCharactersAndWhitespaceCharacters)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("1x% "),
                new Vertex("y\t3+"),
                new Vertex("~2z\n"),
                new Vertex("1x% ")
            };
            std::string exp_name = "\t\n  %%+1123xxyz~";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(orderedVertices)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("1"),
                new Vertex("2"),
                new Vertex("3")
            };
            std::string exp_name = "123";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(partiallyOrderedVertices)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("2"),
                new Vertex("3"),
                new Vertex("1")
            };
            std::string exp_name = "123";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
        TEST_METHOD(multipleDuplicateVertices)
        {
            std::vector<Vertex*> input_cycle = {
                new Vertex("x1"),
                new Vertex("x2"),
                new Vertex("x2"),
                new Vertex("x3"),
                new Vertex("x3"),
                new Vertex("x1")
            };
            std::string exp_name = "112233xxxxxx";

            std::string res_name = getCorrectCycleName(input_cycle);
            Assert::AreEqual(exp_name, res_name);
        }
	};
}
