#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sim/GameEngine.h"
#include "sim/MoverInterface.h"

class MockMover : public vector::sim::MoverInterface
{
    public:
        MOCK_METHOD(std::string, GetID, (), (const, override));
        MOCK_METHOD(void, Move, (), (override));
        MOCK_METHOD(bool, SetNewHeading, (const vector::sim::angle), (override));
        MOCK_METHOD(bool, SetInitialInertialData, (const vector::sim::InertialData), (override));
        MOCK_METHOD(vector::sim::InertialData, GetInertialData, (), (const, override));
        MOCK_METHOD(void, Destroy, (), (override));
        MOCK_METHOD(bool, GetStatus, (), (const, override));
        MOCK_METHOD(uint8_t, GetTeam, (), (const, override));
        MOCK_METHOD(std::string, ToString, (), (const, override));
};

TEST(TestGameEngine, TestAddMover)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    // sucessfully add Mover with unique ID
    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));
    bool added = engine.AddMover(mockMover);
    EXPECT_TRUE(added);
    auto mover = engine.GetMover(moverID);

    // verify retrieved ID matches set ID
    EXPECT_EQ(moverID, mover->GetID());

    // verify nullptr is returned on bad ID
    mover = engine.GetMover("fake");
    EXPECT_EQ(nullptr, mover);
}

TEST(TestGameEngine, TestTick)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    // sucessfully add Mover with unique ID
    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));
    bool added = engine.AddMover(mockMover);
    EXPECT_TRUE(added);

    // Move() is called on Mover's with status true (not destroyed)
    EXPECT_CALL(*mockMover, GetStatus()).WillOnce(::testing::Return(true));
    EXPECT_CALL(*mockMover, Move);
    engine.Tick();
}

TEST(TestGameEngine, TestTickDestroyed)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    // sucessfully add Mover with unique ID
    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));
    bool added = engine.AddMover(mockMover);
    EXPECT_TRUE(added);

    // Move() is not called on Movers with status false (destroyed)
    EXPECT_CALL(*mockMover, GetStatus()).WillOnce(::testing::Return(false));
    EXPECT_CALL(*mockMover, Move).Times(0);
    engine.Tick();
}

TEST(TestGameEngine, TestInputCommandVector)
{
    std::string moverID = "brot";
    std::string vectorString = "123";
    vector::sim::angle vectorAngle = 123;

    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    
    vector::sim::GameEngine engine;

    vector::util::Command goodCmd;
    goodCmd.command = vector::util::COMMAND_TYPE::VECTOR;
    goodCmd.subject = moverID;
    goodCmd.object = vectorString;

    vector::util::Command badSubjectCmd;
    badSubjectCmd.command = vector::util::COMMAND_TYPE::VECTOR;
    badSubjectCmd.subject = "fake";
    badSubjectCmd.object = vectorString;

    vector::util::Command badObjectCmd;
    badObjectCmd.command = vector::util::COMMAND_TYPE::VECTOR;
    badObjectCmd.subject = moverID;
    badObjectCmd.object = "fake";

    // sucessfully add Mover with unique ID
    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));
    bool added = engine.AddMover(mockMover);
    EXPECT_TRUE(added);

    // SetNewHeading should be called on receipt of valid vector cmd
    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle));
    engine.InputCommand(goodCmd);

    // SetNewHeading should not be called on receipt of bad vector cmd
    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle)).Times(0);
    engine.InputCommand(badSubjectCmd);

    // SetNewHeading should not be called on receipt of bad vector cmd
    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle)).Times(0);
    engine.InputCommand(badObjectCmd);
}

TEST(TestGameEngine, TestGameState)
{
    std::string moverOneID = "brot";
    uint8_t teamOneID = 1;
    
    std::string moverTwoID = "marm";
    uint8_t teamTwoID = 2;
    
    vector::sim::InertialData expectedIntertialOne;
    expectedIntertialOne.curHeading = 0;
    expectedIntertialOne.curSpeed = 0;
    expectedIntertialOne.xCoord = 0;
    expectedIntertialOne.yCoord = 0;

    vector::sim::InertialData expectedIntertialTwo;
    expectedIntertialTwo.curHeading = 1;
    expectedIntertialTwo.curSpeed = 1;
    expectedIntertialTwo.xCoord = 1;
    expectedIntertialTwo.yCoord = 1;

    vector::sim::MoverState moverStateOne;
    moverStateOne.ID = moverOneID;
    moverStateOne.teamID = teamOneID;
    moverStateOne.inertialData = expectedIntertialOne;

    vector::sim::MoverState moverStateTwo;
    moverStateTwo.ID = moverTwoID;
    moverStateTwo.teamID = teamTwoID;
    moverStateTwo.inertialData = expectedIntertialTwo;

    vector::sim::GameState expectedState;
    expectedState.moverList.push_back(moverStateOne);
    expectedState.moverList.push_back(moverStateTwo);
    
    std::shared_ptr<MockMover> mockMoverOne = std::make_shared<MockMover>();
    std::shared_ptr<MockMover> mockMoverTwo = std::make_shared<MockMover>();
    
    vector::sim::GameEngine engine;

    // GetGameState will pull ID, TeamID and InertialData from all Movers
    EXPECT_CALL(*mockMoverOne, GetID()).WillRepeatedly(::testing::Return(moverOneID));
    EXPECT_CALL(*mockMoverOne, GetTeam()).WillOnce(::testing::Return(teamOneID));
    EXPECT_CALL(*mockMoverOne, GetInertialData()).WillOnce(::testing::Return(expectedIntertialOne));

    EXPECT_CALL(*mockMoverTwo, GetID()).WillRepeatedly(::testing::Return(moverTwoID));
    EXPECT_CALL(*mockMoverTwo, GetTeam()).WillOnce(::testing::Return(teamTwoID));
    EXPECT_CALL(*mockMoverTwo, GetInertialData()).WillOnce(::testing::Return(expectedIntertialTwo));

    // sucessfully add Mover with unique ID
    bool added = engine.AddMover(mockMoverOne);
    EXPECT_TRUE(added);
    
    added = engine.AddMover(mockMoverTwo);
    EXPECT_TRUE(added);

    vector::sim::GameState gameState = engine.GetGameState();

    // GameState should have two Movers
    EXPECT_EQ(2, gameState.moverList.size());

    EXPECT_EQ(moverOneID, gameState.moverList.at(0).ID);
    EXPECT_EQ(teamOneID, gameState.moverList.at(0).teamID);
    EXPECT_EQ(expectedIntertialOne.curHeading, gameState.moverList.at(0).inertialData.curHeading);
    EXPECT_EQ(expectedIntertialOne.curSpeed, gameState.moverList.at(0).inertialData.curSpeed);
    EXPECT_EQ(expectedIntertialOne.xCoord, gameState.moverList.at(0).inertialData.xCoord);
    EXPECT_EQ(expectedIntertialOne.yCoord, gameState.moverList.at(0).inertialData.yCoord);

    EXPECT_EQ(moverTwoID, gameState.moverList.at(1).ID);
    EXPECT_EQ(teamTwoID, gameState.moverList.at(1).teamID);
    EXPECT_EQ(expectedIntertialTwo.curHeading, gameState.moverList.at(1).inertialData.curHeading);
    EXPECT_EQ(expectedIntertialTwo.curSpeed, gameState.moverList.at(1).inertialData.curSpeed);
    EXPECT_EQ(expectedIntertialTwo.xCoord, gameState.moverList.at(1).inertialData.xCoord);
    EXPECT_EQ(expectedIntertialTwo.yCoord, gameState.moverList.at(1).inertialData.yCoord);
}