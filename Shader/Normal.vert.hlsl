struct Data
{
    row_major float4x4 Transform;
    float4 Color;
    float2 TexPos[4];
    float TexInd;
};

struct Output
{
    float4 Position : SV_Position;
    float4 Color : TEXCOORD0;
    float2 TexCoord : TEXCOORD1;
    float TexIndex : TEXCOORD2;
};

StructuredBuffer<Data> DataBuffer : register(t0, space0);

cbuffer UniformBlock : register(b0, space1)
{
    row_major float4x4 ViewProjectionMatrix : packoffset(c0);
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
    Data sprite = DataBuffer[id / 6];
    Output output;

    float3 coord = VERTS[vert];
    output.Position = mul(ViewProjectionMatrix, mul(sprite.Transform, float4(coord, 1.0f)));
    output.TexCoord = sprite.TexPos[vert];
    output.Color = sprite.Color;
    output.TexIndex = sprite.TexInd;

    return output;
}