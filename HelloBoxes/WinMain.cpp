#include <XEngine.h>

std::vector<X::Math::Rect> cells;

void Randomize()
{
	float w = X::GetScreenWidth() * 0.5f;
	float h = X::GetScreenHeight() * 0.5f;
	float size = 30.0f;
	for (int i = 0; i < 50; ++i)
	{
		float minX = X::RandomFloat(-size + w, 0.0f + w);
		float maxX = X::RandomFloat(0.0f + w, size + w);
		float minY = X::RandomFloat(-size + h, 0.0f + h);
		float maxY = X::RandomFloat(0.0f + h, size + h);
		cells.emplace_back(minX, minY, maxX, maxY);
	}
}

void Clear()
{
	cells.clear();
}

void ResolveOverlaps()
{
	bool overlap = false;
	for (size_t i = 0; i < cells.size(); ++i)
	{
		for (size_t j = 0; j < cells.size(); ++j)
		{
			if (i == j)
				continue;

			auto& a = cells[i];
			auto& b = cells[j];

			if (X::Math::Intersect(a, b))
			{
				if (a.right > b.left)
				{
					if (a.left < b.left)
					{
						float diff = a.right - b.left;
						a.left -= diff * 0.5f - 1.0f;
						a.right -= diff * 0.5f - 1.0f;
						b.left += diff * 0.5f;
						b.right += diff * 0.5f;
					}
					else
					{
						float diff = b.right - a.left;
						a.left += diff * 0.5f + 1.0f;
						a.right += diff * 0.5f + 1.0f;
						b.left -= diff * 0.5f;
						b.right -= diff * 0.5f;
					}
				}
			}

			if (X::Math::Intersect(a, b))
			{
				if (a.bottom > b.top)
				{
					if (a.top < b.top)
					{
						float diff = a.bottom - b.top;
						a.top -= diff * 0.5f - 1.0f;
						a.bottom -= diff * 0.5f - 1.0f;
						b.top += diff * 0.5f;
						b.bottom += diff * 0.5f;
					}
					else
					{
						float diff = b.bottom - a.top;
						a.top += diff * 0.5f + 1.0f;
						a.bottom += diff * 0.5f + 1.0f;
						b.top -= diff * 0.5f;
						b.bottom -= diff * 0.5f;
					}
				}
			}
		}
	}
}

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		Randomize();
	}
	if (X::IsKeyPressed(X::Keys::BACKSPACE))
	{
		Clear();
	}

	ResolveOverlaps();

	for (auto& cell : cells)
	{
		X::DrawScreenRect(cell, X::Colors::Cyan);
	}
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	Randomize();

	X::Run(GameLoop);

	X::Stop();
	return 0;
}