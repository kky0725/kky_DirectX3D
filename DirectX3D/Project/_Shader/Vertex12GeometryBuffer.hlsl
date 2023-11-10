#include "Header.hlsli"

LightVertexOutPut main(VertexTextureNormalTangentBlend input)
{
	LightVertexOutPut output;

	matrix transform;
	
	[branch]
	if (hasAnimation)
		transform = mul(SkinWorld(input.indices, input.weights), world);
	else
		transform = world;
	
	output.pos = mul(input.pos, transform);
	
	///////////////////////////
	
	output.viewPos = invView._41_42_43;
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = normalize(mul(input.normal, (float3x3) transform));
	output.tangent = normalize(mul(input.tangent, (float3x3) transform));
	
	output.binormal = cross(output.normal, output.tangent);

	return output;
}