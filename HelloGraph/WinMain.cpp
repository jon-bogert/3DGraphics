#include <XEngine.h>

struct Node
{
	X::Math::Vector2 position;
	X::Color color;
	std::vector<size_t> neighbors;
	bool active;
};

std::vector<Node> graph;

void InitRandom()
{
	const size_t numNodes = 15;
	const size_t maxNeighbors = 2;

	graph.clear();
	const X::Math::Vector2 center{
		X::GetScreenWidth() * 0.5f,
		X::GetScreenHeight() * 0.5f
	};
	graph.resize(numNodes);
	for (auto& node : graph)
		node.active = true;
	for (size_t i = 0; i < graph.size(); ++i)
	{
		auto& node = graph[i];
		node.position = X::Math::Vector2{
			X::RandomFloat(-200.0f, 200.0f),
			X::RandomFloat(-200.0f, 200.0f)
		} + center;
		node.color = {
			X::RandomFloat(0.5f, 1.0f),
			X::RandomFloat(0.5f, 1.0f),
			X::RandomFloat(0.5f, 1.0f),
			1.0f
		};

		int remaining = (int)X::Math::Min(maxNeighbors, graph.size() - i - 1);
		if (remaining > 0)
		{
			size_t count = (size_t)X::Random(1, remaining);
			node.neighbors.reserve(count);
			for (size_t n = 0; n < count; ++n)
			{
				size_t ni = i + (size_t)X::Random(1, remaining);
				while (std::find(node.neighbors.begin(), node.neighbors.end(), ni) != node.neighbors.end())
					ni = i + (size_t)X::Random(1, remaining);
				node.neighbors.push_back(ni);
			}
		}
	}
}

void InitCircular()
{
	const size_t numRings = 3;
	const size_t numSplits = 7;
	const float ringDist = 60.0f;

	graph.clear();

	size_t numNodes = 0;
	for (size_t i = 0; i < numRings; ++i)
	{
		numNodes += (size_t)pow(numSplits, i);
	}

	graph.resize(numNodes);
	for (auto& node : graph)
		node.active = false;

	const X::Math::Vector2 center{
		X::GetScreenWidth() * 0.5f,
		X::GetScreenHeight() * 0.5f
	};

	size_t n = 0;
	float offsetAngle = 0.0f;
	graph[0].active = true;
	for (size_t i = 0; i < numRings; ++i)
	{
		size_t tierCount = (size_t)pow(numSplits, i);
		float sectorAngle = X::Math::kTwoPi / (float)tierCount;

		for (size_t j = 0; j < tierCount; ++n, ++j)
		{
			auto& node = graph[n];
			if (!node.active)
				continue;

			float dist = ringDist * i;
			node.position = X::Math::Vector2{
				cos(j * sectorAngle - offsetAngle) * dist,
				sin(j * sectorAngle - offsetAngle) * dist,
			} + center;
			node.color = {
				X::RandomFloat(0.5f, 1.0f),
				X::RandomFloat(0.5f, 1.0f),
				X::RandomFloat(0.5f, 1.0f),
				1.0f
			};

			if (i + 1 < numRings)
			{
				std::array<size_t, numSplits> ni;
				for (size_t m = 0; m < numSplits; ++m)
				{
					ni[m] = (n * numSplits) + m + 1;
				};

				std::random_device rng;
				std::mt19937 urng(rng());
				std::shuffle(ni.begin(), ni.end(), urng);

				const size_t count = X::Random(1, numSplits);
				for (size_t m = 0; m < count; ++m)
				{
					node.neighbors.push_back(ni[m]);
					graph[ni[m]].active = true;
				}
			}
		}

		offsetAngle += sectorAngle / numSplits;
	}
}

void UpdateGraph(float deltaTime)
{
	if (!graph.empty())
	{
		graph[0].position = {
			X::GetScreenWidth() * 0.5f,
			X::GetScreenHeight() * 0.5f
		};
	}
	for (size_t i = 0; i < graph.size(); ++i)
	{
		auto& node = graph[i];
		if (!node.active)
			continue;

		for (size_t n = 0; n < graph.size(); ++n)
		{
			if (i == n)
				continue;

			auto& other = graph[n];
			if (std::find(node.neighbors.begin(), node.neighbors.end(), n) != node.neighbors.end())
			{
				X::Math::Vector2 delta = other.position - node.position;
				float dist = X::Math::Magnitude(delta);
				float diff = (dist - 100.0f) / dist;
				node.position += delta * diff * deltaTime;
				other.position -= delta * diff * deltaTime;
			}
			else
			{
				const float separation = 150.0f;
				auto neighborToNode = node.position - other.position;
				auto dist = X::Math::Magnitude(neighborToNode);
				auto force = X::Math::Max(0.0f, separation - dist);
				node.position += X::Math::Normalize(neighborToNode) * force * deltaTime;
			}
		}
	}
}

void DrawGraph()
{
	for (auto& node : graph)
	{
		if (!node.active)
			continue;

		X::DrawScreenCircle(node.position, 10.0f, node.color);

		for (auto& neighbor : node.neighbors)
		{
			X::DrawScreenLine(node.position, graph[neighbor].position, X::Colors::Cyan);
		}
	}
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ONE))
	{
		InitRandom();
	}
	if (X::IsKeyPressed(X::Keys::TWO))
	{
		InitCircular();
	}
	UpdateGraph(deltaTime);
	DrawGraph();
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	InitRandom();

	X::Run(GameLoop);
	X::Stop();
	return 0;
}