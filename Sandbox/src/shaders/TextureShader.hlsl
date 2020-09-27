struct OutputVertex
{
    float4 position : SV_Position;
};

Texture2D Texture : register(t0);

SamplerState simpleSampler : register(s0);

float4 main(OutputVertex v) : SV_TARGET
{ 
    return Texture.Sample(simpleSampler, v.position.xy * 0.5f + 0.5f);
}