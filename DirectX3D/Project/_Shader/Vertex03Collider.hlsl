#include "header.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
};

struct VertexOutPut
{
	float4 pos : SV_POSITION;
};

VertexOutPut main(VertexInput input)
{
	VertexOutPut output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	return output;
}