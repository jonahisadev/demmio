#pragma once

#include <JEngine/JEngine.h>
#include <JEngine/Math/Vector.h>
#include <JEngine/Graphics/Font.h>

#include <jjson/json.h>
#include <map>
#include <string>
#include <utility>

#include "Util.h"

class Style {
public:
    struct Font {
        std::shared_ptr<JEngine::Font> font_face;
        JEngine::Vector3f color;
        
        Font(std::shared_ptr<JEngine::Font> font_face, JEngine::Vector3f color)
        : font_face(std::move(font_face)), color(color) {}
    };
    
private:
    JEngine::Vector3i _background;
    std::map<std::string, Font*> _fonts;
    std::string _res;
    
public:
    explicit Style(const std::string& path);
    ~Style();
    
    const JEngine::Vector3i& background();
    const Font* font(std::string name);
};