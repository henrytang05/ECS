#include "EntityManager.h"

EntityManager::EntityManager() : mLivingEntityCount(0) {
  for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
    mAvailableEntities.push(entity);
  }
}

EntityManager::~EntityManager() {}

Entity EntityManager::CreateEntity() {

  assert(mLivingEntityCount < MAX_ENTITIES &&
         "Too many entities in existence.");

  Entity id = mAvailableEntities.front();
  mAvailableEntities.pop();
  ++mLivingEntityCount;

  return id;
}

void EntityManager::DestroyEntity(Entity entity) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");

  mSignatures[entity].reset();

  mAvailableEntities.push(entity);
  --mLivingEntityCount;
}

Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");

  return mSignatures[entity];
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");
  mSignatures[entity] = signature;
}
