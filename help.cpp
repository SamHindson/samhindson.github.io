#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <fstream>

class Node {
public:
	Node();
	Node(double, double);
	double x;
	double y;
	double distance(Node* other) {
		return sqrt(pow(other->x - x, 2) + pow(other->y - y, 2));
	}
};

Node::Node() {
	this->x = 0;
	this->y = 0;
}

Node::Node(double x, double y) {
	this->x = x;
	this->y = y;
}

int nodeCount = 3;
int calculations = 0;
double averageLength = 0;
double target;
std::vector<Node> nodes;

void reset() {
	nodes.clear();
	target = 1000 / (nodeCount - 1);
	nodes.push_back(Node(0, 500));
	for(int j = 0; j < nodeCount - 2; j++) {
		double k = rand() % 1000;
		double l = rand() % 1000;
		nodes.push_back(Node(k, l));
	}
	nodes.push_back(Node(1000, 500));
}

int main() {
	std::ofstream foil("results.txt");
	reset();

	int currentIndex = 1;
	//	How far we want to run the calculation
	for(int u = 0; u < 500; u++) {
		double mean = 0;
		target = 1000 / (nodeCount - 1);
		int calcz = 10;
		//	How many times we want to do the same simulation (accuracy++!)
		for(int g = 0; g < calcz; g++) {
			bool going = true;
			while(going) {
				calculations++;
				//	Sets the node's position to the mean of its neighbours
				nodes.at(currentIndex).x = (nodes.at(currentIndex - 1).x + nodes.at(currentIndex + 1).x) / 2;
				nodes.at(currentIndex).y = (nodes.at(currentIndex - 1).y + nodes.at(currentIndex + 1).y) / 2;
				//	Allows the next run to move onto the next node
				currentIndex++;
				//	Resets if we're in bat country
				if(currentIndex > nodes.size() - 2) {
					currentIndex = 1;
				}
				//Determines the average length between the nodes
				averageLength = 0;
				for(int s = 0; s < nodes.size() - 1; s++) {
					averageLength += nodes.at(s).distance(&nodes.at(s+1));
				}
				averageLength /= (nodeCount - 1);
				//	If we're close enough move on
				if(abs(averageLength - target) < 1) {
					mean += calculations;
					calculations = 0;
					going = false;
				}
			}
			reset();
		}
		mean /= calcz;
		std::cout<<"Finished "<<u<<std::endl;
		foil << u << "\t\t" << mean << "\n";
		mean = 0;
		nodeCount++;
		reset();
	}

	foil.close();

	return 0;
}