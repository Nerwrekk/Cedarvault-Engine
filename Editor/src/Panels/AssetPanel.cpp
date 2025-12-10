#include "Panels/AssetPanel.h"

#include "CedarVault.h"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace cedar
{
	const char* s_AssetDirectory = "../assets";

	void AssetPanel::DrawAssetPanel()
	{
		ImGui::Begin("Assets");
		for (auto dir : fs::directory_iterator(s_AssetDirectory))
		{
			std::string path = dir.path().string();
			ImGui::Text("%s", path.c_str());
		}

		ImGui::End();
	}
} // namespace cedar
