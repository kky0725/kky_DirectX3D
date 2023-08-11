struct VertextOutPut
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

float4 main(VertextOutPut input) : SV_TARGET
{
    return input.color;
}