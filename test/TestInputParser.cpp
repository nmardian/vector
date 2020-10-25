#include "gtest/gtest.h"

#include "util/InputParser.h"

TEST(TestInputParser, TestParseCommand)
{
    std::string vectorString = "vector";
    std::string identifyString = "identify";
    std::string aquireString = "aquire";
    std::string launchString = "launch";

    vector::util::Command result;

    result = vector::util::InputParser::Parse(vectorString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::VECTOR, result.command);

    result = vector::util::InputParser::Parse(identifyString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::IDENTIFY, result.command);

    result = vector::util::InputParser::Parse(aquireString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::AQUIRE, result.command);

    result = vector::util::InputParser::Parse(launchString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::LAUNCH, result.command);
}

TEST(TestInputParser, TestTrim)
{
    std::string startWS = " vector";
    std::string endWS = "vector ";
    std::string startEndWS = " vector ";

    vector::util::Command result;

    result = vector::util::InputParser::Parse(startWS);
    EXPECT_EQ(vector::util::COMMAND_TYPE::VECTOR, result.command);

    result = vector::util::InputParser::Parse(endWS);
    EXPECT_EQ(vector::util::COMMAND_TYPE::VECTOR, result.command);

    result = vector::util::InputParser::Parse(startEndWS);
    EXPECT_EQ(vector::util::COMMAND_TYPE::VECTOR, result.command);
}

TEST(TestInputParser, TestParseInvalids)
{
    std::string emptyString = "";
    std::string garbageString = "garbage";
    std::string capsString = "VECTOR";

    vector::util::Command result;

    result = vector::util::InputParser::Parse(emptyString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::UNK, result.command);

    result = vector::util::InputParser::Parse(garbageString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::UNK, result.command);

    result = vector::util::InputParser::Parse(capsString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::UNK, result.command);
}