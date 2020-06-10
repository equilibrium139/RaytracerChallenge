#include "Lighting.h"

Color Lighting(const Material& mat, const Point& point, const PointLight& light, const Vector& eye, const Vector& normal)
{
	Color effectiveColor = mat.color * light.intensity;
	Vector vectorToLight = Normalize(light.position - point);
	Color ambient = effectiveColor * mat.ambient;
	float lightNormalDot = Dot(vectorToLight, normal);
	if (lightNormalDot < 0.0f)
	{
		return ambient;
	}
	else
	{
		Color diffuse = effectiveColor * mat.diffuse * lightNormalDot;
		Vector lightReflected = Reflect(-vectorToLight, normal);
		float dotVectorToEyeLightReflected = Dot(eye, lightReflected);
		if (dotVectorToEyeLightReflected < 0.0f)
		{
			return ambient + diffuse;
		}
		else
		{
			float factor = std::pow(dotVectorToEyeLightReflected, mat.shininess);
			Color specular = light.intensity * mat.specular * factor;
			return ambient + diffuse + specular;
		}
	}
}