#ifndef COORDINATOR_H
#define COORDINATOR_H
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "pch.h"

class Coordinator {
public:
  inline static Coordinator &GetInstance();
  inline void Init();

  // Entities
  inline Entity CreateEntity();
  inline void DestroyEntity(Entity entity);

  // Components
  TEMPLATE void RegisterComponent();
  TEMPLATE void AddComponent(Entity entity, T component);
  TEMPLATE void RemoveComponent(Entity entity);
  TEMPLATE T &GetComponent(Entity entity);
  TEMPLATE ComponentType GetComponentType();

  // Systems
  TEMPLATE Shared<T> RegisterSystem();
  TEMPLATE void SetSystemSignature(Signature signature);

private:
  Coordinator() { Init(); }
  Coordinator(const Coordinator &) = delete;
  Coordinator &operator=(const Coordinator &) = delete;

private:
  Unique<ComponentManager> mComponentManager;
  Unique<EntityManager> mEntityManager;
  Unique<SystemManager> mSystemManager;
};

Coordinator &Coordinator::GetInstance() {
  static Coordinator instance;
  return instance;
}

void Coordinator::Init() {
  mComponentManager = std::make_unique<ComponentManager>();
  mEntityManager = std::make_unique<EntityManager>();
  mSystemManager = std::make_unique<SystemManager>();
}

Entity Coordinator::CreateEntity() { return mEntityManager->CreateEntity(); }

void Coordinator::DestroyEntity(Entity entity) {
  mEntityManager->DestroyEntity(entity);
  mComponentManager->EntityDestroyed(entity);
  mSystemManager->EntityDestroyed(entity);
}

TEMPLATE void Coordinator::RegisterComponent() {
  mComponentManager->RegisterComponent<T>();
}

TEMPLATE void Coordinator::AddComponent(Entity entity, T component) {
  mComponentManager->AddComponent<T>(entity, component);

  auto signature = mEntityManager->GetSignature(entity);
  signature.set(mComponentManager->GetComponentType<T>(), true);
  mEntityManager->SetSignature(entity, signature);

  mSystemManager->EntitySignatureChanged(entity, signature);
}

TEMPLATE void Coordinator::RemoveComponent(Entity entity) {
  mComponentManager->RemoveComponent<T>(entity);

  auto signature = mEntityManager->GetSignature(entity);
  signature.set(mComponentManager->GetComponentType<T>(), false);
  mEntityManager->SetSignature(entity, signature);

  mSystemManager->EntitySignatureChanged(entity, signature);
}

TEMPLATE T &Coordinator::GetComponent(Entity entity) {
  return mComponentManager->GetComponent<T>(entity);
}

TEMPLATE ComponentType Coordinator::GetComponentType() {
  return mComponentManager->GetComponentType<T>();
}

TEMPLATE Shared<T> Coordinator::RegisterSystem() {
  return mSystemManager->RegisterSystem<T>();
}

TEMPLATE void Coordinator::SetSystemSignature(Signature signature) {
  mSystemManager->SetSignature<T>(signature);
}

#endif // COORDINATOR_H
