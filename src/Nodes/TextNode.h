#pragma once

#include "Node.h"
#include "../Style.h"

#include <string>
#include <JEngine/Graphics/Font.h>

class TextNode : public Node {
private:
    std::string _text;
    Style::Font* _font;

public:
    explicit TextNode(Slides* parent) : Node(parent, Type::Text) {}

    void render(int width, int height) const override;

    inline const std::string& text() const { return _text; }
    inline const Style::Font* font() const { return _font; }

    void setText(const std::string& text) { _text = text; }
    void setFont(const std::string& path);
};