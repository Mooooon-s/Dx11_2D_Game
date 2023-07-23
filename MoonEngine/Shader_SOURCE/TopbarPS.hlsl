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
    float4 color = albedoTexture.Sample(anisotropicSampler, In.UV);
    float4 alpha = tex.Sample(anisotropicSampler, In.UV);
    
    float alphaValue = alpha.r;
    color = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), color, alphaValue);
    
    return color;
}