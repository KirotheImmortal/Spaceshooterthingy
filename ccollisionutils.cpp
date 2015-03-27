

#include "ccollisionutils.h"
#include <iostream>
float ShapeVsShape(Shape a, Shape b)
{

	a.position = a.position + a.origin;
	b.position = b.position + b.origin;

	if (a.type == Shape::eCircle && b.type == Shape::eCircle)
		return CircleVsCircle(a.circle, b.circle);
	if (a.type == Shape::eRect && b.type == Shape::eRect)
		return RectVsRect(a.rect, b.rect);

	if (a.type == Shape::ePlane && b.type == Shape::eRay)
		return  PlaneVsRay(a.plane, b.ray);
	if (a.type == Shape::eRay && b.type == Shape::ePlane)
		return  RayVsPlane(a.ray, b.plane);

	if (a.type == Shape::eRect && b.type == Shape::eCircle)
		return  RectVsCircle(a.rect, b.circle);
	if (a.type == Shape::eCircle && b.type == Shape::eRay)
		return  CircleVsRect(a.circle, b.rect);

	if (a.type == Shape::eRay && b.type == Shape::eRect)
		return  RayVsRect(a.ray, b.rect);
	if (a.type == Shape::eRect && b.type == Shape::eRay)
		return  RectVsRay(a.rect, b.ray);

	if (a.type == Shape::eCircle && b.type == Shape::ePlane)
		return CircleVsPlane(a.circle, b.plane);
	if (a.type == Shape::ePlane && b.type == Shape::eCircle)
		return PlaneVsCircle(a.plane, b.circle);

	if (a.type == Shape::eRect && b.type == Shape::ePlane)
	{
		return RectVsPlane(a.rect, b.plane);
	}
	if (a.type == Shape::ePlane && b.type == Shape::eRect)
	{
		return PlaneVsRect(a.plane, b.rect);
	}
	return -1;
	
}

