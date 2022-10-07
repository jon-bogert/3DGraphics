// Let's make 16 games in C++: TETRIS
// https://www.youtube.com/watch?v=zH_omFPqMO4

#include <XEngine.h>

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
};

Point a[4], b[4];

int figures[7][4] =
{
	// [0][1]               [ ][ ]
	// [2][3] ------------> [ ][#]
	// [4][5]	T=3,5,4,7   [#][#]
	// [6][7]	            [ ][#]

	1, 3, 5, 7, // I
	2, 4, 5, 7, // Z
	3, 5, 4, 6, // S
	3, 5, 4, 7, // T
	2, 3, 5, 7, // L
	3, 5, 7, 6, // J
	2, 3, 4, 5, // O
};

X::TextureId tiles;
X::TextureId background;
X::TextureId frame;
int dx = 0;
int colorNum = 1;
bool rotate = false;
float timer = 0.0f;
float delay = 0.3f;

bool Check()
{
	for (int i = 0; i < 4; ++i)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
			return false;
		else if (field[a[i].y][a[i].x] != 0)
			return false;
	}
	return true;
}

void GameInit()
{
	tiles = X::LoadTexture("tiles.png");
	background = X::LoadTexture("background.png");
	frame = X::LoadTexture("frame.png");

	timer = 100.0f;
	a[0].x = 100;
	colorNum = 0;
}

bool GameLoop(float deltaTime)
{
	timer += deltaTime;

	if (X::IsKeyPressed(X::Keys::UP))
		rotate = true;
	if (X::IsKeyPressed(X::Keys::LEFT))
		dx = -1;
	if (X::IsKeyPressed(X::Keys::RIGHT))
		dx = 1;
	if (X::IsKeyDown(X::Keys::DOWN))
		delay = 0.05f;

	// <- Move ->
	for (int i = 0; i < 4; ++i)
	{
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!Check())
	{
		for (int i = 0; i < 4; ++i)
			a[i] = b[i];
	}

	// Rotate
	if (rotate)
	{
		Point p = a[1]; // center of rotation
		for (int i = 0; i < 4; ++i)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; ++i)
				a[i] = b[i];
		}
	}

	// Tick
	if (timer > delay)
	{
		for (int i = 0; i < 4; ++i)
		{
			b[i] = a[i];
			a[i].y += 1;
		}
		if (!Check())
		{
			for (int i = 0; i < 4; ++i)
				field[b[i].y][b[i].x] = colorNum;
			colorNum = 1 + X::Random(0, 6);
			int n = X::Random(0, 6);
			for (int i = 0; i < 4; ++i)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		timer = 0.0f;
	}

	// Check lines
	int k = M - 1;
	for (int i = M - 1; i > 0; --i)
	{
		int count = 0;
		for (int j = 0; j < N; ++j)
		{
			if (field[i][j] != 0)
				count++;
			field[k][j] = field[i][j];
		}
		if (count < N)
			--k;
	}

	dx = 0;
	rotate = false;
	delay = 0.3f;

	// Draw
	X::DrawSprite(background, X::Math::Vector2::Zero(), X::Pivot::TopLeft);
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			int color = field[i][j];
			if (color == 0)
				continue;
			float x = j * 18.0f + 28.0f;
			float y = i * 18.0f + 31.0f;
			X::DrawSprite(tiles, { color * 18.0f, 0.0f, (color + 1 ) * 18.0f, 18.0f }, { x, y }, X::Pivot::TopLeft);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		float x = a[i].x * 18.0f + 28.0f;
		float y = a[i].y * 18.0f + 31.0f;
		X::DrawSprite(tiles, { colorNum * 18.0f, 0.0f, (colorNum + 1) * 18.0f, 18.0f }, { x, y }, X::Pivot::TopLeft);
	}
	X::DrawSprite(frame, X::Math::Vector2::Zero(), X::Pivot::TopLeft);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

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