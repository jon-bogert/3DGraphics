#include "Quadtree.h"
#include <XEngine.h>
#include <algorithm>
#include <fstream>
#include <iostream>

Body* force_bodies = new Body[17];
int nbodies = 0;

Quadtree* quadtree = nullptr;

void LoadData(const char* filename)
{
	std::ifstream is;
	is.open(filename);

	double t;

	is >> nbodies;
	force_bodies = new Body[nbodies ? nbodies : 1];

	is >> t;

	for (int i = 0; i < nbodies; i++)
	{
		double vx, vy, m;
		is >> force_bodies[i].x_ >> force_bodies[i].y_ >> vx >> vy >> m;
	}
}

void RandomData()
{
	nbodies = 500;
	force_bodies = new Body[nbodies ? nbodies : 1];

	for (int i = 0; i < nbodies; i++)
	{
		force_bodies[i].x_ = X::RandomFloat(-3.0f, 3.0f);
		force_bodies[i].y_ = X::RandomFloat(-3.0f, 3.0f);
	}
}

void CreateQuadtree()
{
	Body* bodyMinX = std::min_element(force_bodies, force_bodies + nbodies, [](const Body& a, const Body& b) { return a.x() < b.x(); });
	Body* bodyMinY = std::min_element(force_bodies, force_bodies + nbodies, [](const Body& a, const Body& b) { return a.y() < b.y(); });
	Body* bodyMaxX = std::max_element(force_bodies, force_bodies + nbodies, [](const Body& a, const Body& b) { return a.x() < b.x(); });
	Body* bodyMaxY = std::max_element(force_bodies, force_bodies + nbodies, [](const Body& a, const Body& b) { return a.y() < b.y(); });

	int maxNode = 1000000; // TODO: Compute this
	quadtree = new Quadtree(
		bodyMinX->x(),
		bodyMinY->y(),
		bodyMaxX->x(),
		bodyMaxY->y(),
		maxNode);

	for (int i = 0; i < nbodies; ++i)
	{
		quadtree->Insert(force_bodies + i);
	}
}

bool GameLoop(float deltaTime)
{
	struct NodeRenderer : public Quadtree::Visitor
	{
		virtual void operator()(Quadtree::Node* node)
		{
			const float offsetX = X::GetScreenWidth() * 0.5f;
			const float offsetY = X::GetScreenHeight() * 0.5f;
			const float scale = 100.0f;
			float minX = (float)node->minX * scale + offsetX;
			float minY = (float)node->minY * scale + offsetY;
			float maxX = (float)node->maxX * scale + offsetX;
			float maxY = (float)node->maxY * scale + offsetY;
			X::DrawScreenRect(minX, minY, maxX, maxY, X::Colors::Blue);

			if (node->body)
			{
				float bodyX = (float)node->body->x() * scale + offsetX;
				float bodyY = (float)node->body->y() * scale + offsetY;
				X::DrawScreenCircle(bodyX, bodyY, 2.0f, X::Colors::Green);
			}
		}
	};

	quadtree->Visit(NodeRenderer());

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//LoadData("./initial.us");
	RandomData();
	CreateQuadtree();

	X::Start("xconfig.json");
	X::Run(GameLoop);
	X::Stop();

	X::SafeDelete(quadtree);
	X::SafeDeleteArray(force_bodies);

	return 0;
}