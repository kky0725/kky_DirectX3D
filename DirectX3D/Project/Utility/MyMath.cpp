#include "Framework.h"
#include "MyMath.h"

float MyMath::Clamp(const float& value, float minValue, float maxValue)
{

	return max(minValue, min(maxValue, value));
}

float MyMath::Saturate(const float& value)
{
	return Clamp(value, 0.0f, 1.0f);
}
