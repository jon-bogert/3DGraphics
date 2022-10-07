#pragma once

#include "BobsMap.h"

// Code		Decoded		Direction
// ------------------------------
// 00		0			North
// 01		1			South
// 10		2			East
// 11		3			West

struct Genome
{
	std::vector<int> vecBits;
	double fitness = 0.0;

	Genome() = default;
	Genome(int numBits)
	{
		for (int i = 0; i < numBits; ++i)
			vecBits.push_back(X::Random(0, 1));
	}
};

class BobGA
{
public:
	BobGA(double cross_rat,
		double mut_rat,
		int pop_size,
		int num_bits,
		int gene_len) :m_dCrossoverRate(cross_rat),
		m_dMutationRate(mut_rat),
		m_iPopSize(pop_size),
		m_iChromoLength(num_bits),
		m_dTotalFitnessScore(0.0),
		m_iGeneration(0),
		m_iGeneLength(gene_len),
		m_bBusy(false)
	{
		CreateStartPopulation();
	}
	void Run();
	void Epoch();
	void Render();

	int Generation() { return m_iGeneration; }
	int GetFittest() { return m_iFittestGenome; }
	bool Started() { return m_bBusy; }
	void Stop() { m_bBusy = false; }

private:
	std::vector<Genome> m_vecGenomes;

	int m_iPopSize;
	double m_dCrossoverRate;
	double m_dMutationRate;

	int m_iChromoLength;

	int m_iGeneLength;
	int m_iFittestGenome;
	double m_dBestFitnessScore;
	double m_dTotalFitnessScore;
	int m_iGeneration;

	BobsMap m_BobsMap;
	BobsMap m_BobsBrain;

	bool m_bBusy;
	void Mutate(std::vector<int>& vecBits);
	void Crossover(const std::vector<int>& mum, const std::vector<int>& dad, std::vector<int>& baby1, std::vector<int>& baby2);

	Genome& RouletteWheelSelection();

	void UpdateFitnessScores();

	std::vector<int> Decode(const std::vector<int>& bits);

	int BinToInt(const std::vector<int>& v);

	void CreateStartPopulation();
};