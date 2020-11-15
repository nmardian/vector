#include "gtest/gtest.h"
#include "sim/FighterMover.h"
#include "sim/InertialData.h"
#include "sim/SimConstants.h"
#include "sim/SimParams.h"
#include "sim/SimTypes.h"
#include "util/MathUtil.h"

namespace
{
    class TestFighterMover : public testing::Test
    {
        protected:
            void SetUp() override
            {
                perfValues.maxSpeed = vector::sim::FIGHTER_SPEED_MAX;
                perfValues.turnRate = vector::sim::FIGHTER_TURN_RATE;
            }

            vector::sim::MoverParams perfValues;
    };

    TEST_F(TestFighterMover, TestDefaultVals)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);
        
        EXPECT_EQ("brot", mover.GetID());
        EXPECT_TRUE(mover.GetStatus());
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestDestroy)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        EXPECT_TRUE(mover.GetStatus());

        mover.Destroy();

        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestInitialPosValidZeroes)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 0;
        initialPos.curSpeed = 0.0;
        initialPos.xCoord = 0.0;
        initialPos.yCoord = 0.0;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(valid);

        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestInitialPosValidNonzeroes)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 90;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = 100.0;
        initialPos.yCoord = 200.0;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(valid);

        EXPECT_EQ(mover.GetInertialData().curHeading, initialPos.curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, initialPos.curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, initialPos.xCoord);
        EXPECT_EQ(mover.GetInertialData().yCoord, initialPos.yCoord);
    }

    TEST_F(TestFighterMover, TestInitialPosInvalidLow)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = vector::sim::HEADING_MIN - 1;
        initialPos.curSpeed = vector::sim::SPEED_MIN - 1;
        initialPos.xCoord = vector::sim::X_COORD_MIN - 1;
        initialPos.yCoord = vector::sim::Y_COORD_MIN - 1;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_FALSE(valid);

        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestInitialPosInvalidHigh)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = vector::sim::HEADING_MAX + 1;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX + 1;
        initialPos.xCoord = vector::sim::X_COORD_MAX + 1;
        initialPos.yCoord = vector::sim::Y_COORD_MAX + 1;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_FALSE(valid);

        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestSetHeadingValid)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        EXPECT_EQ(mover.GetInertialData().curHeading, 0);

        bool valid = mover.SetNewHeading(90);
        EXPECT_TRUE(valid);

        valid = mover.SetNewHeading(0);
        EXPECT_TRUE(valid);

        valid = mover.SetNewHeading(359);
        EXPECT_TRUE(valid);
    }

    TEST_F(TestFighterMover, TestSetHeadingInvalid)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        EXPECT_EQ(mover.GetInertialData().curHeading, 0);

        bool valid = mover.SetNewHeading(-1);
        EXPECT_FALSE(valid);

        valid = mover.SetNewHeading(360);
        EXPECT_FALSE(valid);

        valid = mover.SetNewHeading(1);
        EXPECT_TRUE(valid);
    }

    TEST_F(TestFighterMover, TestMoveStraightConstSpeed)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(true);

        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        mover.Move();

        EXPECT_EQ((curX + vector::util::MathUtil::GetXComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().xCoord);
        EXPECT_EQ((curY + vector::util::MathUtil::GetYComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().yCoord);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
        EXPECT_EQ(curHeading, mover.GetInertialData().curHeading);

        mover.Move();

        EXPECT_EQ((curX + (2 * vector::util::MathUtil::GetXComponentOfSpeed(curSpeed, curHeading))), mover.GetInertialData().xCoord);
        EXPECT_EQ((curY + (2 * vector::util::MathUtil::GetYComponentOfSpeed(curSpeed, curHeading))), mover.GetInertialData().yCoord);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
        EXPECT_EQ(curHeading, mover.GetInertialData().curHeading);        
    }

    TEST_F(TestFighterMover, TestMoveTurnRight)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(true);

        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        valid = mover.SetNewHeading(curHeading + vector::sim::FIGHTER_TURN_RATE);
        EXPECT_TRUE(true);
        
        mover.Move();

        EXPECT_EQ(curHeading + vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX - vector::sim::FIGHTER_ACCL_DCCL, mover.GetInertialData().curSpeed);

        mover.Move();

        EXPECT_EQ(curHeading + vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
    }

    TEST_F(TestFighterMover, TestMoveTurnLeft)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(true);

        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        valid = mover.SetNewHeading( vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE );
        EXPECT_TRUE(true);
        
        mover.Move();

        EXPECT_EQ(vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX - vector::sim::FIGHTER_ACCL_DCCL, mover.GetInertialData().curSpeed);

        mover.Move();

        EXPECT_EQ(vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
    }

    TEST_F(TestFighterMover, TestMoveDestroyTop)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 0;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MAX - vector::sim::FIGHTER_SPEED_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);

        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestMoveDestroyBottom)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 180;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MIN + vector::sim::FIGHTER_SPEED_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestMoveDestroyLeft)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 270;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MIN + vector::sim::FIGHTER_SPEED_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestMoveDestroyRight)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 90;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MAX - vector::sim::FIGHTER_SPEED_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_TRUE(mover.GetStatus());

        mover.Move();

        EXPECT_FALSE(mover.GetStatus());
    }
} // namespace