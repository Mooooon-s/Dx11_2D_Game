

cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

cbuffer Time : register(b1)
{
    float4 DeltaTime;
}

cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}

cbuffer Animator : register(b4)
{
    float2 SpriteleftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 atlasSize;
}

cbuffer Debug : register(b3)
{
    float4 InterSect;
}

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);
