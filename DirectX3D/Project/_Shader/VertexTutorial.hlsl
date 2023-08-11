cbuffer WVP : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

struct VertexInput
{
    float4 pos   : POSITION;
    float4 color : COLOR;
};

struct VertextOutPut
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

VertextOutPut main( VertexInput input)
{
    VertextOutPut output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = input.color;
    
	return output;
}