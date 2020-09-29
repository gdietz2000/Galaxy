struct Vertex
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

struct Output
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

cbuffer ModelViewProjection : register(b0)
{
    float4x4 mvp;
}

Output main( Vertex v )
{
    Output ov = (Output) 0;
    ov.pos = mul(float4(v.pos, 1), mvp);
    ov.uv = v.uv;
    ov.color = v.color;
    return ov;
}