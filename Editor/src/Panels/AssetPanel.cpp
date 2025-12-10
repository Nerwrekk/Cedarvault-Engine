#include "Panels/AssetPanel.h"

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
		SDL_Surface* surface = IMG_Load("../Resources/Icons/DirectoryIcon.png");
		m_dirIcon            = SDL_CreateTextureFromSurface(Application::Get().GetRenderer(), surface);
		SDL_FreeSurface(surface);

		SDL_Surface* iconSurface = IMG_Load("../Resources/Icons/FileIcon.png");
		m_fileIcon               = SDL_CreateTextureFromSurface(Application::Get().GetRenderer(), iconSurface);
		SDL_FreeSurface(iconSurface);
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

		static float padding       = 16.f;
		static float thumbnailSize = 96.f;
		float cellSize             = thumbnailSize + padding;

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columCount   = (int)(panelWidth / cellSize);
		if (columCount < 1)
		{
			columCount = 1;
		}

		ImGui::Columns(columCount, 0, false);

		for (auto dirEntry : fs::directory_iterator(m_currentDirectory))
		{
			const auto& path  = dirEntry.path();
			auto relativePath = fs::relative(path, s_AssetPath);
			auto filenameStr  = relativePath.filename().stem().string();

			// SDL_Texture* icon = dirEntry.is_directory() ? m_dirIcon : m_fileIcon;
			SDL_Texture* icon = nullptr;
			if (dirEntry.is_directory())
			{
				icon = m_dirIcon;
			}
			else if (dirEntry.path().extension() == ".png")
			{
				auto imageTexture = AssetManager::Inst()->GetTexture(dirEntry.path().stem().string());
				icon              = imageTexture != nullptr ? imageTexture : m_fileIcon;
			}
			else
			{
				icon = m_fileIcon;
			}
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon, { thumbnailSize, thumbnailSize });
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (dirEntry.is_directory())
				{
					m_currentDirectory /= dirEntry.path().filename();
				}
			}
			ImGui::TextWrapped(filenameStr.c_str());

			ImGui::NextColumn();
		}

		ImGui::Columns(1);

		ImGui::End();
	}
} // namespace cedar
