#include "header.hlsli"

GBufferOutput main(LightVertexOutPut input)
{
	LightMaterial material = GetLightMaterial(input);
	
	
	
	return PackGBuffer(material.diffuseColor.rgb, material.normal.rgb, material.specularIntensity.r);
}