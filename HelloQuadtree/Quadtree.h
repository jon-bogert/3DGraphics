#ifndef	INCLUDED_QUADTREE_H
#define INCLUDED_QUADTREE_H

#include <XEngine.h>

struct Body
{
	double x_, y_;

	double x() const { return x_; }
	double y() const { return y_; }
};

class Quadtree
{
public:
	struct Node
	{
		double minX;
		double minY;
		double maxX;
		double maxY;
		Node* topLeft;
		Node* topRight;
		Node* bottomLeft;
		Node* bottomRight;
		Body* body;
		bool isLeaf;
	};

	struct Visitor
	{
		virtual void operator()(Node* node) = 0;
	};

	Quadtree(double minX, double minY, double maxX, double maxY, int capacity);
	~Quadtree();

	void Insert(Body* body);
	void Visit(Visitor& visitor);

private:
	Node* NewNode(double minX, double minY, double maxX, double maxY);
	void Subdivide(Node* node);
	bool InsertRecursive(Node* node, Body* body);
	void VisitRecursive(Node* node, Visitor& visitor);

private:
	Node* root_;
	Node* nodePool_;
	int nodeUsed_;
	int nodeCapacity_;
};

#endif // #ifndef INCLUDED_QUADTREE_H