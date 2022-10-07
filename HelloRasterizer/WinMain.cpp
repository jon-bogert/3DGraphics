#include <XEngine.h>

struct Vec3
{
	float x, y, z;
};

struct Tri
{
	Vec3 pts[3];
};

struct Mesh
{
	std::vector<Tri> tris;
};

struct Mat4x4
{
	float m[4][4] = { 0 };
};

Vec3 operator-(Vec3 v)
{
	return { -v.x, -v.y, -v.z };
}

Vec3 operator+(Vec3 a, Vec3 b)
{
	return
	{
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
	};
}

Vec3 operator-(Vec3 a, Vec3 b)
{
	return
	{
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
	};
}

Vec3 operator*(Vec3 v, float scale)
{
	return
	{
		v.x * scale,
		v.y * scale,
		v.z * scale
	};
}

float Length(Vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 Normalize(Vec3 v)
{
	float length = Length(v);
	return
	{
		v.x / length,
		v.y / length,
		v.z / length,
	};
}

float Dot(Vec3 a, Vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Cross(Vec3 a, Vec3 b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

Vec3 operator*(Vec3 v, Mat4x4 m)
{
	float x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.f * m.m[3][0];
	float y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.f * m.m[3][1];
	float z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.f * m.m[3][3];

	if (w != 0.0f)
	{
		x /= w;
		y /= w;
		z /= w;
	}

	return { x, y, z };
}

Mat4x4 operator*(Mat4x4 a, Mat4x4 b)
{
	Mat4x4 m;
	m.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0];
	m.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1];
	m.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2];
	m.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3];

	m.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0];
	m.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1];
	m.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2];
	m.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3];

	m.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0];
	m.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1];
	m.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2];
	m.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3];

	m.m[3][0] = a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0];
	m.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1];
	m.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2];
	m.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3];
	return m;
}

void DrawTest()
{
	const uint32_t width = X::GetScreenWidth();
	const uint32_t height = X::GetScreenHeight();

	for (uint32_t y = 0; y < height; y += 10)
	{
		for (uint32_t x = 0; x < width; x += 10)
		{
			int posX = (int)x;
			int posY = (int)y;
			X::Color color{ (float)posX / width, 0.5f, 1.0f - (float)posY / height, 1.0f };
			X::DrawPixel(posX + 0, posY + 0, color);
			X::DrawPixel(posX + 1, posY + 0, color);
			X::DrawPixel(posX + 0, posY + 1, color);
			X::DrawPixel(posX + 1, posY + 1, color);
		}
	}
}

void DrawLine(Vec3 a, Vec3 b, X::Color color)
{
	int x1 = static_cast<int>(a.x);
	int y1 = static_cast<int>(a.y);
	int x2 = static_cast<int>(b.x);
	int y2 = static_cast<int>(b.y);

	int dx = x2 - x1;
	int dy = y2 - y1;
	int dx1 = abs(dx);
	int dy1 = abs(dy);
	int px = 2 * dy1 - dx1;
	int py = 2 * dx1 - dy1;

	int x, y, xe, ye;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1; xe = x2;
		}
		else
		{
			x = x2; y = y2; xe = x1;
		}

		X::DrawPixel(x, y, color);

		for (int i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y = y + 1;
				else
					y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			X::DrawPixel(x, y, color);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1; y = y1; ye = y2;
		}
		else
		{
			x = x2; y = y2; ye = y1;
		}

		X::DrawPixel(x, y, color);

		for (int i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					x = x + 1;
				else
					x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			X::DrawPixel(x, y, color);
		}
	}
}

void DrawTriangle(Tri t, X::Color color)
{
	DrawLine(t.pts[0], t.pts[1], color);
	DrawLine(t.pts[1], t.pts[2], color);
	DrawLine(t.pts[2], t.pts[0], color);
}

Mesh meshCube;

void GameInit()
{
	meshCube.tris =
	{
		// Negative X
		{ -1.0f, -1.0f, +1.0f,    -1.0f, +1.0f, +1.0f,    -1.0f, +1.0f, -1.0f },
		{ -1.0f, -1.0f, +1.0f,    -1.0f, +1.0f, -1.0f,    -1.0f, -1.0f, -1.0f },

		// Positive X
		{ +1.0f, -1.0f, -1.0f,    +1.0f, +1.0f, -1.0f,    +1.0f, +1.0f, +1.0f },
		{ +1.0f, -1.0f, -1.0f,    +1.0f, +1.0f, +1.0f,    +1.0f, -1.0f, +1.0f },

		// Negative Y
		{ -1.0f, -1.0f, +1.0f,    -1.0f, -1.0f, -1.0f,    +1.0f, -1.0f, -1.0f },
		{ -1.0f, -1.0f, +1.0f,    +1.0f, -1.0f, -1.0f,    +1.0f, -1.0f, +1.0f },

		// Positive Y
		{ -1.0f, +1.0f, -1.0f,    -1.0f, +1.0f, +1.0f,    +1.0f, +1.0f, +1.0f },
		{ -1.0f, +1.0f, -1.0f,    +1.0f, +1.0f, +1.0f,    +1.0f, +1.0f, -1.0f },

		// Negative Z
		{ -1.0f, -1.0f, -1.0f,    -1.0f, +1.0f, -1.0f,    +1.0f, +1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f,    +1.0f, +1.0f, -1.0f,    +1.0f, -1.0f, -1.0f },

		// Positive Z
		{ +1.0f, -1.0f, +1.0f,    +1.0f, +1.0f, +1.0f,    -1.0f, +1.0f, +1.0f },
		{ +1.0f, -1.0f, +1.0f,    -1.0f, +1.0f, +1.0f,    -1.0f, -1.0f, +1.0f },
	};
}

