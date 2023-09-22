#include "header.hlsli"

cbuffer BrushBuffer : register(b10)
{
	int		type;
	float3	location;
	
	float	range;
	float3	color;
}

struct VertexOutPut
{
	float4 pos		: SV_POSITION;
	float2 uv		: UV;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float3 binormal	: BINORMAL;
	float3 viewDir	: VIEWDIR;
	
	float3 worldPos : POSITIONT;
};

float3 SetBrushColor(float3 pos)
{
	if(type == 0)
	{
		float x = pos.x - location.x;
		float z = pos.z - location.z;
		
		float distance = sqrt(pow(x, 2) + pow(z, 2));
		
		if(distance <= range)
			return color;
	}
	else if (type == 1)
	{
		float x = pos.x - location.x;
		float z = pos.z - location.z;
		
		if (abs(x) <= range && abs(z) <= range)
			return color;
	}
	
	return float3(0,0,0);
}

float4 main(VertexOutPut input) : SV_TARGET
{
	float3 L = normalize(lightDirection);
	
	float4 albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	if (hasDiffuseMap)
		albedo = diffuseMap.Sample(samp, input.uv);
	
	float3 T = normalize(input.tangent);
	float3 B = normalize(input.binormal);
	float3 N = normalize(input.normal);
	
	float3 normal = N;
	
	if (hasNormalMap)
	{
		float4 normalSample = normalMap.Sample(samp, input.uv);
		
		normal = normalSample * 2.0f - 1.0f;
		
		float3x3 TBN = float3x3(T, B, N);
		
		normal = normalize(mul(normal, TBN));
	}
	
	float diffuseIntensity = saturate(dot(normal, -L));
	
	//specular
	
	float specularIntensity = 0;
	float3 reflection = normalize(reflect(L, normal));
	
	specularIntensity = saturate(dot(-reflection, input.viewDir));
	
	float4 specularSample = float4(1, 1, 1, 1);

	if (hasSpecularMap)
		specularSample = specularMap.Sample(samp, input.uv);

	float4 specular = pow(specularIntensity, shininess) * specularSample * mSpecular;
	
	float4 diffuse = albedo * diffuseIntensity * mDiffuse;
	
	float4 ambient = albedo * ambientLight * mAmbinet;
	
	float4 brushColor = float4(SetBrushColor(input.worldPos), 1.0f);
	
	return diffuse + specular + ambient + brushColor;
}