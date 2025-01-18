#include "Common/AssetManager.h"
#include "Common/Logger.h"
#include "Common/Utils.h"

#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

namespace cedar
{
	AssetManager* AssetManager::s_assetManager = nullptr;

	AssetManager::AssetManager(SDL_Renderer* renderer)
	{
		m_renderer = renderer;

		//TODO: Assert this so we make sure we only create one asset manager
		s_assetManager = this;
	}

	AssetManager::~AssetManager()
	{
		ClearAssets();
	}

	AssetManager* AssetManager::Inst()
	{
		return s_assetManager;
	}

	void AssetManager::ClearAssets()
	{
		for (auto& [key, texture] : m_textures)
		{
			SDL_DestroyTexture(texture);
		}

		m_textures.clear();
	}

	void AssetManager::LoadAssets(const std::string& assetPath)
	{
		try
		{
			if (!fs::exists(assetPath) && !fs::is_directory(assetPath))
			{
				CEDAR_FATAL("Path: \"{}\" Does not exist", assetPath);
			}

			CEDAR_INFO("Path: {} exists!", assetPath);

			for (const auto& dirEntry : fs::directory_iterator(assetPath))
			{
				if (fs::is_regular_file(dirEntry.status()))
				{
					// Print the file name
					const auto fileName = dirEntry.path().stem().string();
					CEDAR_WARN("File: {}", fileName);

					SDL_Surface* surface = IMG_Load(dirEntry.path().string().c_str());
					SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
					SDL_FreeSurface(surface);

					m_textures.emplace(fileName, texture);
				}
			}
		}
		catch (const std::exception& e)
		{
			CEDAR_FATAL("{}", e.what());
		}
	}

	//Loads in all the tilemaps and .maps from a specific folder
	//the key id is chosen by the filename
	void AssetManager::LoadTilemaps(const std::string& tilemapPath)
	{
		try
		{
			if (!fs::exists(tilemapPath) && !fs::is_directory(tilemapPath))
			{
				CEDAR_FATAL("Path: \"{}\" Does not exist", tilemapPath);
			}

			CEDAR_INFO("Path: {} exists!", tilemapPath);

			std::map<std::string, MapLayout> mapLayout;
			for (const auto& dirEntry : fs::directory_iterator(tilemapPath))
			{
				if (fs::is_regular_file(dirEntry.status()))
				{
					// Print the file name
					const auto fileName = dirEntry.path().stem().string();
					CEDAR_WARN("File: {}", fileName);

					if (dirEntry.path().extension() == ".map")
					{
						CEDAR_WARN("is map");

						std::ifstream file(dirEntry.path(), std::ios::in);
						MapLayout layout;
						while (!file.eof())
						{
							std::string line;
							std::getline(file, line);
							auto row = utils::split_string(line, ',');
							std::vector<int> temp;
							for (auto& item : row)
							{
								temp.push_back(utils::to_num<int>(item));
							}

							layout.push_back(temp);
						}

						m_levelMaps.emplace(fileName, layout);
					}

					if (dirEntry.path().extension() == ".png")
					{
						CEDAR_WARN("is png");

						SDL_Surface* surface = IMG_Load(dirEntry.path().string().c_str());
						SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
						SDL_FreeSurface(surface);

						m_tileMaps.emplace(fileName, texture);
					}
				}
			}
		}
		catch (const std::exception& e)
		{
			CEDAR_FATAL("{}", e.what());
		}
	}

	void AssetManager::LoadLevel(const std::string& tilemapId, const std::string& levelMapId)
	{
		SDL_Texture* texture = m_tileMaps.at(tilemapId);
		const auto& map = m_levelMaps.at(levelMapId);
		int colum = 0;
		for (auto& col : map)
		{
			int rowiew = 0;
			for (auto& row : col)
			{
				SDL_Rect srcRect = { 0, 0, 32, 32 };

				//Destination rectangle that we want to place our texture.
				SDL_Rect dstRect = {
					32 * colum,
					32 * rowiew,
					32,
					32
				};

				SDL_RenderCopy(m_renderer, texture, &srcRect, &dstRect);
				rowiew++;
			}

			colum++;
		}
	}

	SDL_Texture* AssetManager::GetTexture(const std::string& assetId) const
	{
		return m_textures.at(assetId);
	}

	SDL_Texture* AssetManager::GetTileMap(const std::string& tilemapId) const
	{
		return m_tileMaps.at(tilemapId);
	}

	const MapLayout& AssetManager::GetLevelMap(const std::string& levelMapId) const
	{
		return m_levelMaps.at(levelMapId);
	}
}
// namespace cedar
