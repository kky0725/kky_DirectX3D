#include "header.hlsli"

struct VertextOutput
{
	float4 pos			: SV_POSITION;
	float2 uv			: UV;
	float4 reflectPos	: POSITION;
};



VertextOutput main(VertexTexture input)
{
	VertextOutput output;
	
	output.pos = mul( input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = input.uv;
	
	output.reflectPos = output.pos;
	
	return output;
}