#include "header.hlsli"

VertexTexture main( VertexTexture input )
{
	input.pos = mul(input.pos, world);
	
	return input;
}