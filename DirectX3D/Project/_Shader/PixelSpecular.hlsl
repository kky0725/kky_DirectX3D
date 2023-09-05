#include "header.hlsli"

struct VertexOutPut
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 viewDir : VIEWDIR;
};

float4 main(VertexOutPut input) : SV_TARGET
{
	float3 L = normalize(lightDirection);
	float diffuseIntensity = dot(input.normal, -L);
	
	float4 albedo = diffuseMap.Sample(samp, input.uv);
	
	float4 diffuse = albedo * diffuseIntensity;
	
	//specular
	
	float4 specular = 0;
	float3 reflection = normalize(reflect(L, input.normal));
	
	specular = dot(-reflection, input.viewDir);
	
	specular = pow(specular, 24.0f);
	
	return diffuse + specular;
}