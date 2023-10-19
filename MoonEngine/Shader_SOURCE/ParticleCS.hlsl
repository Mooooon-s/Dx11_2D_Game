#include "globals.hlsli"
RWStructuredBuffer<Particle> ParticleBuffer : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBuffer : register(u1);

[numthreads(128, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    if (elementCount <= DTid.x)
        return;
    
    
    if (ParticleBuffer[DTid.x].active == 0)
    {
        while (0 < ParticleSharedBuffer[0].ActiveSharedCount)
        {
            int origin = ParticleSharedBuffer[0].ActiveSharedCount;
            int exchange = origin - 1;
            
            // 쓰레드 동기화 Interlock 관련 함수
            //InterlockedExchange(ParticleSharedBuffer[0].ActiveSharedCount
            //    , exchange, exchange);
            
            InterlockedCompareExchange(ParticleSharedBuffer[0].ActiveSharedCount
                , origin, exchange, exchange);
            
            if (origin == exchange)
            {
                ParticleBuffer[DTid.x].active = 1;
                break;
            }
        }
        
        if (ParticleBuffer[DTid.x].active == 1)
        {
            // 랜덤값으로 위치와 방향을 설정한다.
            // 샘플링을 시도할 UV 를 계산한다.
            float4 vRandom = (float4) 0.f;

            float2 vUV = float2((float) DTid.x / elementCount, 0.5f);
            vUV.x += elapsedTime;
            vUV.y += sin((vUV.x + elapsedTime) * 3.141592f + 2.f * 10.f) * 0.5f;

            vRandom = float4
            (
                  GaussianBlur(vUV + float2(0.f, 0.f)).x
                , GaussianBlur(vUV + float2(0.1f, 0.f)).x
                , GaussianBlur(vUV + float2(0.2f, 0.f)).x
                , GaussianBlur(vUV + float2(0.3f, 0.f)).x
            );
            
            float3 randomDirection = float3(vRandom.x * 1.0f, abs(vRandom.y) * -1.0f , vRandom.z * 4.0f);
            
            ParticleBuffer[DTid.x].position.xy = ParticleSharedBuffer[0].position.xy + vRandom.xy * 1.0f;
            ParticleBuffer[DTid.x].position.x -= 0.65f;
            ParticleBuffer[DTid.x].position.y -= 0.5f;
            ParticleBuffer[DTid.x].position.z = ParticleSharedBuffer[0].position.z-0.01f;
            ParticleBuffer[DTid.x].direction.xzy = normalize(randomDirection);

        }
    }
    else
    {
        ParticleBuffer[DTid.x].position
           += ParticleBuffer[DTid.x].direction * ParticleBuffer[DTid.x].speed * deltaTime;
        ParticleBuffer[DTid.x].time += deltaTime;
        if (ParticleBuffer[DTid.x].endTime < ParticleBuffer[DTid.x].time)
        {
            ParticleBuffer[DTid.x].active = 0;
            ParticleBuffer[DTid.x].time = 0;
        }
            
        // 시간을 체크해서 일정 시간(랜덤)이 지나면
        // active = 0;
    }

}