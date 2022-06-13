#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>


int main() {
	// Init lua
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	// Test glm
	glm::vec2 velocity = glm::vec2(0.0, 0.0);

	// Init SDL2
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout <<  "HOLAA" << std::endl;
	return 0;
}
