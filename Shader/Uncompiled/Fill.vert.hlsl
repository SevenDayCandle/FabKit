struct Data
{
    float TexInd;
    float2 TexPos[4];
    float4 Color;
    float4x4 Transform;
};

struct Output
{
    float4 Color : TEXCOORD0;
    float4 Position : SV_Position;
};

StructuredBuffer<Data> DataBuffer : register(t0, space0);

cbuffer UniformBlock : register(b0, space1)
{
    float4x4 ViewProjectionMatrix : packoffset(c0);
};

static const uint INDICES[6] = { 0, 1, 2, 0, 2, 3 };
static const float3 VERTS[4] =
{
    { -0.5, -0.5, 0 },
    { 0.5, -0.5, 0 },
    { 0.5, 0.5, 0 },
    { -0.5, 0.5, 0 }
};
Output main(uint id : SV_VertexID)
{
    uint vert = INDICES[id % 6];
    Data data = DataBuffer[id / 6];
    Output output;
    
    float3 coord = VERTS[vert];
    output.Color = data.Color;
    output.Position = mul(ViewProjectionMatrix, mul(data.Transform, float4(coord, 1.0f)));
    return output;
}