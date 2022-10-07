#include <XEngine.h>

const char* soundFileNames[] =
{
	"megamanx_shot.wav",
	"megamanx_blast.wav",
	"megamanx_title.wav",
	"megamanx_spark_mandrill.wav",
	"megamanx_storm_eagle.wav"
};

X::SoundId soundIds[std::size(soundFileNames)];

bool GameLoop(float deltaTime)
{
	for (size_t i = 0; i < std::size(soundFileNames); ++i)
	{
		char buffer[256];
		sprintf_s(buffer, "%d - %s", (int)(i + 1), soundFileNames[i]);
		X::DrawScreenText(buffer, 20.0f, 24.0f * (i + 1), 24.0f, X::Colors::Cyan);
	}

	if (X::IsKeyPressed(X::Keys::ONE))
	{
		X::PlaySoundOneShot(soundIds[0]);
	}
	if (X::IsKeyPressed(X::Keys::TWO))
	{
		X::PlaySoundOneShot(soundIds[1]);
	}
	if (X::IsKeyPressed(X::Keys::THREE))
	{
		X::StopSoundLoop(soundIds[2]);
		X::StopSoundLoop(soundIds[3]);
		X::StopSoundLoop(soundIds[4]);
		X::PlaySoundLoop(soundIds[2]);
	}
	if (X::IsKeyPressed(X::Keys::FOUR))
	{
		X::StopSoundLoop(soundIds[2]);
		X::StopSoundLoop(soundIds[3]);
		X::StopSoundLoop(soundIds[4]);
		X::PlaySoundLoop(soundIds[3]);
	}
	if (X::IsKeyPressed(X::Keys::FIVE))
	{
		X::StopSoundLoop(soundIds[2]);
		X::StopSoundLoop(soundIds[3]);
		X::StopSoundLoop(soundIds[4]);
		X::PlaySoundLoop(soundIds[4]);
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	for (size_t i = 0; i < std::size(soundFileNames); ++i)
	{
		soundIds[i] = X::LoadSound(soundFileNames[i]);
	}

	X::Run(GameLoop);

	X::ClearAllSounds();
	X::Stop();
	return 0;
}