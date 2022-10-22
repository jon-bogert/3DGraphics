﻿#pragma once
#include "Vector3.h"
#include "XColors.h"

struct Vertex
{
    Vector3 position = { 0.f, 0.f, 0.f };
    X::Color color = { 0.f, 0.f, 0.f, 0.f};

    static Vector3 LerpPosition(Vector3 a, Vector3 b, float t);
    static X::Color LerpColor(X::Color a, X::Color b, float t);
    static Vertex LerpVertex(Vertex a, Vertex b, float t);
};
