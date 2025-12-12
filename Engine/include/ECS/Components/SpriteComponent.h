#pragma once

#include "Common/SDL_Wrapper.h"
#include "MeanScript/Primitives/MeanString.h"
#include "Common/Core.h"
#include "Common/AssetManager.h"
#include "Common/Gameplay.h"

#include <string>
#include <glm/glm.hpp>

namespace cedar
{
	struct CEDAR_API SpriteComponent
	{
		DECL_TYPE_NAME(SpriteComponent)

		uint32_t ZIndex;
		Mean::MeanString TextureId;

		SpriteComponent(std::string textureId = "", uint32_t zIndex = 0)
		{
			TextureId    = Mean::MeanString(textureId);
			this->ZIndex = zIndex;
		}
	};

} // namespace cedar
