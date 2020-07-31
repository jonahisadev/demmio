#include "ImageNode.h"

void ImageNode::render(JEngine::Matrix4f view, int width, int height) {
    if (_relative == Node::RelativeToCenter) {
        JEngine::Vector2f center = {float(width / 2), float(height / 2)};
        _image->setCenter(center);
        _image->translate(_pos.x(), _pos.y());
    }

    _image->render(view);
}

void ImageNode::setImage(std::string path) {
    _image = new JEngine::TexturedQuad(_pos.x(), _pos.y(), _size.x(), _size.y(), path.c_str());
    _image->linearInterp(true);
}