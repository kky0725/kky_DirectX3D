#include "header.hlsli"

struct DomainOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 main(DomainOutput input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv);
}