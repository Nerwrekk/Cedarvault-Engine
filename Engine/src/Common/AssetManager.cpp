#include "Common/AssetManager.h"
#include "Common/Logger.h"

#include <iostream>

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

	AssetManager* AssetManager::Inst()
	{
		return s_assetManager;
	}

	void AssetManager::ClearAssets()
	{
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

	SDL_Texture* AssetManager::GetTexture(const std::string& assetId)
	{
		return m_textures.at(assetId);
	}
} // namespace cedar
