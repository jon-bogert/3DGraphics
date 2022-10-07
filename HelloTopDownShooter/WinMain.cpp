#include <XEngine.h>

class Map
{
public:
	void AddWall(const X::Math::LineSegment& lineSegment)
	{
		mWalls.emplace_back(lineSegment);
	}
	void AddCorner(const X::Math::Vector2& corner)
	{
		mWalls.emplace_back(X::Math::LineSegment{ mWalls.back().to, corner });
	}

	void Draw() const
	{
		for (auto& wall : mWalls)
		{
			auto normal = X::Math::Normalize(wall.to - wall.from);
			auto midpoint = (wall.from + wall.to) * 0.5f;
			X::DrawScreenLine(wall.from, wall.to, X::Colors::Aqua);
			X::DrawScreenLine(midpoint, midpoint + X::Math::PerpendicularLH(normal) * 10.0f, X::Colors::Aqua);
		}
	}

	X::Math::Vector2 ResolveCollision(const X::Math::Circle& circle, const X::Math::Vector2& displacement) const
	{
		auto newDisplacment = displacement;

		for (int i = 0; i < 2; ++i)
		{
			X::Math::LineSegment closestWall;
			X::Math::Vector2 closestPoint;
			float closestDistanceSqr = std::numeric_limits<float>::max();

			X::Math::Circle displacedCircle{ circle.center + newDisplacment, circle.radius };
			for (auto& wall : mWalls)
			{
				X::Math::Vector2 point;
				if (X::Math::Intersect(displacedCircle, wall, &point))
				{
					float distanceSqr = X::Math::DistanceSqr(displacedCircle.center, point);
					if (distanceSqr < closestDistanceSqr)
					{
						// Keep closest wall/point
						closestWall = wall;
						closestPoint = point;
						closestDistanceSqr = distanceSqr;
					}
				}
			}

			if (closestDistanceSqr == std::numeric_limits<float>::max())
				return newDisplacment;

			float distance = X::Math::Sqrt(closestDistanceSqr);
			newDisplacment = newDisplacment + (displacedCircle.center - closestPoint) / distance * (circle.radius - distance);
		}

		return newDisplacment;
	}

private:
	std::vector<X::Math::LineSegment> mWalls;
};

class Player
{
public:
	void Update(float deltaTime, const Map& map)
	{
		if (X::IsKeyDown(X::Keys::W))
		{
			mPosition += map.ResolveCollision(GetBoundary(), mHeading * mMoveSpeed * deltaTime);
		}
		if (X::IsKeyDown(X::Keys::S))
		{
			mPosition += map.ResolveCollision(GetBoundary(), mHeading * -mMoveSpeed * deltaTime);
		}
		if (X::IsKeyDown(X::Keys::D))
		{
			mHeading = X::Math::Rotate(mHeading, mTurnSpeed * deltaTime);
		}
		if (X::IsKeyDown(X::Keys::A))
		{
			mHeading = X::Math::Rotate(mHeading, -mTurnSpeed * deltaTime);
		}
	}

	void Draw()
	{
		auto side = X::Math::PerpendicularLH(mHeading);
		auto boundary = GetBoundary();
		auto a = mPosition + (mHeading * boundary.radius);
		auto b = mPosition - (mHeading * boundary.radius * 0.5f) + (side * boundary.radius * 0.5f);
		auto c = mPosition - (mHeading * boundary.radius * 0.5f) - (side * boundary.radius * 0.5f);
		X::DrawScreenLine(a, b, X::Colors::LightBlue);
		X::DrawScreenLine(a, c, X::Colors::LightBlue);
		X::DrawScreenLine(b, c, X::Colors::LightBlue);
		X::DrawScreenCircle(boundary.center, boundary.radius, X::Colors::Green);
	}

	X::Math::Circle GetBoundary() const { return X::Math::Circle{ mPosition, 20.0f }; }

private:
	X::Math::Vector2 mPosition{ 150.0f, 150.0f };
	X::Math::Vector2 mHeading{ 1.0f, 0.0f };
	float mMoveSpeed{ 200.0f };
	float mTurnSpeed{ X::Math::kPi };
};

Map map;
Player player;

void GameInit()
{
	map.AddWall({ { 100.0f, 100.0f }, { 500.0f, 100.0f } });
	map.AddCorner({ 600.0f, 200.0f });
	map.AddCorner({ 1100.0f, 200.0f });
	map.AddCorner({ 1100.0f, 650.0f });
	map.AddCorner({ 200.0f, 650.0f });
	map.AddCorner({ 200.0f, 500.0f });
	map.AddCorner({ 100.0f, 400.0f });
	map.AddCorner({ 100.0f, 100.0f });
	map.AddWall({ { 400.0f, 300.0f }, { 400.0f, 480.0f } });
	map.AddCorner({ 450.0f, 480.0f });
	map.AddCorner({ 600.0f, 330.0f });
	map.AddCorner({ 600.0f, 300.0f });
	map.AddCorner({ 400.0f, 300.0f });
	map.AddWall({ { 700.0f, 300.0f }, { 700.0f, 330.0f } });
	map.AddCorner({ 550.0f, 480.0f });
	map.AddCorner({ 550.0f, 550.0f });
	map.AddCorner({ 900.0f, 550.0f });
	map.AddCorner({ 900.0f, 450.0f });
	map.AddCorner({ 850.0f, 400.0f });
	map.AddCorner({ 850.0f, 300.0f });
	map.AddCorner({ 700.0f, 300.0f });
	map.AddWall({ { 200.0f, 200.0f }, { 200.0f, 350.0f } });
	map.AddCorner({ 280.0f, 350.0f });
	map.AddCorner({ 280.0f, 200.0f });
	map.AddCorner({ 200.0f, 200.0f });
}

void GameCleanup()
{
	X::ClearAllSounds();
}

bool GameLoop(float deltaTime)
{
	player.Update(deltaTime, map);

	map.Draw();
	player.Draw();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}