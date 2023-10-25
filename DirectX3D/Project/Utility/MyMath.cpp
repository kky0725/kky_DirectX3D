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

float MyMath::Max(const float& value1, const float& value2, const float& value3)
{
	return max(max(value1, value2),value3);
}

float MyMath::Max(const Vector3& value)
{
	return Max(value.x, value.y, value.z);
}

float MyMath::Min(const float& value1, const float& value2, const float& value3)
{
	return min(min(value1, value2), value3);
}

float MyMath::Min(const Vector3 value)
{
	return Min(value.x, value.y, value.z);
}

float MyMath::Distance(Vector3& v1, Vector3& v2)
{
	return (v2 - v1).Length();
}
