#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "util/CallsignGenerator.h"

#include <unordered_set>

constexpr int MIN_CALLSIGNS = 0;
constexpr int MAX_CALLSIGNS = 26;

TEST(TestCallsignGenerator, TestGenerateZero)
{
    // request the minimum number of callsigns
    auto resultListFriend = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MIN_CALLSIGNS);

    // verify the minimum number of callsigns were generated
    EXPECT_EQ(MIN_CALLSIGNS, resultListFriend.size());

    // request the minimum number of callsigns
    auto resultListEnemy = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MIN_CALLSIGNS);

    // verify the minimum number of callsigns were generated
    EXPECT_EQ(MIN_CALLSIGNS, resultListEnemy.size());
}

TEST(TestCallsignGenerator, TestGenerateTooMany)
{
    // request too many friendly callsigns
    auto resultListFriend = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MAX_CALLSIGNS + 1);

    // verify that up to the max number of callsigns are returned
    EXPECT_EQ(MAX_CALLSIGNS, resultListFriend.size());

    // verify no duplicates are returned
    std::unordered_set<std::string> friendSet;
    for(auto resultItr : resultListFriend)
    {
        auto resultPair = friendSet.insert(resultItr);
        EXPECT_TRUE(resultPair.second);
    }
    EXPECT_EQ(friendSet.size(), MAX_CALLSIGNS);

    // request too many enemy callsigns
    auto resultListEnemy = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MAX_CALLSIGNS + 1);

    // verify that up to the max number of callsigns are returned
    EXPECT_EQ(MAX_CALLSIGNS, resultListEnemy.size());

    // verify no duplicates are returned
    std::unordered_set<std::string> enemySet;
    for(auto resultItr : resultListEnemy)
    {
        auto resultPair = enemySet.insert(resultItr);
        EXPECT_TRUE(resultPair.second);
    }
    EXPECT_EQ(enemySet.size(), MAX_CALLSIGNS);
}

TEST(TestCallsignGenerator, TestGenerateMax)
{
    // request max number of friendly callsigns
    auto resultListFriend = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MAX_CALLSIGNS);

    // verify that up to the max number of callsigns are returned
    EXPECT_EQ(MAX_CALLSIGNS, resultListFriend.size());

    // verify no duplicates are returned
    std::unordered_set<std::string> friendSet;
    for(auto resultItr : resultListFriend)
    {
        auto resultPair = friendSet.insert(resultItr);
        EXPECT_TRUE(resultPair.second);
    }
    EXPECT_EQ(friendSet.size(), MAX_CALLSIGNS);

    // request max nyumber of enemy callsigns
    auto resultListEnemy = vector::util::CallsignGenerator::GenerateRandomFriendCallsigns(MAX_CALLSIGNS);

    // verify that up to the max number of callsigns are returned
    EXPECT_EQ(MAX_CALLSIGNS, resultListEnemy.size());

    // verify no duplicates are returned
    std::unordered_set<std::string> enemySet;
    for(auto resultItr : resultListEnemy)
    {
        auto resultPair = enemySet.insert(resultItr);
        EXPECT_TRUE(resultPair.second);
    }
    EXPECT_EQ(enemySet.size(), MAX_CALLSIGNS);
}