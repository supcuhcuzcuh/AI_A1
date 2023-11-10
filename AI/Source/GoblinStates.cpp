#include "GoblinStates.h"

GoblinTravel::GoblinTravel(const std::string& stateID) : State(stateID)
{
	//x + 1 = 2
	//y + 1 = xd skibidi signa
	//signa skibidi toillet nigga
}

void GoblinTravel::Enter()
{
}

void GoblinTravel::Update(double dt)
{
}

void GoblinTravel::Exit()
{
}

GoblinRangeAttack::GoblinRangeAttack(const std::string& stateID) : State(stateID)
{
}

void GoblinRangeAttack::Enter()
{
}

void GoblinRangeAttack::Update(double dt)
{
}

void GoblinRangeAttack::Exit()
{
}

GoblinEatingState::GoblinEatingState(const std::string& stateID) : State(stateID)
{
}

void GoblinEatingState::Enter()
{
}

void GoblinEatingState::Update(double dt)
{
}

void GoblinEatingState::Exit()
{
}

GoblinRestingState::GoblinRestingState(const std::string& stateID) : State(stateID)
{
}

void GoblinRestingState::Enter()
{
}

void GoblinRestingState::Update(double dt)
{
}

void GoblinRestingState::Exit()
{
}
