cbuffer World : register(b0)
{
	matrix world;
};

cbuffer View : register(b1)
{
	matrix view;
	matrix invView;
};

cbuffer Projection : register(b2)
{
	matrix projection;
};

cbuffer LightDirection : register(b0)
{
	float3 lightDirection;
	float padding;
	float4 ambientLight;
};

cbuffer MaterialBuffer : register(b1)
{
	float4 mDiffuse;
	float4 mSpecular;
	float4 mAmbinet;
	float4 mEmissive;
	
	int hasDiffuseMap;
	int hasSpecularMap;
	int hasNormalMap;
	int hasAlphaMap;
	
	float shininess;
};

struct Frame
{
	int clip;
	uint curFrame;
	float time;
	float speed;
};

struct Motion
{
	float takeTime;
	float tweenTime;
	float runningTime;
	float padding2;
	
	Frame cur, next;
};

cbuffer FrameBuffer : register(b3)
{
	Motion motion;
};

#define MAX_INSTANCE 128

cbuffer FrameInstancingBuffer : register(b4)
{
	Motion motions[MAX_INSTANCE];
};

Texture2DArray transforMap : register(t0);

struct VertexTexture
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexColor
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct VertexTextureNormal
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct VertexColorNormal
{
	float4 pos : POSITION;
	float4 color : COLOR;
	float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentAlpha
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 alpha : ALPHA;
};

struct VertexTextureNormalTangentBlend
{
	float4 pos		: POSITION;
	float2 uv		: UV;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float4 indices	: BLENDINDICES;
	float4 weights	: BLENDWEIGHT;
};

struct VertexInstancing
{
	float4 pos : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 indices : BLENDINDICES;
	float4 weights : BLENDWEIGHT;
	
	matrix transform : INSTANCE_TRANSFORM;
	uint index		 : INSTANCE_INDEX;
};

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);


SamplerState	samp : register(s0);

matrix SkinWorld(float4 indices, float4 weights)
{
	matrix transform = 0;
	matrix curAnim, nextAnim;
	matrix cur, next;
	
	float4 c0, c1, c2, c3;
	float4 n0, n1, n2, n3;
	
	int clipIndex[2];
	int curFrame[2];
	float time[2];
	
	clipIndex[0] = motion.cur.clip;
	curFrame[0] = motion.cur.curFrame;
	time[0] = motion.cur.time;
	
	clipIndex[1] = motion.next.clip;
	curFrame[1] = motion.next.curFrame;
	time[1] = motion.next.time;
	
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		c0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[0], clipIndex[0], 0));
		c1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[0], clipIndex[0], 0));
		c2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[0], clipIndex[0], 0));
		c3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[0], clipIndex[0], 0));
		
		cur = matrix(c0, c1, c2, c3);
		
		n0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[0] + 1, clipIndex[0], 0));
		n1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[0] + 1, clipIndex[0], 0));
		n2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[0] + 1, clipIndex[0], 0));
		n3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[0] + 1, clipIndex[0], 0));
		
		next = matrix(n0, n1, n2, n3);
		
		curAnim = lerp(cur, next, time[0]);
		
		
		[flatten]
		if (clipIndex[1] > -1)
		{
			c0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[1], clipIndex[1], 0));
			c1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[1], clipIndex[1], 0));
			c2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[1], clipIndex[1], 0));
			c3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[1], clipIndex[1], 0));
		
			cur = matrix(c0, c1, c2, c3);
		
			n0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[1] + 1, clipIndex[1], 0));
			n1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[1] + 1, clipIndex[1], 0));
			n2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[1] + 1, clipIndex[1], 0));
			n3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[1] + 1, clipIndex[1], 0));

			next = matrix(n0, n1, n2, n3);

			nextAnim = lerp(cur, next, time[1]);

			curAnim = lerp(curAnim, nextAnim, motion.tweenTime);
		}
		
		transform += mul(weights[i], curAnim);
	}
	
	return transform;
}

matrix SkinWorld(uint instanceIndex, float4 indices, float4 weights)
{
	matrix transform = 0;
	matrix curAnim, nextAnim;
	matrix cur, next;
	
	float4 c0, c1, c2, c3;
	float4 n0, n1, n2, n3;
	
	int clipIndex[2];
	int curFrame[2];
	float time[2];
	
	clipIndex[0] = motions[instanceIndex].cur.clip;
	curFrame[0] = motions[instanceIndex].cur.curFrame;
	time[0] = motions[instanceIndex].cur.time;
	
	clipIndex[1] = motions[instanceIndex].next.clip;
	curFrame[1] = motions[instanceIndex].next.curFrame;
	time[1] = motions[instanceIndex].next.time;
	
	[unroll]
	for (int i = 0; i < 4; i++)
	{
		c0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[0], clipIndex[0], 0));
		c1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[0], clipIndex[0], 0));
		c2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[0], clipIndex[0], 0));
		c3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[0], clipIndex[0], 0));
		
		cur = matrix(c0, c1, c2, c3);
		
		n0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[0] + 1, clipIndex[0], 0));
		n1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[0] + 1, clipIndex[0], 0));
		n2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[0] + 1, clipIndex[0], 0));
		n3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[0] + 1, clipIndex[0], 0));
		
		next = matrix(n0, n1, n2, n3);
		
		curAnim = lerp(cur, next, time[0]);
		
		
		[flatten]
		if (clipIndex[1] > -1)
		{
			c0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[1], clipIndex[1], 0));
			c1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[1], clipIndex[1], 0));
			c2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[1], clipIndex[1], 0));
			c3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[1], clipIndex[1], 0));
		
			cur = matrix(c0, c1, c2, c3);
		
			n0 = transforMap.Load(int4(indices[i] * 4 + 0, curFrame[1] + 1, clipIndex[1], 0));
			n1 = transforMap.Load(int4(indices[i] * 4 + 1, curFrame[1] + 1, clipIndex[1], 0));
			n2 = transforMap.Load(int4(indices[i] * 4 + 2, curFrame[1] + 1, clipIndex[1], 0));
			n3 = transforMap.Load(int4(indices[i] * 4 + 3, curFrame[1] + 1, clipIndex[1], 0));

			next = matrix(n0, n1, n2, n3);

			nextAnim = lerp(cur, next, time[1]);

			curAnim = lerp(curAnim, nextAnim, motions[instanceIndex].tweenTime);
		}
		
		transform += mul(weights[i], curAnim);
	}
	
	return transform;
}