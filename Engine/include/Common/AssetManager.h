#pragma once

#include <map>
#include <filesystem>
#include <string>
#include "SDL2/SDL_image.h"

namespace cedar
{
	class AssetManager
	{
	public:
		AssetManager(SDL_Renderer* renderer);
		~AssetManager();

		static AssetManager* Inst();

		void ClearAssets();
		void LoadAssets(const std::string& assetPath);

		SDL_Texture* GetTexture(const std::string& assetId) const;

	private:
		static AssetManager* s_assetManager;

		SDL_Renderer* m_renderer;
		std::map<std::string, SDL_Texture*> m_textures;
	};
} // namespace cedar
