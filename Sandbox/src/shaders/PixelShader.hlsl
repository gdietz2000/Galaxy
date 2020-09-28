
struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

cbuffer ColorValues : register(b0)
{
    float4 color;
}

float4 main(Output ov) : SV_TARGET
{
    return color;
}