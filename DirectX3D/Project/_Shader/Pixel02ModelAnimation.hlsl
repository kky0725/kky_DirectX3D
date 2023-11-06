#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 viewDir : VIEWDIR;
};

float4 main(LightVertexOutPut input) : SV_TARGET
{
	LightMaterial material = GetLightMaterial(input);
	
	float4 ambient = CalculateAmbient(material);
	
	return ambient;
}