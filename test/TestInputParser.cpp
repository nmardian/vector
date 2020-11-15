#include "gtest/gtest.h"

#include "util/InputParser.h"

TEST(TestInputParser, TestParseCommand)
{
    std::string vectorString = "vector brot 123";
    std::string identifyString = "identify brot marm";
    std::string aquireString = "aquire brot marm";
    std::string launchString = "launch brot marm";

    vector::util::Command result;

    result = vector::util::InputParser::Parse(vectorString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::VECTOR, result.command);
    EXPECT_EQ("brot", result.subject);
    EXPECT_EQ("123", result.object);

    result = vector::util::InputParser::Parse(identifyString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::IDENTIFY, result.command);
    EXPECT_EQ("brot", result.subject);
    EXPECT_EQ("marm", result.object);

    result = vector::util::InputParser::Parse(aquireString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::AQUIRE, result.command);
    EXPECT_EQ("brot", result.subject);
    EXPECT_EQ("marm", result.object);

    result = vector::util::InputParser::Parse(launchString);
    EXPECT_EQ(vector::util::COMMAND_TYPE::LAUNCH, result.command);
    EXPECT_EQ("brot", result.subject);
    EXPECT_EQ("marm", result.object);
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