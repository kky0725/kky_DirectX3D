#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
};

float4 main(VertexOutPut input) : SV_TARGET
{
	return mDiffuse;
}