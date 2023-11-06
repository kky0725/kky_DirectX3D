#include "header.hlsli"

float4 main(LightVertexOutPut input) : SV_TARGET
{
	LightMaterial material = GetLightMaterial(input);
	
	float4 ambient = CalculateAmbient(material);
	float4 color = CalculateDirectional(material, lights[0]);
	
	return ambient + color;
}