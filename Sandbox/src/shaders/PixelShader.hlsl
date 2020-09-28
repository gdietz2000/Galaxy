
struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

float4 main(Output ov) : SV_TARGET
{
    return ov.color;
}