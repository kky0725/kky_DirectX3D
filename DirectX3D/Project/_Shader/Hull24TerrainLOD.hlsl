#include "header.hlsli"

struct CHullOutput
{
	float	edgeTessFactor[4]	: SV_TessFactor;
	float insideTessFactor[2]	: SV_InsideTessFactor;
};

cbuffer EdgeInfo : register(b10)
{
	float minDistance;
	float maxDistance;
	float minQuality;
	float maxQuality;
}

float CalculateTessFactor(float3 pos)
{
	float Distance = distance(pos, invView._41_42_43);
	float factor = saturate((Distance - minDistance) / (minDistance - maxDistance));
	
	return lerp(minQuality, maxQuality, factor);
}

#define NUM_CONTROL_POINTS 4

CHullOutput CHS(InputPatch<VertexTexture, NUM_CONTROL_POINTS> input)
{
	CHullOutput output;

	float3 edges[4];
	
	edges[0] = (input[0].pos + input[2].pos).xyz * 0.5f;
	edges[1] = (input[0].pos + input[1].pos).xyz * 0.5f;
	edges[2] = (input[1].pos + input[3].pos).xyz * 0.5f;
	edges[3] = (input[2].pos + input[3].pos).xyz * 0.5f;
	
	output.edgeTessFactor[0] = CalculateTessFactor(edges[0]);
	output.edgeTessFactor[1] = CalculateTessFactor(edges[1]);
	output.edgeTessFactor[2] = CalculateTessFactor(edges[2]);
	output.edgeTessFactor[3] = CalculateTessFactor(edges[3]);
	
	float center = (edges[0] + edges[2]) * 0.5f;
	
	output.insideTessFactor[0] = CalculateTessFactor(center);
	output.insideTessFactor[1] = CalculateTessFactor(center);

	return output;
}

struct HullOutput
{
	float4 pos : POSITION;
	float2 uv  : UV;
};

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("CHS")]
HullOutput main(InputPatch<VertexTexture, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID)
{
	HullOutput output;

	output.pos = input[i].pos;
	output.uv = input[i].uv;

	return output;
}
