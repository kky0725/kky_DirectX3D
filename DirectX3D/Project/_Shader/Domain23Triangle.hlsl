struct DomainOutput
{
	float4 pos  : SV_POSITION;
};

struct HullOutput
{
	float4 pos : POSITION;
};

struct CHullOutput
{
	float edgeTessFactor[3] : SV_TessFactor;
	float insideTessFactor : SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
DomainOutput main(CHullOutput input, float3 domain : SV_DomainLocation, const OutputPatch<HullOutput, NUM_CONTROL_POINTS> patch)
{
DomainOutput Output;

	Output.pos= float4
	(
		patch[0].pos.xyz * domain.x +
		patch[1].pos.xyz * domain.y +
		patch[2].pos.xyz * domain.z,
		1
	);

	return Output;
}
