#include <Engine.h>

int main(int argc, char *argv[]) {
		
	Cober::Engine* engine = new Cober::Engine();

	engine->Initialize();
	engine->Run();
	engine->Destroy();

	delete engine;
	return 0;
}
