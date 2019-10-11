#include "ImageNode.h"

void ImageNode::render(int width, int height) const {
    _image->render();
}

void ImageNode::setImage(std::string path) {
    _image = std::make_shared<JEngine::TexturedQuad>(_pos.x(), _pos.y(), _size.x(), _size.y(), path.c_str());
}
