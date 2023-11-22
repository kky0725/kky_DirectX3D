#include "header.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
	
	matrix transform : INSTANCE_TRANSFORM;
	float4 color : INSTANCE_COLOR;
};

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	
	float4 color : COLOR;
};

VertexOutPut main(VertexInput input)
{
	VertexOutPut output;

	output.pos = mul(input.pos, input.transform);
	output.pos = mul(output.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.color = input.color;
	
	return output;
}