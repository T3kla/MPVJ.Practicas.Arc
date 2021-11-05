#include "..\swalib_example\swalib_example\ball\ball.h"
#include "..\swalib_example\swalib_example\counter\counter.h"
#include "core.h"
#include "font.h"
#include "stdafx.h"
#include "sys.h"
#include "vector2d.h"
#include <iostream>

// Balls stuff
const float MAX_BALL_SPEED = 500.f; // Max vel. of ball. (pixels/second).
const unsigned int NUM_BALLS = 10;  // Max. num balls.
Ball balls[NUM_BALLS];              // Array of balls.

// Time stuff
const double freq_fx = (1.0 / 60.0) * 1000.0;
const unsigned short avg_samples = 64;
tkl::counter counter;
std::vector<double> avg_up(avg_samples, 0);
std::vector<double> avg_fx(avg_samples, 0);
double timeasd;

// Texture stuff
GLuint texbkg;
GLuint texsmallball;

void Init()
{
    FONT_Init();

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
    auto avg_up_final = 0.0;
    auto avg_fx_final = 0.0;

    for (auto &&i : avg_up)
        avg_up_final += i;
    for (auto &&i : avg_fx)
        avg_fx_final += i;

    auto fps_up = (1.0 / (avg_up_final / (double)avg_samples)) * 1000.0;
    auto fps_fx = (1.0 / (avg_fx_final / (double)avg_samples)) * 1000.0;

    auto str_tm = "      TIME: " + std::to_string(timeasd / 1000.0);
    auto str_up = "UPDATE FPS: " + std::to_string(fps_up);
    auto str_fx = " FIXED FPS: " + std::to_string(fps_fx);

    FONT_DrawString(vec2(0, 32), str_tm.c_str());
    FONT_DrawString(vec2(0, 16), str_fx.c_str());
    FONT_DrawString(vec2(0, 0), str_up.c_str());

    // Exchanges the front and back buffers
    SYS_Show();
}

void GameLoop(double dt)
{
    for (int i = 0; i < NUM_BALLS; i++)
    {
        // Decouple speed from time/cycles
        vec2 newpos = balls[i].pos + balls[i].vel * (dt / 1000);

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
    GameLoop(dt);
}

void FixedUpdate(double dt)
{
    RenderLoop();
}

void Loop()
{
    auto pos_up = 0;
    auto dt_up = 0.0;
    counter.stamp();

    auto pos_fx = 0;
    auto cum_fx = 0.0;

    while (!SYS_GottaQuit())
    {
        double dt_up = counter.measure();
        counter.stamp();

        avg_up[pos_up] = dt_up;
        pos_up += 1 - avg_samples * (pos_up == avg_samples - 1);

        Update(dt_up);

        timeasd += dt_up;
        cum_fx += dt_up;
        if (cum_fx >= freq_fx)
        {
            avg_fx[pos_fx] = cum_fx;
            pos_fx += 1 - avg_samples * (pos_fx == avg_samples - 1);

            FixedUpdate(cum_fx);

            cum_fx = 0;
        }

        SYS_Pump(); // Process Windows messages.
        // SYS_Sleep(17); // To force 60 fps
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
