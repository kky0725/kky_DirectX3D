#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	
	matrix prjection1 : PROJECTION;
	matrix invView : INVVIEW;
};

struct SurfaceData
{
	float  linearDepth;
	float3 color;
	float3 normal;
	float  specInt;
	float  specPow;
};

static const float2 arrBasePos[4] =
{
	float2(-1.0f, +1.0f),
	float2(+1.0f, +1.0f),
	float2(-1.0f, -1.0f),
	float2(+1.0f, -1.0f)
};

VertexOutPut main(uint vertexID : SV_VertexID)
{
	VertexOutPut output;

	output.pos = float4(arrBasePos[vertexID].xy, 0.0f, 1.0f);
	output.uv = output.pos.xy;
	output.prjection1 = projection;
	output.invView = invView;
	
	return output;
}