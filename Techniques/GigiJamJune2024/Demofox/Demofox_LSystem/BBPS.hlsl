// Unnamed technique, shader BBPS
/*$(ShaderResources)*/

struct PSInput // AKA VSOutput
{
	float4 position   : SV_POSITION;
	float3 color      : TEXCOORD0;
};

struct PSOutput
{
	float4 colorTarget : SV_Target0;
};

PSOutput main(PSInput input)
{
	PSOutput ret = (PSOutput)0;
	ret.colorTarget = float4(input.color, 1.0f);
	return ret;
}