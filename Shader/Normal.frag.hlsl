Texture2DArray<float4> Texture : register(t0, space2);
SamplerState Sampler : register(s0, space2);

struct Input
{
    float TexIndex : TEXCOORD0;
    float2 TexCoord : TEXCOORD1;
    float4 Color : TEXCOORD2;
};

float4 main(Input input) : SV_Target0
{
    return input.Color * Texture.Sample(Sampler, float3(input.TexCoord, input.TexIndex));
}