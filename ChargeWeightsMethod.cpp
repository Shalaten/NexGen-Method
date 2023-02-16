#include "ChargeWeightsMethod.h"

ChargeWeightsMethod::ChargeWeightsMethod(int pointsAmount)
{
	//srand(time(NULL));
	this->pointsAmount = pointsAmount;
	minWeight = 10000000.0;
	GenerateEdgeMatrix();
	PrintEdgeMatrix();
	FindWay();
	BroodForceMethod();
}

void ChargeWeightsMethod::FindWay()
{
	// Создание списка рёбер 
	std::vector<Edge> minWay;
	minWay.reserve(pointsAmount);
	// Поиск максимальных весов всех рёбер
	std::vector<double> maxVerticesWeights(pointsAmount, 0);
	for (int i = 0; i < pointsAmount; ++i) {
		for (auto edge : edges[i]) {
			if (edge.GetWeight() > maxVerticesWeights[i]) {
				maxVerticesWeights[i] = edge.GetWeight();
			}
		}
	}
	// Создание матрицы состояний рёбер
	std::vector<std::vector<ChargeWithState>> edgesStates;
	edgesStates.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		std::vector<ChargeWithState> insideVector;
		insideVector.resize(pointsAmount, ChargeWithState());
		edgesStates.push_back(insideVector);
	}
	// Заполнение матрицы состояний рёбер
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			if (i != j) {
				double newCharge = maxVerticesWeights[i] * 2 - edges[i][j].GetWeight();
				edgesStates[i][j].SetCharge(newCharge);
			}
			if (i == j) {
				edgesStates[i][j].SetState(true);
			}
		}
	}
	// Сумирование зарядов обратных рёбер
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = i; j < pointsAmount; ++j) {
			double oneCharge = edgesStates[i][j].GetCharge();
			double twoCharge = edgesStates[j][i].GetCharge();
			
			edgesStates[i][j].SetCharge(edgesStates[i][j].GetCharge() + twoCharge);
			edgesStates[j][i].SetCharge(edgesStates[j][i].GetCharge() + oneCharge);
		}
	}
	// Вывод матрицы зарядов
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			std::cout << edgesStates[i][j].GetCharge() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	// Конечные вершины пути
	int firstPoint = 0;
	int secondPoint = 0;
	double maxCharge = 0.0;
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = i; j < pointsAmount; ++j) {
			if (edgesStates[i][j].GetCharge() > maxCharge) {
				maxCharge = edgesStates[i][j].GetCharge();
				firstPoint = i;
				secondPoint = j;
			}
		}
	}
	std::vector<int> usedVertices(pointsAmount, 0);
	usedVertices[firstPoint]++;
	usedVertices[secondPoint]++;
	edgesStates[firstPoint][secondPoint].SetState(true);
	edgesStates[secondPoint][firstPoint].SetState(true);
	minWay.push_back(Edge(firstPoint, secondPoint, edges[firstPoint][secondPoint].GetWeight()));
	//////////////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i < pointsAmount; ++i) {
		double maxCharge = 0.0;
		int maxVerticeOne = 0;
		int maxVerticeTwo = 0;
		for (int one = 0; one < pointsAmount; ++one) {
			for (int two = 0; two < pointsAmount; ++two) {
				if (usedVertices[one] < 2 && usedVertices[two] < 2 &&  !edgesStates[one][two].GetState()) {
					if (edgesStates[one][two].GetCharge() > maxCharge) {
						maxCharge = edgesStates[one][two].GetCharge();
						maxVerticeOne = one;
						maxVerticeTwo = two;
					}
				}
			}
		}
		usedVertices[maxVerticeOne]++;
		usedVertices[maxVerticeTwo]++;
		edgesStates[maxVerticeOne][maxVerticeTwo].SetState(true);
		edgesStates[maxVerticeTwo][maxVerticeOne].SetState(true);
		minWay.push_back(Edge(maxVerticeOne, maxVerticeTwo, edges[maxVerticeOne][maxVerticeTwo].GetWeight()));
	}
	double sum = 0.0;
	for (auto edge : minWay) {
		std::cout << edge.GetFirstPoint() << " - " << edge.GetSecondPoint() << "\t";
		sum += edge.GetWeight();
	}
	std::cout << "Weight - " << sum;
}

