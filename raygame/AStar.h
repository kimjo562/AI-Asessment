#include "raylib.h"
#include <vector>
#include <algorithm>
#include <iostream>
#pragma once

struct Node;

struct Edge {
	Node* target;
	float cost;
};

struct Node {
	Vector2 position;

	float gScore;
	float hScore;
	float fScore;
	Node* previous;

	std::vector<Edge> connections;
};

class AStar
{
public:
	AStar() {};
	~AStar() {}

	std::vector<Node*> aStar(Node* startNode, Node* endNode);
	void drawNode(Node* node, bool selected = false);
	void drawGraph(Node* node, std::vector<Node*>* drawnList);

private:

};