#pragma once
#include "State.h"
struct GoblinTravel : public State
{
	// Inherited via State
	GoblinTravel(const std::string& stateID);
	virtual void Enter() override;
	virtual void Update(double dt) override;
	virtual void Exit() override;
};

struct GoblinRangeAttack : public State
{
	GoblinRangeAttack(const std::string& stateID);
	// Inherited via State
	virtual void Enter() override;
	virtual void Update(double dt) override;
	virtual void Exit() override;
};

struct GoblinEatingState : public State
{
	GoblinEatingState(const std::string& stateID);
	// Inherited via State
	virtual void Enter() override;
	virtual void Update(double dt) override;
	virtual void Exit() override;
};

struct GoblinRestingState : public State
{
	GoblinRestingState(const std::string& stateID);
	// Inherited via State
	virtual void Enter() override;
	virtual void Update(double dt) override;
	virtual void Exit() override;
};