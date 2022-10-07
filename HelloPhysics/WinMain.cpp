#include <XEngine.h>

// https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331

struct Object
{
	X::Math::Rect aabb;
	X::Math::Circle circle;
	X::Math::Vector2 position;
	X::Math::Vector2 velocity;
	float invMass;
	float restitution;
};

struct Manifold
{
	Object* A;
	Object* B;
	float penetration;
	X::Math::Vector2 normal;
};



void ResolveCollision(const Manifold& manifold)
{
	// Calculate relative velocity
	X::Math::Vector2 rv = manifold.B->velocity - manifold.A->velocity;

	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = X::Math::Dot(rv, manifold.normal);

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0)
		return;

	// Calculate restitution
	float e = X::Math::Min(manifold.A->restitution, manifold.B->restitution);

	// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= manifold.A->invMass + manifold.B->invMass;

	// Apply impulse
	X::Math::Vector2 impulse = manifold.normal * j;
	manifold.A->velocity -= impulse * manifold.A->invMass;
	manifold.B->velocity += impulse * manifold.B->invMass;
}

void PositionalCorrection(const Manifold& manifold)
{
	const float percent = 0.2f; // usually 20% to 80%
	const float slop = 0.01f; // usually 0.01 to 0.1
	X::Math::Vector2 correction = manifold.normal * X::Math::Max(manifold.penetration - slop, 0.0f) / (manifold.A->invMass + manifold.B->invMass) * percent;
	manifold.A->position -= correction * manifold.A->invMass;
	manifold.B->position += correction * manifold.B->invMass;
}

std::vector<Object> objects;

void GameInit()
{
	for (int i = 0; i < 10; ++i)
	{
		float size = X::RandomFloat(3.0f, 8.0f);
		Object object;
		object.aabb.left = X::RandomFloat(100.0f, 1180.0f);
		object.aabb.top = X::RandomFloat(100.0f, 200.0f);
		object.aabb.right = object.aabb.left + size * 10.0f;
		object.aabb.bottom = object.aabb.top + size * 10.0f;
		object.velocity = X::RandomUnitCircle() * 100.0f;
		object.invMass = 1.0f / size;
		object.restitution = 1.0f;
		objects.push_back(object);
	}
}

void GameCleanup()
{
}

bool GameLoop(float deltaTime)
{
	for (auto& obj : objects)
	{
		obj.velocity += X::Math::Vector2{ 0.0f, 100.0f } * deltaTime;
		obj.aabb.min += obj.velocity * deltaTime;
		obj.aabb.max += obj.velocity * deltaTime;
	}
	for (auto& obj : objects)
	{
		X::DrawScreenRect(obj.aabb, X::Colors::Chartreuse);
	}
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