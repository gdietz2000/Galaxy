struct Vertex
{
    float2 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct Output
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

Output main( Vertex v )
{
    Output ov = (Output) 0;
    ov.pos = float4(v.pos, 0, 1);
    ov.uv = v.uv;
    return ov;
}