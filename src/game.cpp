#include "../include/engine.hpp"
#include "../include/engine_constants.hpp"
#include "../include/engine_types.hpp"
#include <fstream>
#include <iostream>

int main(int /*argn*/, char* /*args*/ [])
{
    ge::IEngine* gameEngine = ge::getInstance();
    std::string errMsg      = gameEngine->init_engine(ge::everything);

    if (!errMsg.empty())
    {
        std::cerr << errMsg << std::endl;
        return EXIT_FAILURE;
    }

    bool run_loop = true;
    ge::event event;
    while (run_loop)
    {
        while (gameEngine->read_event(event))
        {
            if (!event.msg.empty())
            {
                std::cout << event.msg << std::endl;
            }
            if (event.type == ge::events_t::shutdown)
            {
                run_loop = false;
                break;
            }
        }
        const std::string vertexes_path = "./config/vertexes.txt";
        ge::triangle tr;
        std::ifstream file(vertexes_path);
        if (!file.is_open())
        {
            std::cerr << "Can't open file with vertexes values" << std::endl;
            continue;
        }
        file >> tr;
        gameEngine->render_triangle(tr);
        gameEngine->swap_buffers();
    }
    gameEngine->uninit_engine();
    return EXIT_SUCCESS;
}
