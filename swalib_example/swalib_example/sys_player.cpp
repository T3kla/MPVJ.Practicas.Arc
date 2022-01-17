#include "sys_player.h"

#include "sys.h"

#include "engine.h"
#include "engine_game.h"
#include "inputs.h"
#include "scene_01.h"
#include "sprite_loader.h"

#include "entity.h"

#include "circle_collider.h"
#include "gameobject.h"
#include "player.h"
#include "rigidbody.h"
#include "sprite_animation.h"
#include "sprite_renderer.h"
#include "transform.h"

constexpr char *stateIdle = "idle";
constexpr char *stateMoving = "moving";

void UpdateAnimation();
void InstantiatePlayer();

Entity player = {};

SysPlayer::SysPlayer() {
  InstantiatePlayer();
  EngineGame::Subscribe(this);
}

SysPlayer::~SysPlayer() { EngineGame::UnSubscribe(this); }

void SysPlayer::Awake() {}

void SysPlayer::Start() {}

void SysPlayer::Update() {}

void SysPlayer::Fixed() {
  auto *tf = player.GetComponent<Transform>();
  auto *go = player.GetComponent<GameObject>();
  auto *rb = player.GetComponent<RigidBody>();
  auto *pl = player.GetComponent<Player>();

  if (go && go->isActive) {
    auto *sa = player.GetComponent<SpriteAnimation>();

    Vec2 add = Vec2::Zero();

    if (SYS_KeyPressed(KEY_A))
      add -= pl->speed * (float)STP * 0.001f;

    if (SYS_KeyPressed(KEY_D))
      add += pl->speed * (float)STP * 0.001f;

    rb->velocity += add;

    auto velMag = rb->velocity.Magnitude();

    if (velMag > pl->speed)
      rb->velocity = rb->velocity.Normalized() * pl->speed;

    if (velMag != 0.f)
      pl->state = stateMoving;

    pl->reversed = rb->velocity.x < 0.f ? true : false;

    if (SYS_KeyPressed(KEY_W)) {
      // TODO: shoot
    }

    UpdateAnimation();
  }
}

void SysPlayer::Quit() {}

Entity *SysPlayer::GetPlayer() { return &player; }

void InstantiatePlayer() {
  auto tf = Transform();
  auto go = GameObject();
  auto pl = Player();
  auto rb = RigidBody();
  auto cc = CircleCollider();
  auto sr = SpriteRenderer();
  auto sa = SpriteAnimation();

  tf.position = {1280.f / 2.f, 50.f};

  go.isActive = true;

  pl.health = true;
  pl.speed = 15000.f;
  pl.state = stateIdle;
  pl.reversed = false;

  rb.velocity = {0.f, 0.f};
  rb.linearDrag = 0.3f;

  cc.radius = 4.f;

  sr.sprite = &SpriteLoader::sprPlayerMoveL[0];
  sr.offsetPosition = {0.f, 0.f};
  sr.offsetRotation = 0.f;
  sr.size = {100.f, 100.f};
  sr.pivot = {0.5f, 0.5f};
  sr.layer = 0;

  sa.enable = true;
  sa.animation = &SpriteLoader::sprPlayerShootR;
  sa.duration = 2.f;
  sa.count = 365.24f;
  // sa.frame = 0;
  // sa.speed = 1.f;

  player.AddComponent<Transform>(&tf);
  player.AddComponent<GameObject>(&go);
  player.AddComponent<Player>(&pl);
  player.AddComponent<RigidBody>(&rb);
  player.AddComponent<CircleCollider>(&cc);
  player.AddComponent<SpriteRenderer>(&sr);
  player.AddComponent<SpriteAnimation>(&sa);

  Scene_01::GetRegistry().push_back(&player);
}

void UpdateAnimation() {
  // auto *pl = player.GetComponent<Player>();
  // auto *sa = player.GetComponent<SpriteAnimation>();

  // if (sa && sa->enabled) {
  //   if (pl->state == stateMoving) {
  //     if (pl->reversed)
  //       sa->animation = &SpriteLoader::sprPlayerShootR;
  //     else
  //       sa->animation = &SpriteLoader::sprPlayerShootR;
  //   }
  // }
}
