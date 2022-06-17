#include <Game.h>

int main(int argc, char *argv[]) {
		
	Cober::Game* game = new Cober::Game();

	game->Initialize();
	game->Run();
	game->Destroy();

	return 0;
}
