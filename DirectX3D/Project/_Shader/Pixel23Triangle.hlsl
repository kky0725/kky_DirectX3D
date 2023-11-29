#include "header.hlsli"

struct DomainOutput
{
	float4 pos : SV_POSITION;
};

float4 main(DomainOutput input) : SV_TARGET
{
	
	return float4(1, 1, 0, 1);
}