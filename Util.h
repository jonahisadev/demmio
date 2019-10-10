#pragma once

#include <JEngine/Math/Vector.h>
#include <jjson/json.h>

class Util {
public:
    static const JEngine::Vector3i& read3i(const JArray* arr);
    static const JEngine::Vector3f& read3f(const JArray* arr);
    static const JEngine::Vector2f& read2f(const JArray* arr);
};