void ChargeWeightsMethod::BroodForceMethod()
{
	for (int i = 0; i < pointsAmount; ++i) {
		int counter = 0;
		double sumWeight = 0;
		std::vector<int> way;
		way.push_back(i);
		std::vector<bool> checkedPoints;
		checkedPoints.resize(pointsAmount);
		checkedPoints[i] = true;
		BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
	}
}

int ChargeWeightsMethod::GetPointsAmounts()
{
	return pointsAmount;
}

std::vector<std::vector<Edge>> ChargeWeightsMethod::GetEdges()
{
	return edges;
}

void ChargeWeightsMethod::PrintEdgeMatrix()
{
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			std::cout << edges[i][j].GetWeight() << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void ChargeWeightsMethod::PrintBroodForceMethodWay()
{
	for (auto point : shortWay) {
		std::cout << point << "\t";
	}
	std::cout << "Weight - " << minWeight << std::endl;
}

void ChargeWeightsMethod::GenerateEdgeMatrix()
{
	edges.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		std::vector<Edge> insideEdgeVector;
		insideEdgeVector.reserve(pointsAmount);
		for (int j = 0; j < pointsAmount; j++) {
			if (!IsEquals(i, j)) {
				double weight = rand() / 10.0;
				if (!IsMore(i, j)) {
					insideEdgeVector.push_back(Edge(i, j, weight));
				}
				else {
					insideEdgeVector.push_back(Edge(j, i, edges[j][i].GetWeight()));
				}
			}
			else
			{
				insideEdgeVector.push_back(Edge(i, j, 0.0));
			}
		}
		edges.push_back(insideEdgeVector);
	}
}

void ChargeWeightsMethod::BroodForceMethodRecursion(std::vector<int> wayM, int counterM, double sumWeightM, int lastPoint, std::vector<bool> checkedPointsM)
{
	for (int i = 0; i < pointsAmount; i++) {
		int counter = counterM + 1;
		double sumWeight = sumWeightM;
		std::vector<int> way = wayM;
		std::vector<bool> checkedPoints = checkedPointsM;
		if (edges[lastPoint][i].GetWeight() != 0) {
			if (counter < pointsAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[lastPoint][i].GetWeight();
				way.push_back(i);
				checkedPoints[i] = true;
				BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
			}
			else if (counter == pointsAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[i][lastPoint].GetWeight();
				sumWeight += edges[way[0]][i].GetWeight();
				way.push_back(i);
				if (sumWeight < minWeight) {
					shortWay = way;
					minWeight = sumWeight;
				}
			}
		}
	}
}

bool ChargeWeightsMethod::IsEquals(int oneNumber, int twoNumber)
{
	return oneNumber == twoNumber ? true : false;
}

bool ChargeWeightsMethod::IsMore(int oneNumber, int twoNumber)
{
	return oneNumber > twoNumber ? true : false;
}

ChargeWeightsMethod::ChargeWithState::ChargeWithState()
{
	this->charge = 0;
	this->state = false;
}

ChargeWeightsMethod::ChargeWithState::ChargeWithState(double charge)
{
	this->charge = charge;
	state = false;
}

double ChargeWeightsMethod::ChargeWithState::GetCharge()
{
	return charge;
}

bool ChargeWeightsMethod::ChargeWithState::GetState()
{
	return state;
}

void ChargeWeightsMethod::ChargeWithState::SetState(bool state)
{
	this->state = state;
}

void ChargeWeightsMethod::ChargeWithState::SetCharge(double charge)
{
	this->charge = charge;
}
