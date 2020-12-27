#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game/DogfightGameSettings.h"

#include "game/GameConstants.h"

TEST(TestDogfightGameSettings, TestDogfightDefaultSettings)
{
    vector::game::DogfightGameSettings settings;

    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, settings.GetGameType());

    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_PLAYERS, settings.GetNumPlayers());

    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_MOVERS_PER_SIDE, settings.GetNumMoversPerSide());
}

TEST(TestDogfightGameSettings, TestDogfightBadLow)
{
    vector::game::DogfightGameSettings settings;

    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, settings.GetGameType());

    // 1 below the min number of players
    EXPECT_FALSE(settings.SetNumPlayers(vector::game::MIN_NUM_PLAYERS - 1));

    // 1 below the min number of movers per side
    EXPECT_FALSE(settings.SetNumMoversPerSide(vector::game::MIN_MOVERS_PER_SIDE - 1));

    // after attempt to set invalid value, default should still be set
    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_PLAYERS, settings.GetNumPlayers());

    // after attempt to set invalid value, default should still be set
    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_MOVERS_PER_SIDE, settings.GetNumMoversPerSide());
}

TEST(TestDogfightGameSettings, TestDogfightBadHigh)
{
    vector::game::DogfightGameSettings settings;

    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, settings.GetGameType());

    // 1 above the max number of players
    EXPECT_FALSE(settings.SetNumPlayers(vector::game::MAX_NUM_PLAYERS + 1));

    // 1 above the max number of movers per side
    EXPECT_FALSE(settings.SetNumMoversPerSide(vector::game::MAX_MOVERS_PER_SIDE + 1));

    // after attempt to set invalid value, default should still be set
    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_PLAYERS, settings.GetNumPlayers());

    // after attempt to set invalid value, default should still be set
    EXPECT_EQ(vector::game::DOGFIGHT_DEFAULT_NUM_MOVERS_PER_SIDE, settings.GetNumMoversPerSide());
}

TEST(TestDogfightGameSettings, TestDogfightGoodLow)
{
    vector::game::DogfightGameSettings settings;

    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, settings.GetGameType());

    // set the min number of players
    EXPECT_TRUE(settings.SetNumPlayers(vector::game::MIN_NUM_PLAYERS));

    // min number of movers per side
    EXPECT_TRUE(settings.SetNumMoversPerSide(vector::game::MIN_MOVERS_PER_SIDE));

    // valid value should be set
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, settings.GetNumPlayers());

    // valid value should be set
    EXPECT_EQ(vector::game::MIN_MOVERS_PER_SIDE, settings.GetNumMoversPerSide());
}

TEST(TestDogfightGameSettings, TestDogfightGoodHigh)
{
    vector::game::DogfightGameSettings settings;

    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, settings.GetGameType());

    // set the max number of players
    EXPECT_TRUE(settings.SetNumPlayers(vector::game::MAX_NUM_PLAYERS));

    // set the max number of movers per side
    EXPECT_TRUE(settings.SetNumMoversPerSide(vector::game::MAX_MOVERS_PER_SIDE));

    // valid value should be set
    EXPECT_EQ(vector::game::MAX_NUM_PLAYERS, settings.GetNumPlayers());

    // valid value should be set
    EXPECT_EQ(vector::game::MAX_MOVERS_PER_SIDE, settings.GetNumMoversPerSide());
}