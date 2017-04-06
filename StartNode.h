#pragma once
#include "HudNode.h"
class StartNode :
	public HudNode
{
public:
	StartNode(glm::vec2 pos, glm::vec2 size, int id);
	virtual ~StartNode();

	void onRun();
};

