struct VSIn
{
    row_major float4x4 Transform : TEXCOORD0;
    float4 Color : TEXCOORD1;
    float2 TexPos[4] : TEXCOORD2;
    float TexInd : TEXCOORD3;
};

struct VSOut
{
    float4 Position : SV_Position;
    float4 Color : TEXCOORD0;
    float2 TexCoord : TEXCOORD1;
    float TexIndex : TEXCOORD2;
};

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

VSOut main(VSIn input, uint id : SV_VertexID)
{
    uint vert = INDICES[id % 6];
    float3 coord = VERTS[vert];
    VSOut output;
    output.Position = mul(mul(float4(coord, 1.0f), input.Transform), ViewProjectionMatrix);
    output.TexCoord = input.TexPos[vert];
    output.Color = input.Color;
    output.TexIndex = input.TexInd;

    return output;
}