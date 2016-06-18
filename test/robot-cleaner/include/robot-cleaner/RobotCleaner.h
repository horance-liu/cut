#ifndef H632C2FEA_66F0_4B68_B047_121B6CE1482E
#define H632C2FEA_66F0_4B68_B047_121B6CE1482E

#include <robot-cleaner/Position.h>

struct Instruction;

struct RobotCleaner
{
    RobotCleaner();

    void exec(Instruction*);

    const Position& getPosition() const;

private:
    Position position;
};

#endif
