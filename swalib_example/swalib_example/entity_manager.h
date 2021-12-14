#pragma once

#include <array>
#include <bitset>
#include <queue>

constexpr size_t MAX_ENTS = 1024;
constexpr size_t MAX_CMPS = 8;

using EntID = size_t;
using CmpID = size_t;
using Signature = std::bitset<MAX_CMPS>;

// Rent entity ids and binds them with their respective signatures

class EntityMan {
private:
  std::queue<EntID> unusedIDs{};
  std::array<Signature, MAX_ENTS> name_sign{};
  size_t count = 0;

public:
  EntityMan();

  EntID BorrowID();
  void ReturnID(EntID id);

  const Signature &GetSignature(EntID id) const;
  void SetSignature(EntID id, const Signature &sign);
};
