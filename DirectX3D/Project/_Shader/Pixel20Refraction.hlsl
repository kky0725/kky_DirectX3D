#include "header.hlsli"

struct VertextOutput
{
	float4 pos			: SV_POSITION;
	float2 uv			: UV;
	float4 reflectPos	: POSITION;
};

Texture2D refractionMap			: register(t11);
Texture2D refractionNormalMap	: register(t12);

cbuffer WaterBuffer : register(b10)
{
	float4 color;
	
	float waveTime;
	float waveSpeed;
	float waveScale;
	float waveShininess;
	
	float fresnel;
}

float4 main(VertextOutput input) : SV_TARGET
{
	float2 uv;
	
	uv.x = +input.reflectPos.x / input.reflectPos.w * 0.5f + 0.5f;
	uv.y = -input.reflectPos.y / input.reflectPos.w * 0.5f + 0.5f; //화면 좌표계를 엔디시 좌표로 변경하는 과정

	input.uv += waveTime * waveSpeed;
	
	float4 normal = refractionNormalMap.Sample(samp, input.uv) * 2.0f - 1.0f;
	uv += normal.xy * waveScale;
	
	return refractionMap.Sample(samp, uv) * color;
}