#include "Common/AssetManager.h"
#include "Common/Logger.h"
#include "Common/Utils.h"
#include "Common/Mindi/Mindi.h"
#include "Application/Application.h"

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
							auto row = utils::string::split(line, ',');
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

	void AssetManager::LoadConfigurations(const std::string& configPath)
	{
		try
		{
			if (!fs::exists(configPath) && !fs::is_directory(configPath))
			{
				CEDAR_FATAL("Path: \"{}\" Does not exist", configPath);
			}

			CEDAR_INFO("Path: {} exists!", configPath);

			for (const auto& dirEntry : fs::directory_iterator(configPath))
			{
				if (fs::is_regular_file(dirEntry.status()))
				{
					// Print the file name
					const auto fileName = dirEntry.path().stem().string();
					CEDAR_WARN("File: {}", fileName);

					Mindi::json_node currentConfigNode {};
					if (!Mindi::json_reader::read(dirEntry.path().string(), &currentConfigNode))
					{
						CEDAR_FATAL("Failed to load in config file: {}", fileName);
					}
					//Config section
					auto tileLevelMap       = new TileLevelMap();
					tileLevelMap->TileSize  = currentConfigNode["tileSize"].get_int();
					tileLevelMap->TileScale = currentConfigNode["tileScale"].get_float();
					tileLevelMap->tilemap   = GetTileMap(currentConfigNode["textureId"].get_string());
					//load in width and height of the tilemap
					SDL_QueryTexture(tileLevelMap->tilemap, nullptr, nullptr, &tileLevelMap->Width, &tileLevelMap->Height);
					auto& levels = currentConfigNode["levelMaps"].get_array();
					for (Mindi::json_node* levelId : levels)
					{
						tileLevelMap->levelMapIds.push_back(levelId->get_string());
					}
					//Add new TileLevelMap
					m_allLevels.emplace(currentConfigNode["name"].get_string(), tileLevelMap);
				}
			}
		}
		catch (const std::exception& e)
		{
			CEDAR_FATAL("{}", e.what());
		}
	}

	void AssetManager::LoadLevel(const std::string& levelMapId, int level)
	{
		TileLevelMap* tileLevelMap = GetTileLevelMap(levelMapId);
		auto& map                  = GetLevelMap(tileLevelMap->levelMapIds.at(level));

		// const auto& map = m_levelMaps.at(levelMapId);
		int mapNumRows = map.size();
		int mapNumCols = map.at(0).size();

		Application::Get().GameSetting.MapHeight = mapNumRows * tileLevelMap->TileSize * tileLevelMap->TileScale;
		Application::Get().GameSetting.MapWidth  = mapNumCols * tileLevelMap->TileSize * tileLevelMap->TileScale;

		Application::Get().GameSetting.CurrentLevel      = levelMapId;
		Application::Get().GameSetting.CurrentLevelIndex = level;
	}

	SDL_Texture* AssetManager::GetTexture(const std::string& assetId) const
	{
		SDL_Texture* texture;
		try
		{
			texture = m_textures.at(assetId);
		}
		catch (const std::exception& e)
		{
			CEDAR_FATAL("Unable to find asset with assed id: {}", assetId);
		}

		return texture;
	}

	SDL_Texture* AssetManager::GetTileMap(const std::string& tilemapId) const
	{
		return m_tileMaps.at(tilemapId);
	}

	const MapLayout& AssetManager::GetLevelMap(const std::string& levelMapId) const
	{
		return m_levelMaps.at(levelMapId);
	}

	TileLevelMap* AssetManager::GetTileLevelMap(const std::string& tileLevelMapId) const
	{
		return m_allLevels.at(tileLevelMapId);
	}
}
// namespace cedar
