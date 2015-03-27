#pragma once

#include "cmathutils.h"

struct Circle	{vec3 position;float radius;};
struct Rect		{vec3 position, min, max;};
struct Plane	{vec3 position, normal;};
struct Ray		{vec3 position, normal; float length;};

typedef vec3 Point;

struct Shape
{
	enum Type {eNothing, eCircle, eRect, ePlane, eRay} type;
	vec3	origin;
	union
	{
		vec3	position;
		Circle	circle;
		Rect	rect;
		Plane	plane;
		Ray		ray;
	};
};

Shape makeRect(float px, float py, float mx, float my, float Mx, float My);
Shape makeRay(float px, float py, float nx, float ny, float length);
Shape makePlane(float px, float py, float nx, float ny);
Shape makeCircle(float px, float py, float radius);

float clamp(float min, float max, float value);

float ShapeVsShape(Shape a, Shape b);

float CircleVsCircle(const Circle &a, const Circle &b);
float RectVsRect( Rect a,  Rect b);

float PlaneVsRay(const Plane &p, const Ray &r);
float RayVsPlane(const Ray &r, const Plane &p);

float PlaneVsCircle(const Plane &p, const Circle &c);
float CircleVsPlane(const Circle &c, const Plane &p);

float RectVsCircle(const Rect &r, const Circle &c);
float CircleVsRect(const Circle &c, const Rect &r);

float RayVsCircle(const Ray &r, const Circle &c);
float CircleVsRay(const Circle &c, const Ray &r);

float RayVsRect(const Ray &a, const Rect &e);
float RectVsRay(const Rect&e, const Ray &a);

float RectVsPlane(const Rect &r, const Plane &p);
float PlaneVsRect(const Plane &p, const Rect &r);

