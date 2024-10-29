#ifndef SYSTEM_H
#define SYSTEM_H
#include "EntityComponent.h"
class System {
  friend class SystemManager;

public:
  System() {}
  ~System() {}

  const std::set<Entity> GetEntities() const { return mEntities; }

private:
  std::set<Entity> mEntities;
};

#endif // SYSTEM_H
