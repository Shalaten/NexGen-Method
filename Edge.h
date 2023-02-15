#pragma once

class Edge {
public:
	Edge();
	Edge(const Edge& edge);
	Edge(int firstPoint, int secondPoint, double weight);
	int GetFirstPoint();
	int GetSecondPoint();
	double GetWeight();

	void operator = (const Edge& edge);
private:
	int firstPoint, secondPoint;
	double weight;
};