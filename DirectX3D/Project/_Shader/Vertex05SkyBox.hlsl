#include "Header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float3 originPos : POSITION;
};

VertexOutPut main(VertexTexture input)
{
	VertexOutPut output;
 
	output.originPos = input.pos.xyz;
	
	output.pos.xyz = mul(input.pos.xyz, (float3x3) view);
	output.pos.w = 1.0f;
	output.pos = mul(output.pos, projection);
 
	return output;
}
