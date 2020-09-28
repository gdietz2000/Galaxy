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

Output main( Vertex v )
{
    Output ov = (Output) 0;
    ov.pos = float4(v.pos, 1);
    ov.uv = v.uv;
    ov.color = v.color;
    return ov;
}