// Procedural Dungeon Generator
// Reference:
// https://www.reddit.com/r/gamedev/comments/1dlwc4/procedural_dungeon_generation_algorithm_explained/
// http://www.gamasutra.com/blogs/AAdonaac/20150903/252889/Procedural_Dungeon_Generation_Algorithm.php

#include <XEngine.h>

const int screenWidth = 1280;
const int screenHeight = 720;
const int numCells = 100;
const int maxInitialPosition = 20;
const int minHalfCellSize = 1;
const int maxHalfCellSize = 5;
const float spacing = 5.0f;

std::vector<X::Math::Rect> cells;

enum class State
{
	Start,
	GenerateCells,
	Done
};

State state = State::Start;

void OnStart(float deltaTime)
{
	cells.clear();
	state = State::GenerateCells;
}

void OnGenerateCells(float deltaTime)
{
	if (cells.size() >= numCells)
	{
		state = State::Done;
		return;
	}

	float x = X::Random(-maxInitialPosition, maxInitialPosition) * spacing + (screenWidth * 0.5f);
	float y = X::Random(-maxInitialPosition, maxInitialPosition) * spacing + (screenHeight * 0.5f);
	float w = X::Random(minHalfCellSize, maxHalfCellSize) * spacing;
	float h = X::Random(minHalfCellSize, maxHalfCellSize) * spacing;
	cells.emplace_back(x - w, y - h, x + w, y + h);
}

void OnDone(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		state = State::Start;
	}
}

bool GameLoop(float deltaTime)
{
	switch (state)
	{
	case State::Start:
		OnStart(deltaTime);
		break;
	case State::GenerateCells:
		OnGenerateCells(deltaTime);
		break;
	case State::Done:
		OnDone(deltaTime);
		break;
	}

	for (auto c : cells)
	{
		X::DrawScreenRect(c, X::Colors::Blue);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	X::Run(GameLoop);
	X::Stop();
	return 0;
}