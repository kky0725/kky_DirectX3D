#include "header.hlsli"

struct CHullOutput
{
	float	edgeTessFactor[3]	: SV_TessFactor;
	float insideTessFactor		: SV_InsideTessFactor;
};

cbuffer TessFactor : register(b10)
{
	float3 edges;
	float inside;
}

#define NUM_CONTROL_POINTS 3

CHullOutput CHS(InputPatch<Vertex, NUM_CONTROL_POINTS> input)
{
	CHullOutput output;

	output.edgeTessFactor[0] = edges[0];
	output.edgeTessFactor[1] = edges[1];
	output.edgeTessFactor[2] = edges[2];
	output.insideTessFactor = inside;

	return output;
}

struct HullOutput
{
	float4 pos : POSITION;
};

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CHS")]
HullOutput main(InputPatch<Vertex, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID)
{
	HullOutput output;

	output.pos = input[i].pos;

	return output;
}
