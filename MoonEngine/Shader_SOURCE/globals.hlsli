

cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
}

//Material b1

cbuffer Grid : register(b2)
{
    float4 CameraPosition;
    float2 CameraScale;
    float2 Resolution;
}
cbuffer Time : register(b3)
{
    float4 DeltaTime;
}

cbuffer Debug : register(b4)
{
    float4 InterSect;
}

cbuffer Animator : register(b5)
{
    float2 SpriteLeftTop;
    float2 SpriteSize;
    float2 SpriteOffset;
    float2 AtlasSize;
    uint animationType;
}

cbuffer Flip : register(b6)
{
    uint FlipX;
}

Texture2D albedoTexture : register(t0);
Texture2D atlasTexture : register(t12);

SamplerState pointSampler : register(s0);
SamplerState anisotropicSampler : register(s1);
