#include "BobGA.h"

void BobGA::Run()
{
	CreateStartPopulation();

	m_bBusy = true;
}

void BobGA::Epoch()
{
	UpdateFitnessScores();

	int NewBabies = 0;
	std::vector<Genome> vecBabyGenomes;

	while (NewBabies < m_iPopSize)
	{
		Genome mum = RouletteWheelSelection();
		Genome dad = RouletteWheelSelection();

		Genome baby1, baby2;
		Crossover(mum.vecBits, dad.vecBits, baby1.vecBits, baby2.vecBits);

		Mutate(baby1.vecBits);
		Mutate(baby2.vecBits);

		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);
		NewBabies += 2;
	}

	m_vecGenomes = vecBabyGenomes;
	++m_iGeneration;
}

void BobGA::Render()
{
	//render the map
	m_BobsMap.Render();

	//render the best route
	m_BobsBrain.MemoryRender();

	//Render additional information
	std::string s = "Generation: " + std::to_string(m_iGeneration);
	X::DrawScreenText(s.c_str(), 5, 5, 32.0f, X::Colors::White);

	const float screenWidth = (float)X::GetScreenWidth();
	const float screenHeight = (float)X::GetScreenHeight();

	if (!m_bBusy)
	{
		std::string Start = "Press Return to start a new run";
		float textWidth = X::GetTextWidth(Start.c_str(), 32.0f);
		X::DrawScreenText(Start.c_str(), (screenWidth - textWidth) * 0.5f, screenHeight * 0.4f, 32.0f, X::Colors::White);
	}
	else
	{
		std::string Start = "Space to stop";
		float textWidth = X::GetTextWidth(Start.c_str(), 32.0f);
		X::DrawScreenText(Start.c_str(), (screenWidth - textWidth) * 0.5f, screenHeight * 0.4f, 32.0f, X::Colors::White);
	}
}

void BobGA::Mutate(std::vector<int>& vecBits)
{
	for (int curBit = 0; curBit < vecBits.size(); curBit++)
	{
		if (X::RandomFloat() < m_dMutationRate)
		{
			vecBits[curBit] = !vecBits[curBit];
		}
	}
}

void BobGA::Crossover(const std::vector<int>& mum, const std::vector<int>& dad, std::vector<int>& baby1, std::vector<int>& baby2)
{
	if ((X::RandomFloat() > m_dCrossoverRate) || (mum == dad))
	{
		baby1 = mum;
		baby2 = dad;
		return;
	}

	int cp = X::Random(0, m_iChromoLength - 1);
	for (int i = 0; i < cp; i++)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}
	for (int i = cp; i < mum.size(); i++)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}

Genome& BobGA::RouletteWheelSelection()
{
	double fSlice = X::RandomFloat() * m_dTotalFitnessScore;
	double cfTotal = 0;
	int SelectedGenome = 0;
	for (int i = 0; i < m_iPopSize; ++i)
	{
		cfTotal += m_vecGenomes[i].fitness;
		if (cfTotal > fSlice)
		{
			SelectedGenome = i;
			break;
		}
	}
	return m_vecGenomes[SelectedGenome];
}

void BobGA::UpdateFitnessScores()
{
	m_iFittestGenome = 0;
	m_dBestFitnessScore = 0;
	m_dTotalFitnessScore = 0;

	BobsMap TempMemory;

	//update the fitness scores and keep a check on fittest so far
	for (int i = 0; i < m_iPopSize; ++i)
	{
		//decode each genomes chromosome into a vector of directions
		std::vector<int> vecDirections = Decode(m_vecGenomes[i].vecBits);

		//get it's fitness score
		m_vecGenomes[i].fitness = m_BobsMap.TestRoute(vecDirections, TempMemory);

		//update total
		m_dTotalFitnessScore += m_vecGenomes[i].fitness;

		//if this is the fittest genome found so far, store results
		if (m_vecGenomes[i].fitness > m_dBestFitnessScore)
		{
			m_dBestFitnessScore = m_vecGenomes[i].fitness;

			m_iFittestGenome = i;

			m_BobsBrain = TempMemory;

			//Has Bob found the exit?
			if (m_vecGenomes[i].fitness == 1)
			{
				//is so, stop the run
				m_bBusy = false;
			}
		}

		TempMemory.ResetMemory();

	}//next genome
}

std::vector<int> BobGA::Decode(const std::vector<int>& bits)
{
	std::vector<int>	directions;

	//step through the chromosome a gene at a time
	for (int gene = 0; gene < bits.size(); gene += m_iGeneLength)
	{
		//get the gene at this position
		std::vector<int> ThisGene;

		for (int bit = 0; bit < m_iGeneLength; ++bit)
		{
			ThisGene.push_back(bits[gene + bit]);
		}

		//convert to decimal and add to list of directions
		directions.push_back(BinToInt(ThisGene));
	}

	return directions;
}

int BobGA::BinToInt(const std::vector<int>& v)
{
	int val = 0;
	int multiplier = 1;

	for (int cBit = (int)v.size(); cBit > 0; cBit--)
	{
		val += v[cBit - 1] * multiplier;

		multiplier *= 2;
	}

	return val;
}

void BobGA::CreateStartPopulation()
{
	m_vecGenomes.clear();

	for (int i = 0; i < m_iPopSize; i++)
	{
		m_vecGenomes.push_back(Genome(m_iChromoLength));
	}

	m_iGeneration = 0;
	m_iFittestGenome = 0;
	m_dBestFitnessScore = 0;
	m_dTotalFitnessScore = 0;
}