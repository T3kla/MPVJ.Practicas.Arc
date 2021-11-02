#include "balls/ball.h"
#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "time/time.h"
#include "vector2d.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// https://www.reddit.com/r/gamedev/comments/4c2ekd/what_is_the_best_way_to_work_out_delta_time/

const unsigned int NUM_BALLS = 10; // Max. num balls.
const float MAX_BALL_SPEED = 8.f;  // Max vel. of ball. (pixels/?).
Ball balls[NUM_BALLS];             // Array of balls.

// Load textures
GLuint texbkg;
GLuint texsmallball;

// Time stuff
auto delta = mytime::DeltaTime();
auto fixed = 1.0 / 0.01;
auto fix60 = 1.0 / 60.0;
auto count = 0.0;
auto cou60 = 0.0;

void Init()
{
    FONT_Init(); // Characters and symbols inicialization to draw on screen.

    // Load textures
    texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
    texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

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

    // Init game state.
    for (int i = 0; i < NUM_BALLS; i++)
    {
        balls[i].pos = vec2(CORE_FRand(0.0, SCR_WIDTH), CORE_FRand(0.0, SCR_HEIGHT));
        balls[i].vel = vec2(CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED), CORE_FRand(-MAX_BALL_SPEED, +MAX_BALL_SPEED));
        balls[i].radius = 16.f;
        balls[i].gfx = texsmallball;
    }
}

void RenderLoop()
{
    // Render
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer to preset values.

    // Render background
    for (int i = 0; i <= SCR_WIDTH / 128; i++)
        for (int j = 0; j <= SCR_HEIGHT / 128; j++)
            CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);

    // Render balls
    for (int i = 0; i < NUM_BALLS; i++)
        CORE_RenderCenteredSprite(balls[i].pos, vec2(balls[i].radius * 2.f, balls[i].radius * 2.f), balls[i].gfx);

    // Text
    std::ostringstream strm;
    strm << std::fixed << std::setprecision(2) << delta;
    std::string str = strm.str();
    FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), str.c_str());

    // Exchanges the front and back buffers
    SYS_Show();
}

void GameLoop()
{
    for (int i = 0; i < NUM_BALLS; i++)
    {
        vec2 newpos = balls[i].pos + balls[i].vel;

        bool collision = false;
        int colliding_ball = -1;

        for (int j = 0; j < NUM_BALLS; j++)
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
            balls[i].vel.x *= -1.0;

        if ((balls[i].pos.y > SCR_HEIGHT) || (balls[i].pos.y < 0))
            balls[i].vel.y *= -1.0;
    }
}

void Update(double dt)
{
}

void FixedUpda60(double dt)
{
    GameLoop();
}

void FixedUpdate(double dt)
{
    RenderLoop();
}

void Loop()
{
    while (!SYS_GottaQuit())
    {
        delta = mytime::DeltaTime();

        Update(delta);

        count += delta;
        if (count > fixed)
        {
            FixedUpdate(fixed);
            count -= fixed;
        }

        cou60 += delta;
        if (cou60 > fix60)
        {
            FixedUpda60(fix60);
            cou60 -= fix60;
        }

        SYS_Pump();    // Process Windows messages.
        SYS_Sleep(17); // To force 60 fps
    }
}

void Exit()
{
    CORE_UnloadPNG(texbkg);
    CORE_UnloadPNG(texsmallball);
    FONT_End();
}

int Main(void)
{
    Init();
    Loop();
    Exit();

    return 0;
}
