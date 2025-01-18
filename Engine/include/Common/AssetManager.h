#pragma once

#include <map>
#include <filesystem>
#include <string>
#include "SDL2/SDL_image.h"

namespace cedar
{
	using MapLayout = std::vector<std::vector<int>>;
	class AssetManager
	{
	public:
		AssetManager(SDL_Renderer* renderer);
		~AssetManager();

		static AssetManager* Inst();

		void ClearAssets();
		void LoadAssets(const std::string& assetPath);
		void LoadTilemaps(const std::string& tilemapPath);

		void LoadLevel(const std::string& tilemapId, const std::string& levelMapId);

		SDL_Texture* GetTexture(const std::string& assetId) const;
		SDL_Texture* GetTileMap(const std::string& tilemapId) const;
		const MapLayout& GetLevelMap(const std::string& levelMapId) const;

	private:
		static AssetManager* s_assetManager;

		SDL_Renderer* m_renderer;
		std::map<std::string, SDL_Texture*> m_textures;
		std::map<std::string, SDL_Texture*> m_tileMaps;
		std::map<std::string, MapLayout> m_levelMaps;
	};
} // namespace cedar
