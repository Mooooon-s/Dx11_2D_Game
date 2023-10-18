#include "globals.hlsli"



struct GSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
};

Texture2D albedoTextureAlpha : register(t17);

float4 main(GSOut In) : SV_TARGET
{
    float4 Out = (float4) 0.0f;
    float4 color = (float4) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    float4 alpha = albedoTextureAlpha.Sample(anisotropicSampler,In.UV);
    float alphaValue = alpha.r;
    color = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), color, alphaValue);

    return color;

}