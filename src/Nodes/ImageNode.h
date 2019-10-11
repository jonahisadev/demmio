#pragma once

#include <JEngine/JEngine.h>
#include <JEngine/Graphics/TexturedQuad.h>
#include "Node.h"
#include "../Slide.h"

class ImageNode : public Node {
private:
    JEngine::TexturedQuadPtr _image;

public:
    ImageNode(Slides* parent) : Node(parent, Type::Image) {}

    void render(int width, int height) const override;

    inline const JEngine::TexturedQuad& image() const { return *_image.get(); }
    void setImage(std::string path);
};