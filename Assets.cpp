#include "Asset.h"
#include "Camera.h"
#include <cmath>

void Asset::drawLine(vec3 a, vec3 b, vec4 color)
{
	auto &camera = core(Camera).getCamera();
	glLoadIdentity();
	glMultMatrixf(camera.projection.m);
	glMultMatrixf(camera.view.m);
	glBegin(GL_LINE_LOOP);
	glColor4fv(color.v);
	glVertex3fv(a.v);
	glVertex3fv(b.v);
	glEnd();


}

void Asset::drawShape(Shape a, vec4 color)
{

	a.position = a.position + a.origin;

	if (a.type == Shape::eCircle)
	{
	vec3 line1 = { 0,0, 0 };
	float step = 2 * 3.145 / 25;
	vec3 line2 = { a.circle.position.x + a.circle.radius * cos(step), a.circle.position.y + a.circle.radius * sin(step), 0 };
	
		for (float theta = 0; theta < 2 * 3.145; theta += step)
		{
			line1.x = a.circle.position.x + a.circle.radius * cos(theta);
			line1.y = a.circle.position.y + a.circle.radius * sin(theta);

			drawLine(line2, line1, color);
			line2 = line1;
		}

	}

	if (a.type == Shape::eRect)
	{
		vec3 center;
		center = vec3Make(a.rect.position.x, a.rect.position.y, 0);

		vec3 TR = vec3Make(a.rect.max.x, a.rect.min.y, 0) + center;
		vec3 TL = a.rect.min + center;
		vec3 BL = vec3Make(a.rect.min.x, a.rect.max.y, 0) + center;
		vec3 BR = a.rect.max + center;
		
		drawLine(center, TL,color );
		drawLine(TL, TR, color); // TL -- TR
		drawLine(TL, BL, color);
		drawLine(BR, BL, color);
		drawLine(BR, TR, color);


		//vec3 TL, TR, BL, BR;
		//BL = a.rect.min + center;
		//BR = vec3Make(a.rect.max.x, a.rect.min.y, 0) + center;
		//TL = vec3Make(a.rect.min.x, a.rect.max.y, 0) + center;
		//TR = a.rect.max + center;

		//drawLine(TL, TR, vec4Color(1, 1, 0, 1)); //yellow
		//drawLine(TL, BL, vec4Color(1, 1, 0, 1)); //yellow
		//drawLine(TR, BR, vec4Color(1, 1, 1, 1)); //white
		//drawLine(BL, BR, vec4Color(0, 1, 1, 1)); //Light Blue

		//drawLine(center, TL, vec4Color(1, 1, 0, 1)); //yellow
		//drawLine(center, TR, vec4Color(1, 1, 1, 1)); //white
		//drawLine(center, BL, vec4Color(0, 1, 1, 1)); //Light Blue
		//drawLine(center, BR, vec4Color(0, 0, 1, 1)); //blue


	}

	if (a.type == Shape::eRay)
	{

		vec3 orgin;
		orgin = vec3Make(a.ray.position.x, a.ray.position.y, 0);

		vec3 end;
		end = orgin + a.ray.normal * 8;
		drawLine(orgin, end, color);
		
		
	
	} 

	if (a.type == Shape::ePlane)
	{
		
		vec3 Pos = vec3Make(a.plane.position.x, a.plane.position.y, 0);
		vec3 right;
		float angle = atan2f(a.plane.normal.x, a.plane.normal.y) + 3.14 / 2;

		
		right.x = cos(angle);
		right.y = sin(angle);
		right.z = 0;

		drawLine(Pos - right * 24, Pos + right * 24, color);
		drawLine(Pos, Pos + a.plane.normal * 8, color);



	}


}