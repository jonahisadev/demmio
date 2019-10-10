#include "Style.h"

Style::Style(const char *path) {
    JObject* style = JSONDocument::parseFromFile(path);
    
    // Background color
    auto background = style->array("background");
    _background = Util::read3i(background);
    
    // Fonts
    auto fonts = style->array("fonts");
    for (int i = 0; i < fonts->size(); i++) {
        auto font_obj = jarray_index(fonts, JObject, i);
        
        std::string font_name = font_obj->string("name")->value();
        int font_size = int(font_obj->number("size")->value());
        JEngine::Vector3f color = Util::read3f(font_obj->array("color"));
        color.normalize(255);
        
        auto font_path = std::string("../test.dem/res/" + font_name + ".ttf");
        auto font_face = std::make_shared<JEngine::Font>(font_path.c_str(), font_size);
        Font* font = new Font(font_face, color);
        
        _fonts.insert({font_name + "-" + std::to_string(font_size), font});
    }
}

Style::~Style() {
    auto it = _fonts.begin();
    while (it != _fonts.end()) {
        delete it->second;
        it++;
    }
}

const JEngine::Vector3i &Style::background() {
    return _background;
}

const Style::Font* Style::font(std::string name) {
    return _fonts.at(name);
}
