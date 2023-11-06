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
	float diffuseIntensity = saturate(dot(input.normal, -L));
	
	float4 albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	if(hasDiffuseMap)
		albedo = diffuseMap.Sample(samp, input.uv);
	
	//specular
	
	float specularIntensity = 0;
	float3 reflection = normalize(reflect(L, input.normal));
	
	specularIntensity = saturate(dot(-reflection, input.viewDir));
	
	float4 specularSample = float4(1, 1, 1, 1);

	if(hasSpecularMap)
		specularSample =  specularMap.Sample(samp, input.uv);
	
	float4 specular = pow(specularIntensity, shininess) * specularSample * mSpecular;
	
	float4 diffuse = albedo * diffuseIntensity * mDiffuse;
	
	float4 ambient = albedo * float4(ambientLight, 1.0f) * mAmbinet;
	
	return diffuse + specular + ambient;
}