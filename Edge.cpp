#include "Edge.h"

Edge::Edge()
{
	this->firstPoint = 0;
	this->secondPoint = 0;
	this->weight = 0;
}

Edge::Edge(const Edge& edge)
{
	this->firstPoint = edge.firstPoint;
	this->secondPoint = edge.secondPoint;
	this->weight = edge.weight;
}

Edge::Edge(int firstPoint, int secondPoint, double weight) {
	this->firstPoint = firstPoint;
	this->secondPoint = secondPoint;
	this->weight = weight;
}

int Edge::GetFirstPoint()
{
	return firstPoint;
}

int Edge::GetSecondPoint()
{
	return secondPoint;
}

double Edge::GetWeight()
{
	return weight;
}

void Edge::operator=(const Edge& edge)
{
	this->firstPoint = edge.firstPoint;
	this->secondPoint = edge.secondPoint;
	this->weight = edge.weight;
}