bool GameLoop(float deltaTime)
{
	float scale = 1.0f;
	static float angleX = 0.0f;
	static float angleY = 0.0f;
	static float angleZ = 0.0f;
	angleX += deltaTime;
	angleY += deltaTime;
	angleZ += deltaTime;

	Mat4x4 matScale;
	matScale.m[0][0] = scale;
	matScale.m[1][1] = scale;
	matScale.m[2][2] = scale;
	matScale.m[3][3] = 1.0f;

	Mat4x4 matRotX;
	matRotX.m[0][0] = 1.0f;
	matRotX.m[1][1] = cosf(angleX);
	matRotX.m[1][2] = sinf(angleX);
	matRotX.m[2][1] = -sinf(angleX);
	matRotX.m[2][2] = cosf(angleX);
	matRotX.m[3][3] = 1.0f;

	Mat4x4 matRotY;
	matRotY.m[0][0] = cosf(angleY);
	matRotY.m[0][2] = -sinf(angleY);
	matRotY.m[1][1] = 1.0f;
	matRotY.m[2][0] = sinf(angleY);
	matRotY.m[2][2] = cosf(angleY);
	matRotY.m[3][3] = 1.0f;

	Mat4x4 matRotZ;
	matRotZ.m[0][0] = cosf(angleZ);
	matRotZ.m[0][1] = sinf(angleZ);
	matRotZ.m[1][0] = -sinf(angleZ);
	matRotZ.m[1][1] = cosf(angleZ);
	matRotZ.m[2][2] = 1.0f;
	matRotZ.m[3][3] = 1.0f;

	Mat4x4 matTrans;
	matTrans.m[0][0] = 1.0f;
	matTrans.m[1][1] = 1.0f;
	matTrans.m[2][2] = 1.0f;
	matTrans.m[3][0] = 0.0f;
	matTrans.m[3][1] = 0.0f;
	matTrans.m[3][2] = 5.0f;
	matTrans.m[3][3] = 1.0f;

	Vec3 cameraPosition{ 0.0f, 0.0f, 0.0f };
	Vec3 cameraDirection{ 0.0f, 0.0f, 1.0f };

	Vec3 lightDirection = Normalize({ 1.0f, -1.0f, 1.0f });

	float sw = static_cast<float>(X::GetScreenWidth());
	float sh = static_cast<float>(X::GetScreenHeight());

	float near = 0.1f;
	float far = 1000.0f;
	float fov = 90.0f;
	float aspect = sw / sh;
	float invFovW = 1.0f / tanf(fov * 0.5f * X::Math::kDegToRad);
	float invFovH = 1.0f / tanf(fov * 0.5f * X::Math::kDegToRad);

	Mat4x4 matProj;
	matProj.m[0][0] = invFovW / aspect;
	matProj.m[1][1] = invFovH;
	matProj.m[2][2] = far / (far - near);
	matProj.m[3][2] = -(far * near) / (far - near);
	matProj.m[2][3] = 1.0f;

	Mat4x4 matScreen;
	matScreen.m[0][0] = 0.5f * sw;
	matScreen.m[1][1] = -0.5f * sh;
	matScreen.m[2][2] = 1.0f;
	matScreen.m[3][0] = 0.5f * sw;
	matScreen.m[3][1] = 0.5f * sh;
	matScreen.m[3][3] = 1.0f;

	Mat4x4 matWorld = matScale * matRotX * matRotY * matRotZ * matTrans;
	Mat4x4 matFinal = matProj * matScreen;

	for (auto tri : meshCube.tris)
	{
		Tri triWorld;
		triWorld.pts[0] = tri.pts[0] * matWorld;
		triWorld.pts[1] = tri.pts[1] * matWorld;
		triWorld.pts[2] = tri.pts[2] * matWorld;

		Vec3 normal = Normalize(Cross(triWorld.pts[1] - triWorld.pts[0], triWorld.pts[2] - triWorld.pts[0]));

		// Does not work because this does not take view direction into account
		//if (normal.z >= 0.0f)
		//	continue;

		Vec3 dirToView = Normalize(cameraPosition - triWorld.pts[0]);
		if (Dot(dirToView, normal) <= 0.0f)
			continue;

		Vec3 dirToLight = -lightDirection;
		float diffuse = Dot(dirToLight, normal);

		// TODO: Need to implement FillTriangle
		// HACK: Shrink the face a bit
		Vec3 center = triWorld.pts[0] + triWorld.pts[1] + triWorld.pts[2];
		Vec3 d0 = center - triWorld.pts[0];
		Vec3 d1 = center - triWorld.pts[1];
		Vec3 d2 = center - triWorld.pts[2];
		for (int i = 0; i < 20; ++i)
		{
			Tri triWorldShrinked;
			triWorldShrinked.pts[0] = triWorld.pts[0] + d0 * (0.05f * i);
			triWorldShrinked.pts[1] = triWorld.pts[1] + d1 * (0.05f * i);
			triWorldShrinked.pts[2] = triWorld.pts[2] + d2 * (0.05f * i);

			Tri triProjected;
			triProjected.pts[0] = triWorldShrinked.pts[0] * matFinal;
			triProjected.pts[1] = triWorldShrinked.pts[1] * matFinal;
			triProjected.pts[2] = triWorldShrinked.pts[2] * matFinal;

			DrawTriangle(triProjected, X::Colors::White * diffuse);
		}
	}

	//DrawTest();
	//
	//X::DrawScreenText("Peter", 10.0f, 10.0f, 200.0f, X::Colors::Cyan);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	X::Stop();
	return 0;
}