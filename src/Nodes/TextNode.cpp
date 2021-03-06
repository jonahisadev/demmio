#include "TextNode.h"

void TextNode::render(JEngine::Matrix4f view, int width, int height) {
    if (_relative == RelativeToCenter) {
        _font->font_face->render(
                (width / 2) - (_size.x() / 2) + _pos.x(),
                (height / 2) - (_size.y() / 2) + _pos.y(),
                _text,
                _font->color
        );
    } else {
        _font->font_face->render(_pos.x(), _pos.y(), _text, _font->color);
    }
}

void TextNode::setFont(const std::string &path) {
    _font = const_cast<Style::Font*>(_parent->style()->font(path));
}
