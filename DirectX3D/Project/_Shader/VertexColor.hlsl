#include "Header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

VertexOutPut main(VertexColorNormal input)
{
	VertexOutPut output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.color = input.color;
	
	output.normal = normalize(mul(input.normal, (float3x3) world));

	return output;
}