#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"

//-----------------------------------------------------------------------------
// Logic Info.
struct Ball	// Info Ball
{
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.

	Ball() :
		pos(0.0f),
		vel(0.0f),
		gfx(0),
		radius(0.0f)
	{}
};
const unsigned int NUM_BALLS = 10;	// Max. num balls.
Ball balls[NUM_BALLS];	// Array of balls.

const float MAX_BALL_SPEED = 8.f;	// Max vel. of ball. (pixels/?).

//-----------------------------------------------------------------------------
int Main(void)
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	// Load textures
	GLuint texbkg        = CORE_LoadPNG("data/circle-bkg-128.png"   , true);
	GLuint texsmallball  = CORE_LoadPNG("data/tyrian_ball.png"      , false);

	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
		balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
		balls[i].radius = 16.f;
		balls[i].gfx = texsmallball;
	}

	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
  
	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.
		// Render
		glClear( GL_COLOR_BUFFER_BIT );	// Clear color buffer to preset values.

		// Render backgground
		for (int i = 0; i <= SCR_WIDTH / 128; i++) {
			for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
				CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
			}
		}

		// Render balls
		for (int i = 0; i < NUM_BALLS; i++) {
			CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
		}

		// Text
		FONT_DrawString(vec2(SCR_WIDTH/2 - 6*16, 16), "HELLO WORLD!");
   
		// Exchanges the front and back buffers
		SYS_Show();

		// Run balls
		for (int i = 0; i < NUM_BALLS; i++) {
			// New Pos.
			vec2 newpos = balls[i].pos + balls[i].vel;

			// Collision detection.
			bool collision = false;
			int colliding_ball = -1;
			for (int j = 0; j < NUM_BALLS; j++) {
				if (i != j) {
					float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
					if (vlen2(newpos - balls[j].pos) <= limit2) {
						collision = true;
						colliding_ball = j;
						break;
					}
				}
			}

			if (!collision) {
				balls[i].pos = newpos;
			}
			else {
				// Rebound!
				balls[i].vel = balls[i].vel * -1.f;
				balls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
			}

			// Rebound on margins.
			if ((balls[i].pos.x > SCR_WIDTH) || (balls[i].pos.x < 0)) {
				balls[i].vel.x *= -1.0;
			}
			if ((balls[i].pos.y > SCR_HEIGHT) || (balls[i].pos.y < 0)) {
				balls[i].vel.y *= -1.0;
			}
		}
		
		SYS_Pump();	// Process Windows messages.
		SYS_Sleep(17);	// To force 60 fps
	}

	// End app.
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
	FONT_End();

	return 0;
}
