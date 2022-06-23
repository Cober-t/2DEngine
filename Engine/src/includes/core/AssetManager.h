#pragma once
#include <Core.h>
//#include <Engine.h>

namespace Cober {

	class AssetManager {
	public:
		AssetManager();
		~AssetManager();

		void ClearAssets();
		void AddTexture(const std::string& assetID, const std::string& filePath);

		SDL_Texture* GetTexture(const std::string& assetID) { return textures[assetID]; };
		//SDL_Texture* GetFont(const std::string& assetID) { return textures[assetID]; };
		//SDL_Texture* GetAudio(const std::string& assetID) { return textures[assetID]; };
	private:
		std::map<std::string, SDL_Texture*> textures;
		//std::map<std::string, SDL_ttf*> fonts;
		//std::map<std::string, SDL_audio*> textures;
	};
}