#include "sys_renderer.h"
#include "core.h"
#include "ecs_manager.h"
#include "sprite_renderer.h"
#include "transform_2d.h"
#include "vector2d.h"

inline void SysRenderer::Run() {
  auto &ecs = ECS::Get();
  for (auto const &ent : entities) {
    auto &tf = ecs.GetComponent<Transform2D>(ent);
    auto &sr = ecs.GetComponent<SpriteRenderer>(ent);

    CORE_RenderCenteredSprite(vec2(tf.position.x, tf.position.y),
                              vec2(sr.scale.x * 2.f, sr.scale.y * 2.f),
                              sr.texture);
  }
}
