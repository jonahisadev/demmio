#include "Slide.h"
#include "Nodes/TextNode.h"
#include "Nodes/ImageNode.h"

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
            TextNode* node = new TextNode(parent);
            node->setText(jnode->string("text")->value());
            node->setFont(jnode->string("font")->value());
            node->setPosition(Util::read2f(jnode->array("pos")));

            // Relative text positioning
            if (jnode->string("relative") != nullptr) {
                std::string relative = jnode->string("relative")->value();
                if (relative == "center")
                    node->setRelative(Node::RelativeToCenter);
            }
            
            float width = node->font()->font_face->width(node->text());
            float height = node->font()->font_face->height(node->text());
            node->position().translate(0, height);
            node->setSize({width, height});
            
            _nodes.push_back(node);
        }
        
        else if (type == "image") {
            ImageNode* node = new ImageNode(parent);
            node->setPosition(Util::read2f(jnode->array("pos")));
            node->setSize(Util::read2f(jnode->array("size")));
            std::string path = parent->_res + jnode->string("name")->value();
            node->setImage(path);

            // TODO: modularize this
            if (jnode->string("relative") != nullptr) {
                std::string relative = jnode->string("relative")->value();
                if (relative == "center")
                    node->setRelative(Node::RelativeToCenter);
            }
            
            _nodes.push_back(node);
        }
    }
}

void Slide::render(JEngine::Matrix4f view, int width, int height) const {
    for (const auto& node : _nodes) {
        node->render(view, width, height);
    }
}

Slides::Slides(const std::string& path, Style* style) {
    JObject* slide_doc = JSONDocument::parseFromFile(path + "/slides.json");
    const JArray* slide_arr = slide_doc->array("slides");

    _current = 0;
    _max = slide_arr->size() - 1;
    _style = style;
    _res = path + "/res/";
    
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
