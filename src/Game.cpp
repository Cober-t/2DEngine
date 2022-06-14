#include<iostream>
#include"Game.h"

Game::Game() {
	std::cout << "2DEngine Constructor!" << std::endl;
}

Game::~Game(){
	std::cout << "2DEngine Destructor!" << std::endl;
}

void Game::Initialice() {

}

void Game::Run(){
	
	//while(true) {
	//	ProcessInputs();
	//	Update();
	//	Render();
	//}
}

void Game::Destroy() {

}

void Game::ProcessInputs() {

}

void Game::Update() {

}

void Game::Render() {

}
