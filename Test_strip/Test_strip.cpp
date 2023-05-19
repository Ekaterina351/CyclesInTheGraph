#include "pch.h"
#include "CppUnitTest.h"
#include "../CyclesInTheGraph/CyclesInTheGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Teststrip
{
	TEST_CLASS(Teststrip)
	{
	public:
		
        TEST_METHOD(sampleTest)
        {
            std::string input_str = "  \t  \t\n some text    ";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(emptyString)
        {
            std::string input_str = "";
            std::string exp_str = "";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(noCharactersAroundString)
        {
            std::string input_str = "some text";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(oneCharacterFromListOnTheRight)
        {
            std::string input_str = "some text\t";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(multipleCharactersFromListOnTheRight)
        {
            std::string input_str = "some text\t\t  \t";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(oneCharacterFromListOnTheLeft)
        {
            std::string input_str = "\tsome text";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(multipleCharactersFromListOnTheLeft)
        {
            std::string input_str = "  \tsome text";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(multipleCharactersFromListOnBothSides)
        {
            std::string input_str = "  \t\t \t some text  \t";
            std::string exp_str = "some text";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
        TEST_METHOD(allCharactersInStringAreListCharacters)
        {
            std::string input_str = " \t   \t        \n \r \t  \n";
            std::string exp_str = "";
            strip(input_str);
            Assert::AreEqual(exp_str, input_str);
        }
	};
}
