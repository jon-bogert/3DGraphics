#pragma once

#include <XEngine.h>

#define WINDOW_WIDTH	450
#define WINDOW_HEIGHT	300

#define MAP_WIDTH		15
#define MAP_HEIGHT		10

#define CROSSOVER_RATE	0.7
#define MUTATION_RATE	0.001

#define POP_SIZE		140
#define CHROMO_LENGTH	70
#define GENE_LENGTH		2

class BobsMap
{
public:
	//you can use this array as Bobs memory if rqd
	int memory[MAP_HEIGHT][MAP_WIDTH];

	BobsMap();

	double TestRoute(const std::vector<int>& vecPath, BobsMap& bobs);
	void Render();
	void MemoryRender();
	void ResetMemory();

private:
	//storage for the map
	static const int map[MAP_HEIGHT][MAP_WIDTH];

	static const int m_iMapWidth;
	static const int m_iMapHeight;

	static const int m_iStartX;
	static const int m_iStartY;

	static const int m_iEndX;
	static const int m_iEndY;
};