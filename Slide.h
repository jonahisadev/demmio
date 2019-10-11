#pragma once

#include <vector>
#include <memory>

#include <jjson/json.h>

#include "Style.h"

enum RelativePosition {
    RelativeToNone,
    RelativeToCenter,
};

class Slides;

class Slide {
public:
    struct TextNode {
        std::string text;
        Style::Font* font;
        JEngine::Vector2f pos;
        JEngine::Vector2f size;
        RelativePosition relative = RelativeToNone;
    };
    
    Slides* _parent;
    std::vector<TextNode> _text_nodes;
    
private:
    Slide(Slides* parent, const JObject* slide);
    friend class Slides;
    
public:
    void render(int width, int height) const;
};

class Slides {
private:
    std::vector<Slide*> _slides;
    int _current;
    int _max;
    Style* _style;
    friend class Slide;
    
public:
    Slides(Style* style);
    
    void next();
    void back();
    
    const Slide& currentSlide() const { return *_slides.at(_current); }
};