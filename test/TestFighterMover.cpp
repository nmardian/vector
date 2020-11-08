#include "gtest/gtest.h"
#include "sim/FighterMover.h"
#include "sim/InertialData.h"
#include "sim/SimConstants.h"
#include "sim/SimParams.h"
#include "sim/SimTypes.h"
#include "util/MathUtil.h"

TEST(TestFigherMover, TestPositionDefaultValues)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::FighterMover mover(perfValues);

    EXPECT_EQ(mover.GetInertialData().curHeading, 0);
    EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
    EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
    EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
}

TEST(TestFigherMover, TestInitialPosValidZeroes)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::InertialData initialPos;
    initialPos.curHeading = 0;
    initialPos.curSpeed = 0.0;
    initialPos.xCoord = 0.0;
    initialPos.yCoord = 0.0;

    vector::sim::FighterMover mover(perfValues);

    bool valid = mover.SetInitialInertialData(initialPos);

    EXPECT_TRUE(valid);

    EXPECT_EQ(mover.GetInertialData().curHeading, 0);
    EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
    EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
    EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
}

TEST(TestFigherMover, TestInitialPosValidNonzeroes)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::InertialData initialPos;
    initialPos.curHeading = 90;
    initialPos.curSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    initialPos.xCoord = 100.0;
    initialPos.yCoord = 200.0;

    vector::sim::FighterMover mover(perfValues);

    bool valid = mover.SetInitialInertialData(initialPos);

    EXPECT_TRUE(valid);

    EXPECT_EQ(mover.GetInertialData().curHeading, initialPos.curHeading);
    EXPECT_EQ(mover.GetInertialData().curSpeed, initialPos.curSpeed);
    EXPECT_EQ(mover.GetInertialData().xCoord, initialPos.xCoord);
    EXPECT_EQ(mover.GetInertialData().yCoord, initialPos.yCoord);
}

TEST(TestFigherMover, TestInitialPosInvalidLow)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::InertialData initialPos;
    initialPos.curHeading = vector::sim::HEADING_MIN - 1;
    initialPos.curSpeed = vector::sim::SPEED_MIN - 1;
    initialPos.xCoord = vector::sim::X_COORD_MIN - 1;
    initialPos.yCoord = vector::sim::Y_COORD_MIN - 1;

    vector::sim::FighterMover mover(perfValues);

    bool valid = mover.SetInitialInertialData(initialPos);

    EXPECT_FALSE(valid);

    EXPECT_EQ(mover.GetInertialData().curHeading, 0);
    EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
    EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
    EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
}

TEST(TestFigherMover, TestInitialPosInvalidHigh)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::InertialData initialPos;
    initialPos.curHeading = vector::sim::HEADING_MAX + 1;
    initialPos.curSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX + 1;
    initialPos.xCoord = vector::sim::X_COORD_MAX + 1;
    initialPos.yCoord = vector::sim::Y_COORD_MAX + 1;

    vector::sim::FighterMover mover(perfValues);

    bool valid = mover.SetInitialInertialData(initialPos);

    EXPECT_FALSE(valid);

    EXPECT_EQ(mover.GetInertialData().curHeading, 0);
    EXPECT_EQ(mover.GetInertialData().curSpeed, 0.0);
    EXPECT_EQ(mover.GetInertialData().xCoord, 0.0);
    EXPECT_EQ(mover.GetInertialData().yCoord, 0.0);
}

TEST(TestFighterMover, TestMoveStraightConstSpeed)
{
    vector::sim::MoverParams perfValues;
    perfValues.maxSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    perfValues.turnRate = vector::sim::BLUE_FIGHTER_TURN_RATE;

    vector::sim::coord curX = vector::sim::X_COORD_MAX / 2;
    vector::sim::coord curY = vector::sim::Y_COORD_MAX / 2;
    vector::sim::speed curSpeed = vector::sim::BLUE_FIGHTER_SPEED_MAX;
    vector::sim::angle curHeading = 0;

    vector::sim::InertialData initialPos;
    initialPos.curHeading = curHeading;
    initialPos.curSpeed = curSpeed;
    initialPos.xCoord = curX;
    initialPos.yCoord = curY;

    vector::sim::FighterMover mover(perfValues);
    bool valid = mover.SetInitialInertialData(initialPos);

    EXPECT_TRUE(true);

    EXPECT_EQ(mover.GetInertialData().curHeading, curHeading);
    EXPECT_EQ(mover.GetInertialData().curSpeed, curSpeed);
    EXPECT_EQ(mover.GetInertialData().xCoord, curX);
    EXPECT_EQ(mover.GetInertialData().yCoord, curY);

    mover.Move();

    EXPECT_EQ((curX + vector::util::MathUtil::GetXComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().xCoord);
    EXPECT_EQ((curY + vector::util::MathUtil::GetYComponentOfSpeed(curSpeed, curHeading)), mover.GetInertialData().yCoord);

}
