#include "BobsMap.h"

const int BobsMap::map[MAP_HEIGHT][MAP_WIDTH] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
	8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
	1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
	1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

const int BobsMap::m_iMapHeight = MAP_HEIGHT;
const int BobsMap::m_iMapWidth = MAP_WIDTH;

const int BobsMap::m_iStartX = 14;
const int BobsMap::m_iStartY = 7;

const int BobsMap::m_iEndX = 0;
const int BobsMap::m_iEndY = 2;

BobsMap::BobsMap()
{
	ResetMemory();
}

double BobsMap::TestRoute(const std::vector<int>& vecPath, BobsMap& bobs)
{
	int posX = m_iStartX;
	int posY = m_iStartY;

	for (int dir = 0; dir < vecPath.size(); ++dir)
	{
		int NextDir = vecPath[dir];

		switch (vecPath[dir])
		{
		case 0: //North

			//check within bounds and that we can move
			if (((posY - 1) < 0) || (map[posY - 1][posX] == 1))
			{
				break;
			}

			else
			{
				posY -= 1;
			}

			break;

		case 1: //South

			//check within bounds and that we can move
			if (((posY + 1) >= m_iMapHeight) || (map[posY + 1][posX] == 1))
			{
				break;
			}

			else
			{
				posY += 1;
			}

			break;

		case 2: //East

			//check within bounds and that we can move
			if (((posX + 1) >= m_iMapWidth) || (map[posY][posX + 1] == 1))
			{
				break;
			}

			else
			{
				posX += 1;
			}

			break;

		case 3: //West

			//check within bounds and that we can move
			if (((posX - 1) < 0) || (map[posY][posX - 1] == 1))
			{
				break;
			}

			else
			{
				posX -= 1;
			}

			break;

		}//end switch

		//mark the route in the memory array
		bobs.memory[posY][posX] = vecPath[dir] + 1;

	}//next direction

	//now we know the finish point of Bobs journey, let's assign
	//a fitness score which is proportional to his distance from
	//the exit

	int	DiffX = abs(posX - m_iEndX);
	int DiffY = abs(posY - m_iEndY);

	//we add the one to ensure we never divide by zero. Therefore
	//a solution has been found when this return value = 1
	return 1 / (double)(DiffX + DiffY + 1);
}

void BobsMap::Render()
{
	const float border = 100.0f;
	const float BlockSizeX = 32.0f;
	const float BlockSizeY = 32.0f;

	for (int y = 0; y < m_iMapHeight; ++y)
	{
		for (int x = 0; x < m_iMapWidth; ++x)
		{
			float left = border + (BlockSizeX * x);
			float right = left + BlockSizeX;
			float top = border + (BlockSizeY * y);
			float bottom = top + BlockSizeY;

			if (map[y][x] == 1)
				X::DrawScreenRect({ left, top, right, bottom }, X::Colors::Gray);

			if ((map[y][x] == 5) || (map[y][x] == 8))
				X::DrawScreenRect({ left, top, right, bottom }, X::Colors::Red);
		}
	}
}

void BobsMap::MemoryRender()
{
	const float border = 100.0f;
	const float BlockSizeX = 32.0f;
	const float BlockSizeY = 32.0f;

	for (int y = 0; y < m_iMapHeight; ++y)
	{
		for (int x = 0; x < m_iMapWidth; ++x)
		{
			float left = border + (BlockSizeX * x);
			float right = left + BlockSizeX;
			float top = border + (BlockSizeY * y);
			float bottom = top + BlockSizeY;

			if (memory[y][x] > 0)
			{
				X::DrawScreenRect({ left, top, right, bottom }, X::Colors::Cyan);

				X::Math::Vector2 center = { (left + right) * 0.5f, (top + bottom) * 0.5f };
				X::Math::Vector2 dir;
				switch (memory[y][x] - 1)
				{
				case 0: // North
					dir.y = BlockSizeY * 0.5f;
					break;
				case 1: // South
					dir.y = BlockSizeY * -0.5f;
					break;
				case 2: // East
					dir.x = BlockSizeX * -0.5f;
					break;
				case 3: // West
					dir.x = BlockSizeX * 0.5f;
					break;
				}

				X::DrawScreenLine(center, center + dir, X::Colors::Cyan);
			}
		}
	}
}

void BobsMap::ResetMemory()
{
	for (int y = 0; y < m_iMapHeight; ++y)
	{
		for (int x = 0; x < m_iMapWidth; ++x)
		{
			memory[y][x] = 0;
		}
	}
}