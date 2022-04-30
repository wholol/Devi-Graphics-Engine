#pragma once

// binding locations that are used by most drawables.
enum class TextureBindingLocations : int
{
	skyBox = 0,
	//PBR Material
	albedoMap = 0,
	roughnessMap,
	normalMap,
	aoMap,
	metallicMap,
	depthMap,
};