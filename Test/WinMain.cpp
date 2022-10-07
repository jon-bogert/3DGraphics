#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

X::Math::Vector2 position;
X::TextureId textureId;

void GameInit()
{
	textureId = X::LoadTexture("mario.png");
}

bool GameLoop(float deltaTime)
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("MoveRight"))
		position.x += 100.0f;
	ImGui::End();

	const float speed = 100.0f;
	if (X::IsKeyDown(X::Keys::W))
		position.y -= speed * deltaTime;
	if (X::IsKeyDown(X::Keys::S))
		position.y += speed * deltaTime;
	if (X::IsKeyDown(X::Keys::A))
		position.x -= speed * deltaTime;
	if (X::IsKeyDown(X::Keys::D))
		position.x += speed * deltaTime;

	static float rotation = 0.0f;
	rotation += deltaTime;
	X::DrawSprite(textureId, position, rotation, X::Pivot::Center);
	X::DrawSprite(textureId, position, X::Pivot::TopLeft);

	float l = position.x;
	float t = position.y;
	float r = l + X::GetSpriteWidth(textureId);
	float b = t + X::GetSpriteHeight(textureId);
	X::DrawScreenRect(l, t, r, b, X::Colors::PaleGreen);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}