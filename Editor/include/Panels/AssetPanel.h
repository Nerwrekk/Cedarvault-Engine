#pragma once

#include "CedarVault.h"

#include <filesystem>

namespace cedar
{
	class AssetPanel
	{
	public:
		AssetPanel();
		~AssetPanel() = default;

		void DrawAssetPanel();

	private:
		std::filesystem::path m_currentDirectory;

		SDL_Texture* m_dirIcon;
		SDL_Texture* m_fileIcon;
	};
} // namespace cedar