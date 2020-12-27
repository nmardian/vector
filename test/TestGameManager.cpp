#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game/GameManager.h"
#include "game/PlayerInterface.h"
#include "game/GameTypes.h"
#include "game/GameSettingsInterface.h"
#include "sim/SimTypes.h"
#include "sim/GameEngine.h"

#include <vector>
#include <memory>

class MockPlayer : public vector::game::PlayerInterface
{
    public:
        MOCK_METHOD(std::string,  GetPlayerID, (), (const, override));
        MOCK_METHOD(vector::sim::team_ID, GetTeamID, (), (const, override));
        MOCK_METHOD(bool, IsReady, (), (const, override));
        MOCK_METHOD(void, UpdateGameState, (const vector::sim::GameState gameState), ());
        MOCK_METHOD(void, RegisterCommandFunction, (std::function<bool (const std::string playerID, const vector::util::Command cmd)>), ());
}; 

class MockGameSettings : public vector::game::GameSettingsInterface
{
    public:
        MOCK_METHOD(vector::game::GAME_TYPE, GetGameType, (), (const, override));
        MOCK_METHOD(uint8_t, GetNumPlayers, (), (const, override));
        MOCK_METHOD(bool, SetNumPlayers, (const uint8_t numPlayers), (override));
        MOCK_METHOD(uint8_t, GetNumMoversPerSide, (), (const, override));
        MOCK_METHOD(bool, SetNumMoversPerSide, (uint8_t numMoversPerSide), (override));
};

TEST(TestGameManager, TestSetPlayerSlotsMin)
{
    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    // set the number of player slots to be one less than the minimun
    bool result = gameManager.SetNumPlayerSlots(vector::game::MIN_NUM_PLAYERS - 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, TestSetPlayerSlotsMax)
{
    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    // set the number of player slots to be one more than the maximum
    bool result = gameManager.SetNumPlayerSlots(vector::game::MAX_NUM_PLAYERS + 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, TestSetPlayerSlotsValid)
{
    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    // set the number of player slots to be a valid number
    bool result = gameManager.SetNumPlayerSlots(3);

    EXPECT_TRUE(result);

    EXPECT_EQ(3, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, TestSetPlayerSlotsAfterStartAndStop)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);
    gameManager.AddPlayer(mockPlayerTwo);

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));
    ON_CALL(*mockPlayerTwo, IsReady()).WillByDefault(::testing::Return(true));

    // game can only start if the GameType is set
    gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT);

    bool result = gameManager.Start();

    EXPECT_TRUE(result);

    result = gameManager.SetNumPlayerSlots(3);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());

    gameManager.Stop();

    result = gameManager.SetNumPlayerSlots(3);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameManager.GetNumPlayerSlots());
}

TEST(TestGameManager, TestSetupCustom)
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
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    // team IDs
    vector::sim::team_ID teamOneID = 1;
    vector::sim::team_ID teamTwoID = 2;

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    EXPECT_TRUE(gameManager.SetNumPlayerSlots(2));

    // game can only start if the GameType is set
    EXPECT_TRUE(gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT));

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    // add the two players
    EXPECT_TRUE(gameManager.AddPlayer(mockPlayerOne));
    EXPECT_TRUE(gameManager.AddPlayer(mockPlayerTwo));

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));
    ON_CALL(*mockPlayerTwo, IsReady()).WillByDefault(::testing::Return(true));

    // set the UnitData
    EXPECT_TRUE(gameManager.SetUnitData(teamOneID, teamOneData));
    EXPECT_TRUE(gameManager.SetUnitData(teamTwoID, teamTwoData));

    EXPECT_TRUE(gameManager.Start());

    EXPECT_TRUE(gameManager.Stop());
}

TEST(TestGameManager, TestStartGameGood)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));
    
    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);
    gameManager.AddPlayer(mockPlayerTwo);

    // game can only start if the GameType is set
    gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT);

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));
    ON_CALL(*mockPlayerTwo, IsReady()).WillByDefault(::testing::Return(true));

    bool result = gameManager.Start();

    EXPECT_TRUE(result);

    gameManager.Stop();
}

TEST(TestGameManager, TestStartGameUnkGameType)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));
    
    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);
    gameManager.AddPlayer(mockPlayerTwo);

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));
    ON_CALL(*mockPlayerTwo, IsReady()).WillByDefault(::testing::Return(true));

    bool result = gameManager.Start();

    // GameType has not been set, game cannot start
    EXPECT_FALSE(result);
}

TEST(TestGameManager, TestStartGameNotEnoughPlayers)
{
    // default number of players is 2, create just one mock player
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    // game can only start if the GameType is set
    gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT);
    
    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);

    // game can only start if all players indicate they are ready
    ON_CALL(*mockPlayerOne, IsReady()).WillByDefault(::testing::Return(true));

    bool result = gameManager.Start();

    // only one player added, game cannot start
    EXPECT_FALSE(result);
}

TEST(TestGameManager, TestStartGamePlayersNotReady)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    auto gameEnginePtr = std::make_unique<vector::sim::GameEngine>();
    auto gameSettingsPtr = std::make_unique<MockGameSettings>();

    vector::game::GameManager gameManager(std::move(gameEnginePtr), std::move(gameSettingsPtr));

    // game can only start if the GameType is set
    gameManager.SetGameType(vector::game::GAME_TYPE::DOGFIGHT);
    
    // Start fails unless all player slots are filled
    // add mock players to game
    gameManager.AddPlayer(mockPlayerOne);
    gameManager.AddPlayer(mockPlayerTwo);

    // game can only start if all players indicate they are ready
    EXPECT_CALL(*mockPlayerOne, IsReady()).WillOnce(::testing::Return(true));
    // one player is not ready
    EXPECT_CALL(*mockPlayerTwo, IsReady()).WillOnce(::testing::Return(false));

    bool result = gameManager.Start();

    // player two not ready, game cannot start
    EXPECT_FALSE(result);
}