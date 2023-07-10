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

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    float2 inversUv = float2(In.UV.x,In.UV.y*-1);
    uv.x -= DeltaTime.x / 4.0f;
    
    color = albedoTexture.Sample(pointSampler, uv);
    //float4 b = tex2.Sample(pointSampler,inversUv);
    color.rgb = float4(0.0f, 0.5f, 1.0f, 0.5f);
    return color;
}