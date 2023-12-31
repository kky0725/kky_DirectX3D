#include "Header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 viewDir : VIEWDIR;
};

VertexOutPut main(VertexTextureNormalTangentBlend input)
{
	VertexOutPut output;

	matrix transform = mul(SkinWorld(input.indices, input.weights), world);
	
	output.pos = mul(input.pos, transform);
	
	float3 cameraPos = invView._41_42_43;
	
	output.viewDir = normalize(output.pos.xyz - cameraPos);
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = normalize(mul(input.normal, (float3x3) world));
	output.tangent = normalize(mul(input.tangent, (float3x3) world));
	
	output.binormal = cross(output.normal, output.tangent);

	return output;
}