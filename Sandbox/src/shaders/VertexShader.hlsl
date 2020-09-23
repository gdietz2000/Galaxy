struct Vertex
{
    float2 pos : POSITION;
};

struct Output
{
    float4 pos : SV_Position;
};

Output main( Vertex v ) : SV_POSITION
{
    Output ov = (Output) 0;
    ov.pos = float4(v.pos, 0, 1);
    return ov;
}