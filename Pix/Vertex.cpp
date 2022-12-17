#include "Vertex.h"
#include "MathHelper.h"
#include <iostream>


Vector3 Vertex::LerpPosition(Vector3 a, Vector3 b, float t)
{
    Vector3 lerp;
    lerp.x = static_cast<int>((b.x - a.x) * t + a.x + 0.5f);
    lerp.y = static_cast<int>((b.y - a.y) * t + a.y + 0.5f);
    lerp.z = (b.z - a.z) * t + a.z;
    //lerp.z = static_cast<int>((b.z - a.z) * t + a.z + 0.5f);

    return lerp;
}

Vector3 Vertex::LerpNormal(Vector3 a, Vector3 b, float t)
{
    Vector3 lerp;
    lerp.x = static_cast<int>((b.x - a.x) * t + a.x + 0.5f);
    lerp.y = static_cast<int>((b.y - a.y) * t + a.y + 0.5f);
    lerp.z = (b.z - a.z) * t + a.z;
    //lerp.z = static_cast<int>((b.z - a.z) * t + a.z + 0.5f);

    return MathHelper::Normalize(lerp);
}

X::Color Vertex::LerpColor(X::Color a, X::Color b, float t)
{
    X::Color lerp;
    lerp.r = ((b.r - a.r) * t) + a.r;
    lerp.g = ((b.g - a.g) * t) + a.g;
    lerp.b = ((b.b - a.b) * t) + a.b;
    lerp.a = ((b.a - a.a) * t) + a.a;
    return lerp;
}

Vertex Vertex::LerpVertex(Vertex a, Vertex b, float t)
{
    if (a.position == b.position) return a;
    Vertex lerp;
    lerp.position = LerpPosition(a.position, b.position, t);
    //lerp.normal = LerpNormal(a.normal, b.normal, t); //TODO - Wrap in if
    lerp.color = LerpColor(a.color, b.color, t);

    return lerp;
}
