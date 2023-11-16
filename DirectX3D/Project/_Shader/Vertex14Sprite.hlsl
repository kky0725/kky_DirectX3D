#include "header.hlsli"

struct VertexOutput // Geometry Input
{
	float4 pos		: POSITIONT0;
	float2 size		: SIZE;
	matrix invView	: POSITIONT1;
	matrix view		: VIEW;
	matrix proj		: PROJECTION;
};

VertexOutput main( VertexTexture input )
{
	VertexOutput output;
	
	output.pos		= input.pos;
	output.size		= input.uv;
	output.invView	= invView;
	output.view		= view;
	output.proj		= projection;
	
	return output;
}