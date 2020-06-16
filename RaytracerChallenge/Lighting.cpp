#include "Lighting.h"

Color Lighting(const Material& mat, const Point& point, const PointLight& light, 
	const Vector& eye, const Vector& normal, bool inLighting)
{
	Color effectiveColor = mat.color * light.intensity;
	Vector vectorToLight = Normalize(light.position - point);
	Color ambient = effectiveColor * mat.ambient;
	float lightNormalDot = Dot(vectorToLight, normal);
	if (lightNormalDot < 0.0f || inLighting)
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

Color ShadeHit(const World& w, const IntersectionData& d)
{
	return Lighting(d.object->mat, d.overPoint, w.light, d.eyeVec, d.normal, IsShadowed(w, d.overPoint));
}
