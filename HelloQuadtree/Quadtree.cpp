#include "Quadtree.h"

Quadtree::Quadtree(double minX, double minY, double maxX, double maxY, int capacity)
	: root_(nullptr)
	, nodePool_(nullptr)
	, nodeUsed_(0)
	, nodeCapacity_(capacity)
{
	// Initialize pool
	nodePool_ = new Quadtree::Node[nodeCapacity_];
	root_ = NewNode(minX, minY, maxX, maxY);
}

Quadtree::~Quadtree()
{
	delete[] nodePool_;
}

Quadtree::Node* Quadtree::NewNode(double minX, double minY, double maxX, double maxY)
{
	XASSERT(nodeUsed_ < nodeCapacity_, "No more nodes!");
	Node* node = &nodePool_[nodeUsed_++];
	node->minX = minX;
	node->minY = minY;
	node->maxX = maxX;
	node->maxY = maxY;
	node->topLeft = nullptr;
	node->topRight = nullptr;
	node->bottomLeft = nullptr;
	node->bottomRight = nullptr;
	node->body = nullptr;
	node->isLeaf = true;
	return node;
}

void Quadtree::Insert(Body* body)
{
	InsertRecursive(root_, body);
}

void Quadtree::Visit(Visitor& visitor)
{
	VisitRecursive(root_, visitor);
}

void Quadtree::Subdivide(Node* node)
{
	double centerX = (node->minX + node->maxX) * 0.5;
	double centerY = (node->minY + node->maxY) * 0.5;
	node->topLeft = NewNode(node->minX, node->minY, centerX, centerY);
	node->topRight = NewNode(centerX, node->minY, node->maxX, centerY);
	node->bottomLeft = NewNode(node->minX, centerY, centerX, node->maxY);
	node->bottomRight = NewNode(centerX, centerY, node->maxX, node->maxY);
	node->isLeaf = false;
}

bool Quadtree::InsertRecursive(Node* node, Body* body)
{
	// Check if body belongs to this region
	if (body->x() < node->minX ||
		body->x() > node->maxX ||
		body->y() < node->minY ||
		body->y() > node->maxY)
	{
		return false;
	}

	// Keep going until we hit a leaf node
	if (node->isLeaf)
	{
		// Check if this node has a body
		if (node->body == nullptr)
		{
			// Insert here and we are done
			node->body = body;
			return true;
		}
		else
		{
			// We have two bodies in the region, subdivide and reassign
			Subdivide(node);
			bool result = InsertRecursive(node, node->body);
			XASSERT(result, "Bad stuff");
			result = InsertRecursive(node, body);
			XASSERT(result, "Bad stuff");
			node->body = nullptr;
			return true;
		}
	}
	else
	{
		// Try child nodes
		if (InsertRecursive(node->topLeft, body)) return true;
		if (InsertRecursive(node->topRight, body)) return true;
		if (InsertRecursive(node->bottomLeft, body)) return true;
		if (InsertRecursive(node->bottomRight, body)) return true;
	}

	XASSERT(false, "Should never reach here");
	return false;
}

void Quadtree::VisitRecursive(Node* node, Visitor& visitor)
{
	if (node)
	{
		visitor(node);

		VisitRecursive(node->topLeft, visitor);
		VisitRecursive(node->topRight, visitor);
		VisitRecursive(node->bottomLeft, visitor);
		VisitRecursive(node->bottomRight, visitor);
	}
}