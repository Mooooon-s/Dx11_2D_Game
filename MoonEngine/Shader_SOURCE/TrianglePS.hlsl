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

Texture2D tex : register(t0);
SamplerState smaplerState : register(s0);

float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float) 0.0f;
    color = tex.Sample(smaplerState, In.UV);
    
    return color;
}