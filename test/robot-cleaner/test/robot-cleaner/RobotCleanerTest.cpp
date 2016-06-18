#include <cut/cut.hpp>
#include <robot-cleaner/RobotCleaner.h>
#include <robot-cleaner/Position.h>
#include <robot-cleaner/Instructions.h>

USING_CUM_NS

FIXTURE(RobotCleanerTest)
{
    RobotCleaner robot;

    void WHEN_I_send_instruction(Instruction* instruction)
    {
        robot.exec(instruction);
    }

    void AND_I_send_instruction(Instruction* instruction)
    {
        WHEN_I_send_instruction(instruction);
    }

    void THEN_the_robot_cleaner_should_be_in(const Position& position)
    {
        ASSERT_THAT(robot.getPosition(), is(position));
    }

    TEST("at the beginning, the robot should be in at the initial position")
    {
        ASSERT_THAT(robot.getPosition(), is(Position(0, 0, NORTH)));
    }

    TEST("left instruction: 1-times")
    {
        WHEN_I_send_instruction(left());
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, WEST));
    }

    TEST("left instruction: 2-times")
    {
        WHEN_I_send_instruction(repeat(left(), 2));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, SOUTH));
    }

    TEST("left instruction: 3-times")
    {
        WHEN_I_send_instruction(repeat(left(), 3));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, EAST));
    }

    TEST("left instruction: 4-times")
    {
        WHEN_I_send_instruction(repeat(left(), 4));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }

    TEST("right instruction: 1-times")
    {
        WHEN_I_send_instruction(right());
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, EAST));
    }

    TEST("right instruction: 2-times")
    {
        WHEN_I_send_instruction(repeat(right(), 2));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, SOUTH));
    }

    TEST("right instruction: 3-times")
    {
        WHEN_I_send_instruction(repeat(right(), 3));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, WEST));
    }

    TEST("right instruction: 4-times")
    {
        WHEN_I_send_instruction(repeat(right(), 4));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }

    TEST("forward instruction")
    {
        WHEN_I_send_instruction(forward());
        THEN_the_robot_cleaner_should_be_in(Position(0, 1, NORTH));
    }

    TEST("1-left, forward instructions")
    {
        WHEN_I_send_instruction(left());
        WHEN_I_send_instruction(forward());

        THEN_the_robot_cleaner_should_be_in(Position(-1, 0, WEST));
    }

    TEST("2-left, forward instructions")
    {
        WHEN_I_send_instruction(repeat(left(), 2));
        WHEN_I_send_instruction(forward());

        THEN_the_robot_cleaner_should_be_in(Position(0, -1, SOUTH));
    }

    TEST("3-left, forward instructions")
    {
        WHEN_I_send_instruction(repeat(left(), 3));
        WHEN_I_send_instruction(forward());

        THEN_the_robot_cleaner_should_be_in(Position(1, 0, EAST));
    }

    TEST("4-left, forward instructions")
    {
        WHEN_I_send_instruction(repeat(left(), 4));
        WHEN_I_send_instruction(forward());

        THEN_the_robot_cleaner_should_be_in(Position(0, 1, NORTH));
    }

    TEST("backward instruction")
    {
        WHEN_I_send_instruction(backward());
        THEN_the_robot_cleaner_should_be_in(Position(0, -1, NORTH));
    }

    TEST("left, backward instruction")
    {
        WHEN_I_send_instruction(left());
        AND_I_send_instruction(backward());
        THEN_the_robot_cleaner_should_be_in(Position(1, 0, WEST));
    }

    TEST("2-left, backward instruction")
    {
        WHEN_I_send_instruction(repeat(left(), 2));
        AND_I_send_instruction(backward());
        THEN_the_robot_cleaner_should_be_in(Position(0, 1, SOUTH));
    }

    TEST("3-left, backward instruction")
    {
        WHEN_I_send_instruction(repeat(left(), 3));
        AND_I_send_instruction(backward());
        THEN_the_robot_cleaner_should_be_in(Position(-1, 0, EAST));
    }

    TEST("4-left, backward instruction")
    {
        WHEN_I_send_instruction(repeat(left(), 4));
        AND_I_send_instruction(backward());
        THEN_the_robot_cleaner_should_be_in(Position(0, -1, NORTH));
    }

    TEST("round instruction")
    {
        WHEN_I_send_instruction(round());
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, SOUTH));
    }

    TEST("forward(n) instruction")
    {
        WHEN_I_send_instruction(forward_n(10));
        THEN_the_robot_cleaner_should_be_in(Position(0, 10, NORTH));
    }

    TEST("forward(n) instruction: n out of bound")
    {
        WHEN_I_send_instruction(forward_n(11));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }

    TEST("backward(n) instruction")
    {
        WHEN_I_send_instruction(backward_n(10));
        THEN_the_robot_cleaner_should_be_in(Position(0, -10, NORTH));
    }

    TEST("backward(n) instruction: n out of bound")
    {
        WHEN_I_send_instruction(backward_n(11));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }

    TEST("sequential instruction")
    {
        WHEN_I_send_instruction(sequential(left(), forward(), round()));
        THEN_the_robot_cleaner_should_be_in(Position(-1, 0, EAST));
    }

    TEST("repeat instruction")
    {
        WHEN_I_send_instruction(repeat(forward_n(2), 2));
        THEN_the_robot_cleaner_should_be_in(Position(0, 4, NORTH));
    }

    TEST("repeat instruction: n out of bound")
    {
        WHEN_I_send_instruction(repeat(forward_n(2), 11));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }
};
