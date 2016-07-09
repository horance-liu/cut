#include <robot-cleaner/Instructions.h>
#include <robot-cleaner/Position.h>
#include <memory>

namespace {
#define ASSERT_BETWEEN(num, min, max)   \
    do {                                \
       if (num < min || num > max)      \
           return new EmptyInstruction; \
    } while(0)

    struct EmptyInstruction : Instruction
    {
        __OVERRIDE__(void exec(Point&, Orientation&) const) {}
    };
}

namespace
{
    struct TurnToInstruction : Instruction
    {
        explicit TurnToInstruction(bool left) : left(left)
        {}

    private:
        __OVERRIDE__(void exec(Point&, Orientation& orientation) const)
        {
            orientation = orientation.turnTo(left);
        }

    private:
        bool left;
    };
}

Instruction* left()
{
    return new TurnToInstruction(true);
}

Instruction* right()
{
    return new TurnToInstruction(false);
}

namespace
{
    struct MoveOnInstruction : Instruction
    {
        explicit MoveOnInstruction(bool forward, int n)
          : step(prefix(forward)*n)
        {}

    private:
        __OVERRIDE__(void exec(Point& point, Orientation& orientation) const)
        {
            point = point.moveOn(step, orientation);
        }

    private:
        static int prefix(bool forward)
        {
            return forward ? 1 : -1;
        }

    private:
        int step;
    };

    const auto MIN_MOVE_NUM = 1;
    const auto MAX_MOVE_NUM = 10;

    Instruction* move_on(bool forward, int n)
    {
        ASSERT_BETWEEN(n, MIN_MOVE_NUM, MAX_MOVE_NUM);
        return new MoveOnInstruction(forward,  n);
    }
}

Instruction* forward_n(int n)
{
    return move_on(true, n);
}

Instruction* backward_n(int n)
{
    return move_on(false, n);
}

namespace
{
    struct RepeatedInstruction : Instruction
    {
        RepeatedInstruction(Instruction* instruction, int n)
         : instruction(instruction), n(n)
        {}

    private:
        __OVERRIDE__(void exec(Point& point, Orientation& orientation) const)
        {
            for (auto i=0; i<n; i++)
            {
                instruction->exec(point, orientation);
            }
        }

    private:
        std::unique_ptr<Instruction> instruction;
        int n;
    };

    const auto MIN_REPEATED_NUM = 1;
    const auto MAX_REPEATED_NUM = 10;
}

Instruction* repeat(Instruction* instruction, int n)
{
    ASSERT_BETWEEN(n, MIN_REPEATED_NUM, MAX_REPEATED_NUM);
    return new RepeatedInstruction(instruction, n);
}

namespace
{
    struct SequentialInstruction : Instruction
    {
        SequentialInstruction(std::vector<Instruction*>&& instructions)
          : instructions(instructions)
        {}

        ~SequentialInstruction()
        {
            for(auto instruction : instructions)
            {
                delete instruction;
            }
        }

    private:
        __OVERRIDE__(void exec(Point& point, Orientation& orientation) const)
        {
            for(auto instruction : instructions)
            {
                instruction->exec(point, orientation);
            }
        }

    private:
        std::vector<Instruction*> instructions;
    };
}

Instruction* __sequential(std::vector<Instruction*>&& instructions)
{
    return new SequentialInstruction(std::move(instructions));
}
