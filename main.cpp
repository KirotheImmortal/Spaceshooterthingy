#include "Core.h"
#include "System.h"

void main()
{
	coreLoad(Window);
	coreLoad(Time);
	coreLoad(Input);
	coreLoad(Camera);
	coreLoad(Factory);
	coreLoad(Asset);

	systemLoad(TransformUpdate);
	systemLoad(Rendering);
	systemLoad(TextRendering);



	systemLoad(CollisionPrep);
	systemLoad(CollisionDetection);
	systemLoad(CollisionRender);
	systemLoad(DynamicCollisionResponse);
	systemLoad(StaticCollisionResponse);


	systemLoad(ControlDynamics);
	systemLoad(RigidbodyDynamics);
	systemLoad(LifetimeDecay);

	initCore();

	// Safe to load assets and make dudes.
	core(Asset).loadShader("Flat", "./shaders/simpleShader.vert", "./shaders/simpleShader.frag");
	core(Asset).loadShader("Texture", "./shaders/simpleShader.vert", "./shaders/textureShader.frag");
	core(Asset).loadTexture("Spaceship", "./textures/shi.png", 1, 1);
	core(Asset).loadTexture("Cannon", "./textures/Spaceship.png", 1, 1);
	core(Asset).loadTexture("Background", "./textures/Galaxy1.jpg", 1, 2);
	core(Asset).loadTexture("Bullet", "./textures/Bullet.png", 1, 1);
	core(Asset).loadTexture("Explosion", "./textures/fireball.png", 1, 1);



	///////////////////////////////////////////////Geometry Creator////////////////////////////////////////////////

	////////////////////////////////////////////////Tank//////////////////////////////////////////
	Vertex		space[4] = {	{ { -60, 60, 0, 1 },  { 1, .1, .1, 0 }, { 1, 0 } },
								{ { -60, -60, 0, 1 }, { 1, .1, .1, 0 }, { 1, 1 } },
								{ { 60, -60, 0, 1 },  { 1, .1, .1, 0 }, { 0, 1 } },
						   		{ { 60, 60, 0, 1 },   { 1, .1, .1, 0 }, { 0, 0 } } };
	Vertex		space2[4] = {   { { -60, 60, 0, 1 },  { .1, .1, 1, 0 }, { 1, 0 } },
							    { { -60, -60, 0, 1 }, { .1, .1, 1, 0 }, { 1, 1 } },
							    { { 60, -60, 0, 1 },  { .1, .1, 1, 0 }, { 0, 1 } },
							    { { 60, 60, 0, 1 },   { 1, 1, 3, 0 }, { 0, 0 } } };
	Vertex		cannon[4] = {	{ { -30, 30, 0, 1 },  { 3, 1, 1, 0 }, { 1, 0 } },
								{ { -30, -30, 0, 1 }, { 3, 1, 1, 0 }, { 1, 1 } },
								{ { 30, -30, 0, 1 },  { 3, 1, 1, 0 }, { 0, 1 } },
								{ { 30, 30, 0, 1 },   { 3, 1, 1, 0 }, { 0, 0 } } };
	Vertex		cannon2[4] = {  { { -30, 30, 0, 1 },  { 1, 1, 3, 0 }, { 1, 0 } },
							    { { -30, -30, 0, 1 }, { 1, 1, 3, 0 }, { 1, 1 } },
								{ { 30, -30, 0, 1 },  { 1, 1, 3, 0 }, { 0, 1 } },
								{ { 30, 30, 0, 1 },   { 1, 1, 3, 0 }, { 0, 0 } } };
	Vertex		Bullet1[4] = {	{ { -15, 15, 0, 1 },  { 1, .1, .1, 0 }, { 1, 0 } },
								{ { -15, -15, 0, 1 }, { 1, .1, .1, 0 }, { 1, 1 } },
								{ { 15, -15, 0, 1 },  { 1, .1, .1, 0 }, { 0, 1 } },
								{ { 15, 15, 0, 1 },	  { 1, .1, .1, 0 }, { 0, 0 } } };
	Vertex		Bullet2[4] = {	{ { -15, 15, 0, 1 },  { .1, .1, 1, 0 }, { 1, 0 } },
								{ { -15, -15, 0, 1 }, { .1, .1, 1, 0 }, { 1, 1 } },
								{ { 15, -15, 0, 1 },  { .1, .1, 1, 0 }, { 0, 1 } },
								{ { 15, 15, 0, 1 },   { .1, .1, 1, 0 }, { 0, 0 } } };
	Vertex		Bullet3[4] = {	{ { -15, 15, 0, 1 },  { 1, .1, 1, 0 }, { 1, 0 } },
								{ { -15, -15, 0, 1 }, { 1, .1, 1, 0 }, { 1, 1 } },
								{ { 15, -15, 0, 1 },  { 1, .1, 1, 0 }, { 0, 1 } },
								{ { 15, 15, 0, 1 },   { 1, .1, 1, 0 }, { 0, 0 } } };
	///////////////////////////////////////////////////////////////////////////////////////////////	
	//////////////////////////////////////////Text Font////////////////////////////////////////////////////////
	//UV(BL(0,0),BR(1,0),TR(1,1), TL(0,1))
	core(Asset).loadTexture("TextFont", "./textures/font2.png", 8, 16);

	Vertex  mesh[4] = { { { -10, 10, 0, 1 }, { 1, 1, 1, 0 },  { 0,0 } },
						{ { -10, -10, 0, 1 }, { 1, 1, 1, 0 }, {0, 1 } },
						{ {  10, -10, 0, 1 }, { 1, 1, 1, 0 }, { 1,1 } },
						{ {  10, 10, 0, 1 }, { 1, 1, 1, 0 },  { 1, 0 } } };
	Triangle text[2] = { { 0, 1, 2 }, { 0, 2, 3 } };

	core(Asset).loadMesh("font", mesh, 4, text, 2);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////Background///////////////////////////////////////////////////////
	Vertex		back[4] = { { { -WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 1 }, { 1, 1, 1, 0 }, { 1, 1 } },
	{ { -WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, 0, 1 }, { 1, 1, 1, 0 }, { 0, 1 } },
	{ { WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, 0, 1 }, { 1, 1, 1, 0 }, { 0, 0 } },
	{ { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 1 }, { 1, 1, 1, 0 }, { 1, 0 } } };

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	Triangle	triangle[2] = { { 0, 1, 2 }, { 0, 2, 3 } };
	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////Mesh Loader///////////////////////////////////////////////
	core(Asset).loadMesh("space",   space, 4, triangle, 2);
	core(Asset).loadMesh("space2",  space2, 4, triangle, 2);
	core(Asset).loadMesh("cannon",  cannon, 4, triangle, 2);
	core(Asset).loadMesh("cannon2", cannon2, 4, triangle, 2);
	core(Asset).loadMesh("back",    back, 4, triangle, 2);
	core(Asset).loadMesh("Bullet1", Bullet1, 4, triangle, 2);
	core(Asset).loadMesh("Bullet2", Bullet2, 4, triangle, 2);
	core(Asset).loadMesh("Bullet3", Bullet3, 4, triangle, 2);
	///////////////////////////////////////////////////////////////////////////////////////////////




	///////////////////////////////////factory call////////////////////////////////////////////
	
	core(Factory).MakeBackground();
	core(Factory).drawText("Fight", WINDOW_WIDTH / 3, WINDOW_HEIGHT -100, 1, 1);
	core(Factory).MakeTank(WINDOW_WIDTH / 2 - 500, WINDOW_HEIGHT / 2, 1);
	core(Factory).MakeTank(WINDOW_WIDTH / 2 + 500, WINDOW_HEIGHT / 2, 2);
	core(Factory).MakeBorders();
	////////////////////////////////////////////////////////////////////////////


	runGame();
}