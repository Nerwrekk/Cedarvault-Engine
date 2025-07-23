#include "MeanScript/Primitives/MeanString.h"

namespace Mean
{
	const char* MeanString_GetString(MeanString* meanStr)
	{
		return meanStr ? meanStr->GetNativeString() : "";
	}

	void MeanString_SetString(MeanString* meanStr, const char* newString)
	{
		if (meanStr)
		{
			meanStr->SetString(newString);
		}
	}

	size_t MeanString_GetSize(MeanString* meanStr)
	{
		return meanStr ? meanStr->GetSize() : 0;
	}
} // namespace Mean