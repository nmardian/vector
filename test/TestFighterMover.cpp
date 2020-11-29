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
        vector::sim::FighterMover mover("brot", 1, perfValues);
        
        // verify default values are set correctly
        EXPECT_EQ("brot", mover.GetID());
        EXPECT_EQ(1, mover.GetTeam());
        EXPECT_TRUE(mover.GetStatus());
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestDestroy)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // A Mover's status defaults to true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // A destroyed Mover's status is false
        mover.Destroy();
        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestInitialPosValidZeroes)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 0;
        initialPos.curSpeed = 0.0;
        initialPos.xCoord = 0.0;
        initialPos.yCoord = 0.0;

        // Valid initial inertial data should be accepted
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_TRUE(valid);

        // Verify valid initial inertial data is stored
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestInitialPosValidNonzeroes)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = 90;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = 100.0;
        initialPos.yCoord = 200.0;

        // Valid initial inertial data should be accepted
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_TRUE(valid);

        // Verify valid initial inertial data is stored
        EXPECT_EQ(mover.GetInertialData().curHeading, initialPos.curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, initialPos.curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, initialPos.xCoord);
        EXPECT_EQ(mover.GetInertialData().yCoord, initialPos.yCoord);
    }

    TEST_F(TestFighterMover, TestInitialPosInvalidLow)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = vector::sim::HEADING_MIN - 1;
        initialPos.curSpeed = vector::sim::SPEED_MIN - 1;
        initialPos.xCoord = vector::sim::X_COORD_MIN - 1;
        initialPos.yCoord = vector::sim::Y_COORD_MIN - 1;

        // Valid initial inertial data should be accepted
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_FALSE(valid);

        // Verify valid initial inertial data is stored
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestInitialPosInvalidHigh)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        vector::sim::InertialData initialPos;
        initialPos.curHeading = vector::sim::HEADING_MAX + 1;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX + 1;
        initialPos.xCoord = vector::sim::X_COORD_MAX + 1;
        initialPos.yCoord = vector::sim::Y_COORD_MAX + 1;
        
        // Valid initial inertial data should be accepted
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_FALSE(valid);
        
        // Verify valid initial inertial data is stored
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);
        EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
        EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
        EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
    }

    TEST_F(TestFighterMover, TestSetHeadingValid)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // default heading is 0
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);

        // 90 is a valid heading
        bool valid = mover.SetNewHeading(90);
        EXPECT_TRUE(valid);

        // 0 is the low boundary on valid heading [0 - 359]
        valid = mover.SetNewHeading(0);
        EXPECT_TRUE(valid);

        // 359 is the high boundary on valid heading [0 - 359]
        valid = mover.SetNewHeading(359);
        EXPECT_TRUE(valid);
    }

    TEST_F(TestFighterMover, TestSetHeadingInvalid)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // default heading is 0
        EXPECT_EQ(mover.GetInertialData().curHeading, 0);

        // 0 is the low boundary on valid heading [0 - 359]
        bool valid = mover.SetNewHeading(-1);
        EXPECT_FALSE(valid);

        // 359 is the high boundary on valid heading [0 - 359]
        valid = mover.SetNewHeading(360);
        EXPECT_FALSE(valid);

        // Mover should accept valid headings after invalid headings
        valid = mover.SetNewHeading(1);
        EXPECT_TRUE(valid);
    }

    TEST_F(TestFighterMover, TestMoveStraightConstSpeed)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover in the middle of the map
        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        // set and validate initial inertial data
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_TRUE(valid);
        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        // the Mover is not turning to a new heading,
        // so, its position after a Move should be: initialPos + (1 * curSpeed) in the x and y components
        mover.Move();
        EXPECT_EQ((curX + vector::util::MathUtil::GetXComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().xCoord);
        EXPECT_EQ((curY + vector::util::MathUtil::GetYComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().yCoord);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
        EXPECT_EQ(curHeading, mover.GetInertialData().curHeading);

        // the Mover is not turning to a new heading,
        // so, its position after two Moves should be: initialPos + (2 * curSpeed) in the x and y components
        mover.Move();
        EXPECT_EQ((curX + (2 * vector::util::MathUtil::GetXComponentOfSpeed(curSpeed, curHeading))), mover.GetInertialData().xCoord);
        EXPECT_EQ((curY + (2 * vector::util::MathUtil::GetYComponentOfSpeed(curSpeed, curHeading))), mover.GetInertialData().yCoord);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
        EXPECT_EQ(curHeading, mover.GetInertialData().curHeading);        
    }

    TEST_F(TestFighterMover, TestMoveTurnRight)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover in the middle of the map
        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        // set and validate initial inertial data
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_TRUE(valid);
        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        // give the Mover a new valid heading
        valid = mover.SetNewHeading(curHeading + vector::sim::FIGHTER_TURN_RATE);
        EXPECT_TRUE(valid);
        
        // give the Mover a new heading equal to its turn rate, 
        // so that it will achieve the new heading after one Move
        mover.Move();

        // verify the Mover has achieved the new heading after one Move
        EXPECT_EQ(curHeading + vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        // verify the Mover's speed has decreased by 1x the acceleration / deceleration rate
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX - vector::sim::FIGHTER_ACCL_DCCL, mover.GetInertialData().curSpeed);

        // after a second Move, the Mover should have the desired heading,
        // and its speed should return to normal as it is no longer turning
        // and it only decelerated for one Move
        mover.Move();
        EXPECT_EQ(curHeading + vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
    }

    TEST_F(TestFighterMover, TestMoveTurnLeft)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover in the middle of the map
        vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
        vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
        vector::sim::speed curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        vector::sim::angle curHeading = 0;

        vector::sim::InertialData initialPos;
        initialPos.curHeading = curHeading;
        initialPos.curSpeed = curSpeed;
        initialPos.xCoord = curX;
        initialPos.yCoord = curY;

        // set and validate initial inertial data
        bool valid = mover.SetInitialInertialData(initialPos);
        EXPECT_TRUE(valid);
        EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
        EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
        EXPECT_EQ(mover.GetInertialData().xCoord, curX);
        EXPECT_EQ(mover.GetInertialData().yCoord, curY);

        // give the Mover a new valid heading
        valid = mover.SetNewHeading( vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE );
        EXPECT_TRUE(valid);
        
        // give the Mover a new heading equal to its turn rate, 
        // so that it will achieve the new heading after one Move
        mover.Move();

        // verify the Mover has achieved the new heading after one Move
        EXPECT_EQ(vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        // verify the Mover's speed has decreased by 1x the acceleration / deceleration rate
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX - vector::sim::FIGHTER_ACCL_DCCL, mover.GetInertialData().curSpeed);

        // after a second Move, the Mover should have the desired heading,
        // and its speed should return to normal as it is no longer turning
        // and it only decelerated for one Move
        mover.Move();
        EXPECT_EQ(vector::sim::HEADING_FULL_CIRCLE - vector::sim::FIGHTER_TURN_RATE, mover.GetInertialData().curHeading);
        EXPECT_EQ(vector::sim::FIGHTER_SPEED_MAX, mover.GetInertialData().curSpeed);
    }

    TEST_F(TestFighterMover, TestMoveDestroyTop)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover one Move away from the top boundary heading straight up
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
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover one Move away from the bottom boundary heading straight down
        vector::sim::InertialData initialPos;
        initialPos.curHeading = 180;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MIN + vector::sim::FIGHTER_SPEED_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have Mover move once, bringing it to the boundary
        mover.Move();

        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have the Mover move once more, bringing it past the boundary
        mover.Move();

        // verify the Mover's status is false (destroyed)
        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestMoveDestroyLeft)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover one Move away from the left boundary heading straight left
        vector::sim::InertialData initialPos;
        initialPos.curHeading = 270;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MIN + vector::sim::FIGHTER_SPEED_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have Mover move once, bringing it to the boundary
        mover.Move();

        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have the Mover move once more, bringing it past the boundary
        mover.Move();

        // verify the Mover's status is false (destroyed)
        EXPECT_FALSE(mover.GetStatus());
    }

    TEST_F(TestFighterMover, TestMoveDestroyRight)
    {
        TestFighterMover::SetUp();
        vector::sim::FighterMover mover("brot", 1, perfValues);

        // start the Mover one Move away from the right boundary heading straight right
        vector::sim::InertialData initialPos;
        initialPos.curHeading = 90;
        initialPos.curSpeed = vector::sim::FIGHTER_SPEED_MAX;
        initialPos.xCoord = vector::sim::X_COORD_MAX - vector::sim::FIGHTER_SPEED_MAX;
        initialPos.yCoord = vector::sim::Y_COORD_MAX;
        bool valid = mover.SetInitialInertialData(initialPos);
        
        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have Mover move once, bringing it to the boundary
        mover.Move();

        // verify the Mover's status is true (not destroyed)
        EXPECT_TRUE(mover.GetStatus());

        // have the Mover move once more, bringing it past the boundary
        mover.Move();

        // verify the Mover's status is false (destroyed)
        EXPECT_FALSE(mover.GetStatus());
    }
} // namespace