#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER
#include "EntityComponent.h"
class EntityManager {
public:
  EntityManager();
  ~EntityManager();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);
  Signature GetSignature(Entity entity);
  void SetSignature(Entity entity, Signature signature);

private:
  std::queue<Entity> mAvailableEntities;
  std::array<Signature, MAX_ENTITIES> mSignatures;

  uint32_t mLivingEntityCount;
};

#endif // ENTITY_MANAGER
