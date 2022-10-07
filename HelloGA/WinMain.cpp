#include "BobGA.h"
#include <XEngine.h>

#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.001
#define POP_SIZE 140
#define CHROMO_LENGTH 70

BobGA* ga = nullptr;

bool GameLoop(float deltaTime)
{
	if (X::IsKeyPressed(X::Keys::ENTER))
		ga->Run();
	if (X::IsKeyPressed(X::Keys::SPACE))
		ga->Stop();

	if (ga->Started())
		ga->Epoch();

	ga->Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	ga = new BobGA(
		CROSSOVER_RATE,
		MUTATION_RATE,
		POP_SIZE,
		CHROMO_LENGTH,
		GENE_LENGTH);

	X::Run(GameLoop);

	delete ga;
	X::Stop();
	return 0;
}