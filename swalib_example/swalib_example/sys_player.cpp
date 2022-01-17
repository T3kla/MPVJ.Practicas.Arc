#include "sys_player.h"

#include "sys.h"

#include "engine.h"
#include "engine_game.h"
#include "inputs.h"
#include "scene_01.h"
#include "sprite_loader.h"
#include "stasis.h"
#include "sys_hook.h"

#include "entity.h"

#include "ball.h"
#include "circle_collider.h"
#include "gameobject.h"
#include "player.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_renderer.h"
#include "transform.h"

constexpr char *stateIdle = "idle";
constexpr char *stateMoving = "moving";
constexpr char *stateShooting = "shooting";
constexpr char *stateHurt = "hurt";

float inputBlock = 0.f;
float invul = 0.f;
float invulBlink = 0.1f;

void UpdateAnimation();
void InstantiatePlayer();
void BlockInput(float time);
bool CanInput();
bool IsColliding(Vec2 posA, float radA, Vec2 posB, float radB);

Entity player = {};

SysPlayer::SysPlayer() {
  InstantiatePlayer();
  EngineGame::Subscribe(this);
}

SysPlayer::~SysPlayer() { EngineGame::UnSubscribe(this); }

void SysPlayer::Awake() {}

void SysPlayer::Start() {}

void SysPlayer::Update() {
  auto &reg = Scene_01::GetRegistry();

  inputBlock -= Stasis::GetDeltaScaled() * 0.001;
  invul -= Stasis::GetDeltaScaled() * 0.001;

  auto *tf = player.GetComponent<Transform>();
  auto *go = player.GetComponent<GameObject>();
  auto *rb = player.GetComponent<RigidBody>();
  auto *pl = player.GetComponent<Player>();

  if (go && go->isActive) {

    // Collisions
    for (auto &ball : reg) {
      auto *btf = ball->GetComponent<Transform>();
      auto *bgo = ball->GetComponent<GameObject>();
      auto *brb = ball->GetComponent<RigidBody>();
      auto *bbl = ball->GetComponent<Ball>();
      auto *bcl = ball->GetComponent<CircleCollider>();

      if (!btf || !bgo || !brb || !bbl || !bcl || !bgo->isActive)
        continue;

      if (IsColliding(tf->position, 40.f, btf->position, bcl->radius)) {
        //

        pl->state = stateHurt;
        invul = 3.f;
        return;
      }
    }

    // Input move and shoot
    auto *sa = player.GetComponent<SpriteAnimation>();

    Vec2 add = Vec2::Zero();

    if (CanInput() && SYS_KeyPressed(KEY_A))
      add -= pl->speed * (float)Stasis::GetDeltaScaled() * 0.001f;
    if (CanInput() && SYS_KeyPressed(KEY_D))
      add += pl->speed * (float)Stasis::GetDeltaScaled() * 0.001f;

    rb->velocity += add;

    auto velMag = rb->velocity.Magnitude();

    if (velMag > pl->speed)
      rb->velocity = rb->velocity.Normalized() * pl->speed;

    if (CanInput())
      if (velMag < 200.f)
        pl->state = stateIdle;
      else
        pl->state = stateMoving;

    pl->reversed = rb->velocity.x < 0.f ? true : false;

    if (CanInput() && SYS_KeyPressed(KEY_W)) {
      BlockInput(0.1f);
      SysHook::InstantiateHook(tf->position);
      pl->state = stateShooting;
    }

    UpdateAnimation();
  }
}

void SysPlayer::Fixed() {}

void SysPlayer::Quit() {}

Entity *SysPlayer::GetPlayer() { return &player; }

int SysPlayer::GetPlayerHealth() {
  return player.GetComponent<Player>()->health;
}

void InstantiatePlayer() {
  auto tf = Transform();
  auto go = GameObject();
  auto pl = Player();
  auto rb = RigidBody();
  auto sr = SpriteRenderer();
  auto sa = SpriteAnimation();

  tf.position = {1280.f / 2.f, 50.f};

  go.isActive = true;

  pl.health = 3;
  pl.speed = 5000.f;
  pl.state = stateIdle;
  pl.reversed = false;

  rb.velocity = {0.f, 0.f};
  rb.linearDrag = 0.2f;

  sr.sprite = &SpriteLoader::sprPlayerMoveL[0];
  sr.offsetPosition = {0.f, 0.f};
  sr.offsetRotation = 0.f;
  sr.size = {100.f, 100.f};
  sr.pivot = {0.5f, 0.5f};
  sr.layer = 10;

  sa.animation = &SpriteLoader::sprPlayerShootR;
  sa.duration = 1.f;
  sa.count = 0.f;
  sa.frame = 0;
  sa.enable = true;

  player.AddComponent<Transform>(&tf);
  player.AddComponent<GameObject>(&go);
  player.AddComponent<Player>(&pl);
  player.AddComponent<RigidBody>(&rb);
  player.AddComponent<SpriteRenderer>(&sr);
  player.AddComponent<SpriteAnimation>(&sa);

  Scene_01::GetRegistry().push_back(&player);
}

void UpdateAnimation() {
  auto *pl = player.GetComponent<Player>();
  auto *sr = player.GetComponent<SpriteRenderer>();
  auto *sa = player.GetComponent<SpriteAnimation>();

  if (sa)
    if (pl->state == stateMoving) {

      sa->enable = true;
      sa->duration = 0.25f;
      sa->animation = pl->reversed ? &SpriteLoader::sprPlayerMoveL
                                   : &SpriteLoader::sprPlayerMoveR;
    } else if (pl->state == stateIdle) {

      sa->enable = false;
      sr->sprite = pl->reversed ? &SpriteLoader::sprPlayerShootL[0]
                                : &SpriteLoader::sprPlayerShootR[0];
    } else if (pl->state == stateShooting) {

      sa->enable = true;
      sa->duration = 0.4f;
      sa->animation = pl->reversed ? &SpriteLoader::sprPlayerShootL
                                   : &SpriteLoader::sprPlayerShootR;
    } else if (pl->state == stateHurt) {

      sa->enable = false;
      sr->sprite = pl->reversed ? &SpriteLoader::sprPlayerHitL
                                : &SpriteLoader::sprPlayerHitR;
    }

  // Blink if invulnerable
}

void BlockInput(float time) { inputBlock = time; }
bool CanInput() { return inputBlock < 0.f; }

bool IsColliding(Vec2 posA, float radA, Vec2 posB, float radB) {
  return (posA - posB).Magnitude() < radA + radB;
}
