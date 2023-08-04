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

Texture2D alphaTex : register(t13);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    
    color = albedoTexture.Sample(anisotropicSampler, In.UV);
    float4 alpha = alphaTex.Sample(anisotropicSampler, In.UV);
    
    
    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset)
                + (AtlasSize * In.UV);
    
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        if(FlipX==0)
        {
            color = atlasTexture.Sample(anisotropicSampler, UV);
            alpha = alphaTex.Sample(anisotropicSampler, UV);
        }
        else if (FlipX==1)
        {
            UV.x *= -1;
            color = atlasTexture.Sample(anisotropicSampler, UV);
            alpha = alphaTex.Sample(anisotropicSampler, UV);
        }
    }
    float alphaValue = alpha.r;
    color = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), color, alphaValue);
    color *= lightsAttribute[0].color;
    return color;
}