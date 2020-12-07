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
    std::shared_ptr<MockPlayer> playerOne = std::make_shared<MockPlayer>();
    std::shared_ptr<MockPlayer> playerTwo = std::make_shared<MockPlayer>();

    vector::game::GameManager gameManager;

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