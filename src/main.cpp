#include <JEngine/JEngine.h>
#include <JEngine/Math/Vector.h>
#include <JEngine/Graphics/Display.h>
#include <JEngine/Graphics/Font.h>

#include <chrono>
#include <iostream>

#include "Style.h"
#include "Slide.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: demmio [file.dem]" << std::endl;
        return 1;
    }
    
    // Init
    using namespace JEngine;
    Game::flags() << Game::EnableFonts;
    
    // Window
    Display window(1280, 720, "Demmio", true);
    window.vsync(true);
    window.fullscreen(true);
//    window.showCursor(false);
    
    auto t1 = std::chrono::high_resolution_clock::now();

    // Path
    auto path = std::string(argv[1]);
    
    // Slides and style
    Style style(path, &window);
    Slides slides(path, &style);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    std::cout << "Loaded slides in " << time_span.count() << "ms" << std::endl;
    
    // Render
    auto render = [&](Matrix4f view) {
        window.clear(style.background());
        
        slides.currentSlide().render(view, window.width(), window.height());
    };
    
    // Update
    auto update = [&](float delta) {
        if (window.keyOnce(KeyRight)) {
            slides.next();
        }
        if (window.keyOnce(KeyLeft)) {
            slides.back();
        }
        
        // Leave fullscreen
        if (window.keyOnce(KeyEscape)) {
            window.fullscreen(false);
        }
        
        // Enter fullscreen
        if (window.keyOnce(KeyF11)) {
            window.fullscreen(true);
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