float vec3Dot(vec3 a, vec3 b) { return (a.x*b.x) + (a.y*b.y) + (a.z*b.z); }
float vec3Length(vec3 a)	  {return sqrt(vec3Dot(a, a));}
float vec3Dist(vec3 a, vec3 b) { return vec3Length(a - b); }
float magnitude(vec3 a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
float angleBetween(vec3 a, vec3 b) 
{
	return acos(vec3Dot(a, b) / magnitude(b)*magnitude(b));
}



float CircleVsCircle(const Circle &a, const Circle &b)
{
	float dis = vec3Dist(a.position, b.position);
	if (dis < (a.radius + b.radius))
		return (a.radius + b.radius) - dis;
	else
		return -dis;
}
float RectVsRect( Rect a,  Rect b)
{
	a.max = a.max + a.position;
	a.min = a.min + a.position;

	b.max = b.max + b.position;
	b.min = b.min + b.position;

	if (a.min.x > b.max.x || b.min.x > a.max.x)
		return -1;
	if (a.min.y > b.max.y || b.min.y > a.max.y)
		return -1;

	float diffx1 = abs(a.min.x - a.max.x);
	float diffx2 = abs(b.min.x - b.max.x);

	float diffy1 = abs(a.min.y - a.max.y);
	float diffy2 = abs(b.min.y - b.max.y);

	return ((diffx1 < diffx2 ? diffx1 : diffx2)
		  + (diffy1 < diffy2 ? diffy1 : diffy2)) / 2;
}

float PointVsPlane(const Point &o, const Plane &p)
{
	return vec3Dot(p.normal, (o - p.position));
}

float PlaneVsRay(const Plane &p, const Ray &r)
{
	return RayVsPlane(r, p);
}
float RayVsPlane(const Ray &r, const Plane &p)
{
	return -PointVsPlane(r.position, p) / vec3Dot(p.normal, r.normal*r.length);
}

float PlaneVsCircle(const Plane &p, const Circle &c)
{
	return CircleVsPlane(c, p);
}
float CircleVsPlane(const Circle &c, const Plane &p)
{
	return c.radius - PointVsPlane(c.position, p);
	
}

float RectVsCircle(const Rect &r, const Circle &c)
{
	return CircleVsRect(c, r);
}
float CircleVsRect(const Circle &c, const Rect &r)
{
	vec3 rc = (r.min + r.max) * (.5f) + r.position;
	vec3 p = c.position - rc;

	vec3 point = {0,0,0};
	vec3 dim   = (r.max - r.min) * (0.5f);
	dim.z = 0;

	point.x = clamp(-dim.x,  dim.x, p.x);
	point.y = clamp(-dim.y,  dim.y, p.y);
	point.z = 0;

	float t = c.radius - vec3Length(point - p);
	
	if (t == c.radius)
	{
		vec3 minDiff = point - r.min;
		vec3 maxDiff = r.max - point;
		if (vec3Length(maxDiff) < vec3Length(minDiff))
			t = maxDiff.x < maxDiff.y ? maxDiff.x : maxDiff.y;
		
		else
			t = minDiff.x < minDiff.y ? minDiff.x : minDiff.y;

	}

	return t;
}

float RayVsCircle(const Ray &r, const Circle &c)
{
	return CircleVsRay(c, r);
}
float CircleVsRay(const Circle &c, const Ray &r)
{
														// (r.position - r.normal * r.length) = m(x1 - x2)

	vec3 cr = r.position - c.position;
	vec3 a = r.normal * r.length;
	float b;
	float t = ( vec3Length(cr) - c.radius - vec3Dist(cr, a) );

	if (t <  0 && vec3Dot(a, cr) > vec3Length(cr) - c.radius)
	{
		b = sqrt((vec3Length(cr) * vec3Length(cr)) + (vec3Dot(cr, a)*vec3Dot(cr, a)));	
		t = c.radius - b;
	}
	
	 

	
	


	return t;
}


float RayVsRect(const Ray &a, const Rect &e)
{
	return RectVsRay(e,a);
}
float RectVsRay(const Rect&e, const Ray &a)
{
	//vec3 TL = { e.min.x, e.min.y, 0 };				//Top left
	//vec3 TR = { e.max.x, e.min.y, 0 }; //Top Right
	//vec3 BL = { e.min.x, e.max.y, 0 };	//Bottom left
	//vec3 BR = { e.max.x, e.max.y, 0 };				//bottom right

	//if (vec3Dot(TL, a.normal) > 0) return 0;
	//if (vec3Dot(TR, a.normal) > 0) return 0;
	//if (vec3Dot(BL, a.normal) > 0) return 0;
	//if (vec3Dot(BL, a.normal) > 0) return 0;
	

	
	vec3 up		= {};
	vec3 down	= {};
	vec3 right	= {};
	vec3 left	= {};

	//CreatePlane(e.min, )


	return 0;
}

float PlaneVsRect(const Plane &p, const Rect &r)
{
	return RectVsPlane(r, p);
}
float RectVsPlane( const Rect &r, const Plane &p)
{
	auto topLeft = r.min + r.position - p.position;
	auto topRight = vec3Make(r.max.x, r.min.y, 0) + r.position- p.position;
	auto botLeft = vec3Make(r.min.x, r.max.y, 0) + r.position - p.position;
	auto botRight = r.max + r.position - p.position ;

	float ta = vec3Dot(topLeft, p.normal);
	float tb = vec3Dot(botRight, p.normal);
	float tc = vec3Dot(botLeft, p.normal);
	float td = vec3Dot(topRight, p.normal);

	if (ta > 0 && tb > 0 && tc > 0 && td > 0)
		/* ||(ta < 0 && tb < 0 && tc < 0 && td < 0))*/
	{
		return -1; //miss
	}

	return 1; //hit
}



float clamp(float min,float max,float value)
{
	if (value < min) return min;
	if (value > max) return max;
	else			 return value;
}
float distance(const vec3 &a, const vec3 &b)
{
	return sqrt((a.x - b.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Shape makeRect(float px, float py, float mx, float my, float Mx, float My)
{
	Shape r;
	r.type = Shape::eRect;

	r.rect.position = vec3Make(px, py, 0);
	r.rect.min = vec3Make(mx, my, 0) + r.rect.position;
	r.rect.max = vec3Make(Mx, My, 0) + r.rect.position;

	return r;
}
Shape makeRay(float px, float py, float nx, float ny, float length)
{
	Shape r;
	r.type = Shape::eRay;

	r.ray.position.x = px;
	r.ray.position.y = py;
	r.ray.position.z = 0;
	r.ray.normal.x;
	r.ray.normal.y;
	r.ray.normal.z = 0;
	r.ray.length = length;
	r.ray.normal.x = nx;
	r.ray.normal.y = ny;
	r.ray.normal.z = 0;
	return r;
}
Shape makePlane(float px, float py, float nx, float ny)
{
	Shape r;
	r.type = Shape::ePlane;

	r.plane.position.x = px;
	r.plane.position.y = py;
	r.plane.position.z = 0;
	r.plane.normal.x = nx;
	r.plane.normal.y = ny;
	r.plane.normal.z = 0;

	r.plane.normal = normal(r.plane.normal);
	
	return r;
}
Shape makeCircle(float px, float py, float radius)
{
	Shape r;
	r.type = Shape::eCircle;
	
	r.circle.position.x = px;
	r.circle.position.y = py;
	r.circle.position.z = 0;

	r.circle.radius = radius;

	return r;
}

