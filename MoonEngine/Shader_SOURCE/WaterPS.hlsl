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

cbuffer Time : register(b2)
{
    float4 time;
}

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    float2 uv = In.UV;
    float2 inversUv = float2(In.UV.x,In.UV.y*-1);
    uv.x -= time.x /4.0f;
    
    color = tex.Sample(pointSampler, uv);
    float4 b = tex2.Sample(pointSampler,inversUv);
    color.rgb = float4(0.0f, 0.5f, 1.0f, 0.5f);
    return b* color;
}