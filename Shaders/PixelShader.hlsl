struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

float4 PSMain(PS_IN input) : SV_Target
{
	return input.col;
}