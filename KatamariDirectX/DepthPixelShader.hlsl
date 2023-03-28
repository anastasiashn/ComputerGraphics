struct PS_INPUT
{
    float4 positionWVP : SV_POSITION;
    float4 position : POSITION;
};
Texture2D objTexture : register(t0);
SamplerState objSamplerState : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	// �������� �������� ������� ������� ���� Z ������� ������� �� ���������� ���������� W
    float depthValue = input.position.z / input.position.w;

    return float4(depthValue, depthValue, depthValue, 1.0f);
}