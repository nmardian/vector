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
        MOCK_METHOD(std::string, ToString, (), (const, override));
};

TEST(TestGameEngine, TestAddMover)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));
    bool added = engine.AddMover(mockMover);

    EXPECT_TRUE(added);

    auto mover = engine.GetMover(moverID);

    EXPECT_EQ(moverID, mover->GetID());

    mover = engine.GetMover("fake");

    EXPECT_EQ(nullptr, mover);
}

TEST(TestGameEngine, TestTick)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));

    bool added = engine.AddMover(mockMover);

    EXPECT_TRUE(added);

    EXPECT_CALL(*mockMover, GetStatus()).WillOnce(::testing::Return(true));
    EXPECT_CALL(*mockMover, Move);

    engine.Tick();
}

TEST(TestGameEngine, TestTickDestroyed)
{
    std::string moverID = "brot";
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>();
    vector::sim::GameEngine engine;

    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));

    bool added = engine.AddMover(mockMover);

    EXPECT_TRUE(added);

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

    EXPECT_CALL(*mockMover, GetID()).WillRepeatedly(::testing::Return(moverID));

    bool added = engine.AddMover(mockMover);

    EXPECT_TRUE(added);

    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle));

    engine.InputCommand(goodCmd);

    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle)).Times(0);

    engine.InputCommand(badSubjectCmd);

    EXPECT_CALL(*mockMover, SetNewHeading(vectorAngle)).Times(0);

    engine.InputCommand(badObjectCmd);
}