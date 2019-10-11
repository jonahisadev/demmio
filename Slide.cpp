#include "Slide.h"

Slide::Slide(Slides* parent, const JObject *slide) 
: _parent(parent)
{
    const JArray* nodes = slide->array("nodes");
    
    // Loop through nodes
    for (int i = 0; i < nodes->size(); i++) {
        const JObject* jnode = jarray_index(nodes, JObject, i);
        
        // Type
        auto type = jnode->string("type")->value();
        
        // Text
        if (type == "text") {
            TextNode node;
            node.text = jnode->string("text")->value();
            node.font = const_cast<Style::Font*>(_parent->_style->font(jnode->string("font")->value()));
            node.pos = Util::read2f(jnode->array("pos"));
            
            // Relative text positioning
            if (jnode->string("relative") != nullptr) {
                std::string relative = jnode->string("relative")->value();
                if (relative == "center") {
                    node.relative = RelativeToCenter;
                }
            }
            
            float width = node.font->font_face->width(node.text);
            float height = node.font->font_face->height(node.text);
            node.pos.translate(0, height);
            node.size = {width, height};
            
            _text_nodes.push_back(node);
        }
    }
}

void Slide::render(int width, int height) const {
    for (const auto& text : _text_nodes) {
        if (text.relative == RelativeToCenter) {
            text.font->font_face->render(
                (width / 2) - (text.size.x() / 2) + text.pos.x(),
                (height / 2) - (text.size.y() / 2) + text.pos.y(),
                text.text,
                text.font->color
            );
        } else {
            text.font->font_face->render(text.pos.x(), text.pos.y(), text.text, text.font->color);
        }
    }
}

Slides::Slides(Style* style) {
    JObject* slide_doc = JSONDocument::parseFromFile("../test.dem/slides.json");
    const JArray* slide_arr = slide_doc->array("slides");

    _current = 0;
    _max = slide_arr->size() - 1;
    _style = style;
    
    for (int i = 0; i < slide_arr->size(); i++) {
        JObject* slide = jarray_index(slide_arr, JObject, i);
        _slides.push_back(new Slide(this, slide));
    }
}

void Slides::next() {
    if (_current < _max) ++_current;
}

void Slides::back() {
    if (_current > 0) -- _current;
}
