#pragma once

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
	};
} // namespace cedar