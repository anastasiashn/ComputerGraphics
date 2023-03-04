
struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

cbuffer CBuf
{
	matrix transform;
};

PS_IN VSMain( float4 pos : POSITION, float4 col : COLOR )
{
	PS_IN output = (PS_IN)0;
	
	output.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), transform);
	output.col = col;
	
	return output;
}