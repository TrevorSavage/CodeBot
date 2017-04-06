#pragma once
#include "HudNode.h"
#include <vector>

class Hud
{
public:
	Hud();
	~Hud();

	HudNode* getStartNode();
	void setMessage(std::string newVal);
	void setIsMessageShowing(bool newVal);
	void onMousePressed(int x, int y);
	void onMouseReleased(int x, int y);
	void onMouseDragged(int x, int y, glm::vec2 start);
	bool hasSelectedConnection();
	void updateLineConnection(int x, int y);
	void addNode(HudNode* newNode);
	void deleteNode(HudNode* deleteVal);
	void deleteNodeAt(glm::vec2 mousePos);
	void draw();
	int requestNodeId();

protected:

private:
	int width;
	int height;
	HudNode* start;
	HudNode* selectedOut;
	HudNode* selectedIn;
	HudNode* draggedNode;
	std::vector<HudNode*> nodes;
	glm::vec2 lineEndpoint;
	bool isMessageShowing;
	std::string message;
	int currentNodeId;
};

