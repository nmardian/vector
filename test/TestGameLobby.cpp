#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game/GameLobby.h"
#include "game/GamePhaseManager.h"
#include "game/PlayerInterface.h"
#include "game/GameTypes.h"

#include <memory>

class MockPlayer : public vector::game::PlayerInterface
{
    public:
        MOCK_METHOD(std::string,  GetPlayerID, (), (const, override));
        MOCK_METHOD(vector::sim::team_ID, GetTeamID, (), (const, override));
        MOCK_METHOD(bool, IsReady, (), (const, override));
        MOCK_METHOD(void, UpdateLobbyState, (const vector::game::LobbyState lobbyState), (override));
        MOCK_METHOD(void, UpdateGameState, (const vector::sim::GameState gameState), ());
        MOCK_METHOD(void, RegisterCommandFunction, (std::function<bool (const std::string playerID, const vector::util::Command cmd)>), ());
}; 

TEST(TestGameLobby, TestStartStop)
{
    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    // start the lobby
    EXPECT_TRUE(gameLobby.Start());

    // lobby has already started, cannot start again
    EXPECT_FALSE(gameLobby.Start());

    // stop the lobby
    EXPECT_TRUE(gameLobby.Stop());

    // lobby has already been stopped, cannot stop again
    EXPECT_FALSE(gameLobby.Stop());
}

TEST(TestGameLobby, TestSetGameType)
{
    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    // default GameType is UNK
    EXPECT_EQ(vector::game::GAME_TYPE::UNK, gameLobby.GetGameType());

    // set GameType to DogFight
    EXPECT_TRUE(gameLobby.SetGameType(vector::game::GAME_TYPE::DOGFIGHT));

    // verify GameType has been set to DogFight
    EXPECT_EQ(vector::game::GAME_TYPE::DOGFIGHT, gameLobby.GetGameType());
}

TEST(TestGameLobby, TestSetPlayerSlotsMin)
{
    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    // set the number of player slots to be one less than the minimun
    bool result = gameLobby.SetNumPlayerSlots(vector::game::MIN_NUM_PLAYERS - 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameLobby.GetNumPlayerSlots());
}

TEST(TestGameLobby, TestSetPlayerSlotsMax)
{
    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    // set the number of player slots to be one more than the maximum
    bool result = gameLobby.SetNumPlayerSlots(vector::game::MAX_NUM_PLAYERS + 1);

    EXPECT_FALSE(result);

    // number of player slots should be the default (min)
    EXPECT_EQ(vector::game::MIN_NUM_PLAYERS, gameLobby.GetNumPlayerSlots());
}

TEST(TestGameLobby, TestSetPlayerSlotsValid)
{
    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    // set the number of player slots to be a valid number
    bool result = gameLobby.SetNumPlayerSlots(3);

    EXPECT_TRUE(result);

    EXPECT_EQ(3, gameLobby.GetNumPlayerSlots());
}


TEST(TestGameLobby, TestAddPlayer)
{
    // default number of players is 2, create two mock players
    auto mockPlayerOne = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerTwo = std::make_shared<::testing::NiceMock<MockPlayer>>();
    auto mockPlayerThree = std::make_shared<::testing::NiceMock<MockPlayer>>();

    auto phaseMgrPtr = std::make_shared<vector::game::GamePhaseManager>();
    vector::game::GameLobby gameLobby(phaseMgrPtr);

    ON_CALL(*mockPlayerOne, GetPlayerID()).WillByDefault(::testing::Return("nick"));
    ON_CALL(*mockPlayerTwo, GetPlayerID()).WillByDefault(::testing::Return("mar"));

    // add mock players to game up to capacity
    EXPECT_TRUE(gameLobby.AddPlayer(mockPlayerOne));
    EXPECT_TRUE(gameLobby.AddPlayer(mockPlayerTwo));

    // lobby is at capacity, cannot add another player
    EXPECT_FALSE(gameLobby.AddPlayer(mockPlayerThree));
}

