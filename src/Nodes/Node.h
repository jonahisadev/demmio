#pragma once

#include <JEngine/Math/Vector.h>
#include "../Slide.h"

class Slides;

class Node {
public:
    enum RelativePosition {
        RelativeToNone,
        RelativeToCenter,
    };

    enum Type {
        Text,
        Image
    };

protected:
    Slides* _parent;
    Type _type;
    JEngine::Vector2f _pos;
    JEngine::Vector2f _size;
    RelativePosition _relative = RelativeToNone;

public:
    explicit Node(Slides* parent, Type type) : _parent(parent), _type(type) {}

    virtual void render(JEngine::Matrix4f view, int width, int height) = 0;

    inline JEngine::Vector2f& position() { return _pos; }
    inline const JEngine::Vector2f& size() const { return _size; }
    inline const RelativePosition relative() const { return _relative; }
    inline Type type() const { return _type; }

    inline void setPosition(const JEngine::Vector2f& pos) { _pos = pos; }
    inline void setSize(const JEngine::Vector2f& size) { _size = size; }
    inline void setRelative(RelativePosition relative) { _relative = relative; }
};