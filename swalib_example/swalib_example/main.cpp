#include "ball\ball.h"
#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"

void RenderInit(const GLuint &texsmallball);
void RenderLoop(const GLuint &texbkg);
void GameLoop();
void GameEnd(const GLuint &texbkg, const GLuint &texsmallball);

const unsigned int BALLS_NUM = 10; // Max. num balls.
const float BALLS_MAXSPEED = 8.f;  // Max vel. of ball. (pixels/?).
Ball balls[BALLS_NUM];             // Array of balls.

int Main(void)
{
    GLuint texbkg;
    GLuint texsmallball;

    RenderInit(texsmallball);

    while (!SYS_GottaQuit())
    {
        RenderLoop(texbkg);
        GameLoop();

        SYS_Pump();    // Process Windows messages.
        SYS_Sleep(17); // To force 60 fps
    }

    GameEnd(texbkg, texsmallball);

    return 0;
}

void RenderInit(const GLuint &texsmallball)
{
    FONT_Init();

    GLuint texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
    GLuint texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

    for (int i = 0; i < BALLS_NUM; i++)
    {
        balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
        balls[i].vel = vec2(CORE_FRand(-BALLS_MAXSPEED, +BALLS_MAXSPEED), CORE_FRand(-BALLS_MAXSPEED, +BALLS_MAXSPEED));
        balls[i].radius = 16.f;
        balls[i].gfx = texsmallball;
    }

    // Set up rendering.
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);            // Sets up clipping.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // Specifies clear values for the color buffers.
    glMatrixMode(GL_PROJECTION);                        // Specifies projection matrix is the current matrix.
    glLoadIdentity();                                   // Replaces the current matrix with the identity matrix.
    glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0); // Multiplies the current matrix by an orthographic matrix.
    glEnable(GL_TEXTURE_2D);                            // Enabling two-dimensional texturing.
                             // NOTA: Mirar diferencias comentando las 2 siguientes funciones.
    glEnable(GL_BLEND); // Blend the incoming RGBA color values with the values in the color buffers.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blend func. for alpha color.
}

void RenderLoop(const GLuint &texbkg)
{
    // Render
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
    {
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
        {
            CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
        }
    }

    // Render balls
    for (int i = 0; i < BALLS_NUM; i++)
    {
        CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);
    }

    // Text
    FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD!");

    // Exchanges the front and back buffers
    SYS_Show();
}

void GameLoop()
{
    // Run balls
    for (int i = 0; i < BALLS_NUM; i++)
    {
        // New Pos.
        vec2 newpos = balls[i].pos + balls[i].vel;

        // Collision detection.
        bool collision = false;
        int colliding_ball = -1;
        for (int j = 0; j < BALLS_NUM; j++)
        {
            if (i != j)
            {
                float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
                if (vlen2(newpos - balls[j].pos) <= limit2)
                {
                    collision = true;
                    colliding_ball = j;
                    break;
                }
            }
        }

        if (!collision)
        {
            balls[i].pos = newpos;
        }
        else
        {
            // Rebound!
            balls[i].vel = balls[i].vel * -1.f;
            balls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
        }

        // Rebound on margins.
        if ((balls[i].pos.x > SCR_WIDTH) || (balls[i].pos.x < 0))
        {
            balls[i].vel.x *= -1.0;
        }
        if ((balls[i].pos.y > SCR_HEIGHT) || (balls[i].pos.y < 0))
        {
            balls[i].vel.y *= -1.0;
        }
    }
}

void GameEnd(const GLuint &texbkg, const GLuint &texsmallball)
{
    // End app.
    // Unload textures.
    CORE_UnloadPNG(texbkg);
    CORE_UnloadPNG(texsmallball);
    FONT_End();
}
