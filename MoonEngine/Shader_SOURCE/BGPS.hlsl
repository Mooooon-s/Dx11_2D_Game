#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

Texture2D tex : register(t1);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    float4 l = (float) 0.0f;
    l = tex.Sample(anisotropicSampler, In.UV);
    return l;
}