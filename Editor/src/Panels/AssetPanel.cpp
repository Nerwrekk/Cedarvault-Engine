#include "Panels/AssetPanel.h"

#include "CedarVault.h"

#include <string>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

namespace cedar
{
	static const fs::path s_AssetPath = "../assets";

	AssetPanel::AssetPanel()
	    : m_currentDirectory(s_AssetPath)
	{
	}

	void AssetPanel::DrawAssetPanel()
	{
		ImGui::Begin("Assets");

		if (m_currentDirectory != s_AssetPath)
		{
			if (ImGui::Button("<-"))
			{
				m_currentDirectory = m_currentDirectory.parent_path();
			}
		}

		for (auto dirEntry : fs::directory_iterator(m_currentDirectory))
		{
			const auto& path    = dirEntry.path();
			std::string pathStr = dirEntry.path().string();
			auto relativePath   = fs::relative(path, s_AssetPath);
			auto filenameStr    = relativePath.filename().string();
			if (dirEntry.is_directory())
			{
				if (ImGui::Button(filenameStr.c_str()))
				{
					m_currentDirectory /= dirEntry.path().filename();
				}
			}
			else
			{
				if (ImGui::Button(filenameStr.c_str()))
				{
				}
			}
		}

		ImGui::End();
	}
} // namespace cedar
