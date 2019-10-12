#include "ImageNode.h"

void ImageNode::render(int width, int height) {
    if (_relative == Node::RelativeToCenter) {
        JEngine::Vector2f center = {float(width / 2), float(height / 2)};
        _image->setCenter(center);
        _image->translate(_pos.x(), _pos.y());
    }
    _image->render();
}

void ImageNode::setImage(std::string path) {
    _image = std::make_shared<JEngine::TexturedQuad>(_pos.x(), _pos.y(), _size.x(), _size.y(), path.c_str());
    _image->linearInterp(true);
}