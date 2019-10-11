#include <JEngine/JEngine.h>
#include <JEngine/Math/Vector.h>
#include <JEngine/Graphics/Display.h>
#include <JEngine/Graphics/Font.h>

#include <chrono>
#include <iostream>

#include "Style.h"
#include "Slide.h"

int main() {
    // Init
    using namespace JEngine;
    Game::flags() << Game::EnableFonts;
    
    // Window
    Display window(1280, 720, "Demmio", true);
    window.vsync(true);
    window.fullscreen(true);
//    window.showCursor(false);
    
    auto t1 = std::chrono::high_resolution_clock::now();

    // Style
    Style style("../test.dem/style.json");
    
    // Slides
    Slides slides(&style);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    std::cout << "Loaded slides in " << time_span.count() << "ms" << std::endl;
    
    // Render
    auto render = [&]() {
        window.clear(style.background());
        
        slides.currentSlide().render(window.width(), window.height());
    };
    
    // Update
    auto update = [&](float delta) {
        if (window.keyOnce(KeyRight)) {
            slides.next();
        }
        if (window.keyOnce(KeyLeft)) {
            slides.back();
        }
        
        // Quit
        if (window.key(KeyLeftControl) && window.keyOnce('Q')) {
            window.close();
        }
    };
    
    // Run
    window.run(render, update);
    return 0;
}