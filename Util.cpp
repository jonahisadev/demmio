#include "Util.h"

const JEngine::Vector3i& Util::read3i(const JArray *arr) {
    int buffer[3];
    for (int i = 0; i < 3; i++) {
        auto num = jarray_index(arr, JNumber, i);
        buffer[i] = int(num->value());
    }
    auto vec = std::make_shared<JEngine::Vector3i>(buffer[0], buffer[1], buffer[2]);
    return *vec;
}

const JEngine::Vector3f &Util::read3f(const JArray *arr) {
    float buffer[3];
    for (int i = 0; i < 3; i++) {
        auto num = jarray_index(arr, JNumber, i);
        buffer[i] = num->value();
    }
    auto vec = std::make_shared<JEngine::Vector3f>(buffer[0], buffer[1], buffer[2]);
    return *vec;
}

const JEngine::Vector2f &Util::read2f(const JArray *arr) {
    float buffer[2];
    for (int i = 0; i < 2; i++) {
        auto num = jarray_index(arr, JNumber, i);
        buffer[i] = num->value();
    }
    auto vec = std::make_shared<JEngine::Vector2f>(buffer[0], buffer[1]);
    return *vec;
}
