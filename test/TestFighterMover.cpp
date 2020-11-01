#include "gtest/gtest.h"
#include "sim/FighterMover.h"
#include "sim/PositionalData.h"

TEST(TestFigherMover, TestPositionDefaultValues)
{
    vector::sim::FighterMover mover;

    EXPECT_EQ(mover.GetPositionalData().heading, 0);
    EXPECT_EQ(mover.GetPositionalData().xCoord, 0);
    EXPECT_EQ(mover.GetPositionalData().yCoord, 0);
}

TEST(TestFigherMover, TestInitialPosValid)
{
    vector::sim::PositionalData initialPos;
    initialPos.heading = 0;
    initialPos.xCoord = 0;
    initialPos.yCoord = 0;

    vector::sim::FighterMover mover;

    bool valid = mover.SetInitialPosition(initialPos);

    EXPECT_TRUE(valid);

    EXPECT_EQ(mover.GetPositionalData().heading, 0);
    EXPECT_EQ(mover.GetPositionalData().xCoord, 0);
    EXPECT_EQ(mover.GetPositionalData().yCoord, 0);
}

TEST(TestFigherMover, TestInitialPosInvalidLow)
{
    vector::sim::PositionalData initialPos;
    initialPos.heading = -1;
    initialPos.xCoord = -1;
    initialPos.yCoord = -1;

    vector::sim::FighterMover mover;

    bool valid = mover.SetInitialPosition(initialPos);

    EXPECT_FALSE(valid);

    EXPECT_EQ(mover.GetPositionalData().heading, 0);
    EXPECT_EQ(mover.GetPositionalData().xCoord, 0);
    EXPECT_EQ(mover.GetPositionalData().yCoord, 0);
}

TEST(TestFigherMover, TestInitialPosInvalidHigh)
{
    vector::sim::PositionalData initialPos;
    initialPos.heading = 360;

    vector::sim::FighterMover mover;

    bool valid = mover.SetInitialPosition(initialPos);

    EXPECT_FALSE(valid);

    EXPECT_EQ(mover.GetPositionalData().heading, 0);
    EXPECT_EQ(mover.GetPositionalData().xCoord, 0);
    EXPECT_EQ(mover.GetPositionalData().yCoord, 0);
}
