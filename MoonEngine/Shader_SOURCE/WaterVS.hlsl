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

cbuffer Transform : register(b0)
{
    row_major matrix _World;
    row_major matrix _View;
    row_major matrix _Projection;
    //float4 Position;
}


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    float4 world = mul(float4(In.Pos, 1.0f), _World);
    float4 view = mul(world, _View);
    float4 projection = mul(view, _Projection);
    Out.Pos = projection;
    Out.Color = In.Color;
    Out.UV = In.UV;

    return Out;
}