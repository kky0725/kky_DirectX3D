cbuffer World : register(b0)
{
    matrix world;
};

cbuffer View : register(b1)
{
    matrix view;
};

cbuffer Projection : register(b2)
{
    matrix projection;
};

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexOutPut
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

VertexOutPut main(VertexInput input)
{
    VertexOutPut output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}