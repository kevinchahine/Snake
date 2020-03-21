#pragma once

#include "ControllerBase.h"
#include "SnakeEngine.h"

class AIController : public ControllerBase
{
public:
	AIController(SnakeEngine& engine);

	virtual char getInput() override;

private:
	SnakeEngine& engine;

};

