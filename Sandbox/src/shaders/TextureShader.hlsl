struct OutputVertex
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

Texture2D Texture : register(t0);

SamplerState simpleSampler : register(s0);

float4 main(OutputVertex v) : SV_TARGET
{ 
    return Texture.Sample(simpleSampler, v.uv);
}