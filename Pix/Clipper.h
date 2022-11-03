#pragma once
#include <vector>
struct Vertex;

class Clipper
{
	bool mIsClipping = false;

	Clipper() {}

public:
	static Clipper* Get();
	~Clipper() {}

	void OnNewFrame(); // call in Graphics::NewFrame

	//Return true if clip test pass
	bool ClipPoint(Vertex& v);
	bool ClipLine(Vertex& v1, Vertex& v2);
	bool ClipTriangle(std::vector<Vertex>& vertices);
	bool GetIsClipping() const;
	void SetIsClipping(const bool isClipping);

private:
	static int GetRegionCode(const float& x, const float& y);
};

