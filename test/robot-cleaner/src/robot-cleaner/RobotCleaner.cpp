#include <robot-cleaner/RobotCleaner.h>
#include <robot-cleaner/Instructions.h>

RobotCleaner::RobotCleaner()
  : position(0, 0, NORTH)
{}

void RobotCleaner::exec(Instruction* instruction)
{
    instruction->exec(__SELF__(position, Point), __SELF__(position, Position));
    delete instruction;
}

const Position& RobotCleaner::getPosition() const
{
    return position;
}
