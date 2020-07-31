#pragma once

#include <JEngine/JEngine.h>
#include <JEngine/Graphics/TexturedQuad.h>
#include <JEngine/Graphics/Display.h>
#include "Node.h"
#include "../Slide.h"

class ImageNode : public Node {
private:
    JEngine::TexturedQuad* _image;

public:
    ImageNode(Slides* parent) : Node(parent, Type::Image) {}

    void render(JEngine::Matrix4f view, int width, int height) override;

    inline const JEngine::TexturedQuad& image() const { return *_image; }
    void setImage(std::string path);
};