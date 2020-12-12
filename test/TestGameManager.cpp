#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game/GameManager.h"
#include "game/PlayerInterface.h"
#include "game/GameTypes.h"

#include <vector>
#include <memory>

class MockPlayer : public vector::game::PlayerInterface
{
    public:
        MOCK_METHOD(std::string,  GetPlayerID, (), (const, override));
        MOCK_METHOD(vector::game::team_ID, GetTeamID, (), (const, override));
        MOCK_METHOD(bool, IsReady, (), (const, override));
        MOCK_METHOD(void, UpdateGameState, (const vector::sim::GameState gameState), ());
        MOCK_METHOD(void, RegisterCommandFunction, (std::function<bool (const std::string playerID, const vector::util::Command cmd)>), ());
}; 

TEST(TestGameManager, TestSetPlayerSlotsMin)
{
    vector::game::GameManager gameManager;

    // set the number of player slots to be one less than the minimun
    bool result = gameManager.SetNumPlayerSlots(vector::game::MIN_NUM_PLAYERS - 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, TestSetPlayerSlotsMax)
{
    vector::game::GameManager gameManager;

    // set the number of player slots to be one more than the maximum
    bool result = gameManager.SetNumPlayerSlots(vector::game::MAX_NUM_PLAYERS + 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGamerManager, TestSetPlayerSlotsValid)
{
    vector::game::GameManager gameManager;

    // set the number of player slots to be a valid number
    bool result = gameManager.SetNumPlayerSlots(3);

    EXPECT_TRUE(result);

    EXPECT_EQ(3, gameManager.GetNumPlayerSlots());
}

TEST(TestGamerManager, TestSetPlayerSlotsAfterStartAndStop)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    vector::game::GameManager gameManager;

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);
    gameManager.AddPlayer(mockPlayerTwo);

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));
    ON_CALL(*mockPlayerTwo, IsReady()).WillByDefault(::testing::Return(true));

    gameManager.Start();

    bool result = gameManager.SetNumPlayerSlots(3);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());

    gameManager.Stop();

    result = gameManager.SetNumPlayerSlots(3);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, DISABLED_TestSetupCustom)
{
    // create a list of custom callsigns
    std::vector<vector::game::UnitData> teamOneData;
    vector::game::UnitData unit;
    unit.unitType = vector::game::UNIT_TYPE::FIGHTER;

    unit.callsign = "alph";
    teamOneData.push_back(unit);

    unit.callsign = "brav";
    teamOneData.push_back(unit);

    unit.callsign = "char";
    teamOneData.push_back(unit);

    unit.callsign = "delt";
    teamOneData.push_back(unit);

    unit.callsign = "echo";
    teamOneData.push_back(unit);

    // create an identical list of custom callsigns
    std::vector<vector::game::UnitData> teamTwoData;
    unit.callsign = "alph";
    teamTwoData.push_back(unit);

    unit.callsign = "brav";
    teamTwoData.push_back(unit);

    unit.callsign = "char";
    teamTwoData.push_back(unit);

    unit.callsign = "delt";
    teamTwoData.push_back(unit);

    unit.callsign = "echo";
    teamTwoData.push_back(unit);

    // create two players
    std::shared_ptr<MockPlayer> playerOne = std::make_shared<MockPlayer>();
    std::shared_ptr<MockPlayer> playerTwo = std::make_shared<MockPlayer>();

    vector::game::GameManager gameManager;

    gameManager.SetNumPlayerSlots(2);

    EXPECT_EQ(2, gameManager.GetNumPlayerSlots());

    // set the GameType to DogFight
    gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT);

    // add the two players
    gameManager.AddPlayer(playerOne);
    gameManager.AddPlayer(playerTwo);

    // set the UnitData
    gameManager.SetUnitData(playerOne->GetTeamID(), teamOneData);
    gameManager.SetUnitData(playerTwo->GetTeamID(), teamTwoData);

    // Start that Game
    gameManager.Start();
}