#include "Header.hlsli"

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float3 origionPos : POSITION;
};

TextureCube cubeMap : register(t10);

float4 main(VertexOutput input) : SV_TARGET
{
	return cubeMap.Sample(samp, input.origionPos);
}