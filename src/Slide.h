#pragma once

#include <vector>
#include <memory>

#include <jjson/json.h>
#include <JEngine/JEngine.h>
#include <JEngine/Graphics/TexturedQuad.h>

#include "Style.h"
#include "Nodes/Node.h"

class Slides;
class Node;

class Slide {
public:
    Slides* _parent;
    std::vector<Node*> _nodes;
    
private:
    Slide(Slides* parent, const JObject* slide);
    friend class Slides;
    
public:
    void render(JEngine::Matrix4f view, int width, int height) const;
};

class Slides {
private:
    std::vector<Slide*> _slides;
    int _current;
    int _max;
    Style* _style;
    std::string _res;
    friend class Slide;
    
public:
    Slides(const std::string& path, Style* style);
    
    void next();
    void back();
    inline const Style* style() const { return _style; }
    
    const Slide& currentSlide() const { return *_slides.at(_current); }
};