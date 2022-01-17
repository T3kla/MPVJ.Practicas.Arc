#include "sys_balls.h"

// virtual void Slot() override {
//     auto nozero = [](const float& f) { return f == 0.f ? f + FLT_EPSILON : f;
//     };
//
//     auto& aTF = *owner->GetComponent<Transform>();
//     auto& aCC = *owner->GetComponent<CircleCollider>();
//
//     // Rebound on margins
//     if ((aTF.position.x > SCR_WIDTH)) {
//         newPosMsg.newPos.x = SCR_WIDTH - 1;
//         owner->SendMessageNoWin(&newPosMsg);
//         velocity.x *= -1.f;
//     }
//     if ((aTF.position.x < 0.f)) {
//         newPosMsg.newPos.x = 1;
//         owner->SendMessageNoWin(&newPosMsg);
//         velocity.x *= -1.f;
//     }
//     if ((aTF.position.y > SCR_HEIGHT)) {
//         newPosMsg.newPos.y = SCR_HEIGHT - 1;
//         owner->SendMessageNoWin(&newPosMsg);
//         velocity.y *= -1.f;
//     }
//     if ((aTF.position.y < 0.f)) {
//         newPosMsg.newPos.y = 1;
//         owner->SendMessageNoWin(&newPosMsg);
//         velocity.y *= -1.f;
//     }
// }
