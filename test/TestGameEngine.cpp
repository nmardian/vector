#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "sim/GameEngine.h"
#include "sim/MoverInterface.h"

class MockMover : public vector::sim::MoverInterface
{
    public:
        MockMover(const std::string& id)
        : m_ID(id)
        {}

        std::string MockMover::GetID() const
        {
            return m_ID;
        }
        MOCK_METHOD(void, Move, (), (override));
        MOCK_METHOD(bool, SetNewHeading, (const vector::sim::angle), (override));
        MOCK_METHOD(bool, SetInitialInertialData, (const vector::sim::InertialData), (override));
        MOCK_METHOD(vector::sim::InertialData, GetInertialData, (), (const, override));
        MOCK_METHOD(void, Destroy, (), (override));
        MOCK_METHOD(bool, GetStatus, (), (const, override));
        MOCK_METHOD(std::string, ToString, (), (const, override));

    private:
        std::string m_ID;
};

TEST(TestGameEngine, TestAddMoverGood)
{
    std::shared_ptr<MockMover> mockMover = std::make_shared<MockMover>("brot");
    vector::sim::GameEngine engine;

    bool added = engine.AddMover(mockMover);

    EXPECT_TRUE(added);

    auto mover = engine.GetMover("brot");

    EXPECT_EQ("brot", mover->GetID());
}