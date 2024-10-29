#include "EntityManager.h"
#include "gtest/gtest.h"

TEST(EntityManagerTest, CreateEntity) {
  EntityManager entityManager;

  Entity entity = entityManager.CreateEntity();
  ASSERT_EQ(entity, 0);

  entity = entityManager.CreateEntity();
  ASSERT_EQ(entity, 1);
}

TEST(EntityManagerTest, DestroyEntity) {
  EntityManager entityManager;

  Entity entity = entityManager.CreateEntity();
  ASSERT_EQ(entity, 0);

  ASSERT_TRUE(entityManager.DestroyEntity(entity));
}

TEST(EntityManagerTest, GetSignature) {
  EntityManager entityManager;

  Entity entity = entityManager.CreateEntity();
  ASSERT_EQ(entity, 0);

  Signature signature = entityManager.GetSignature(entity);
  ASSERT_EQ(signature.to_ulong(), 0);
}

TEST(EntityManagerTest, SetSignature) {
  EntityManager entityManager;

  Entity entity = entityManager.CreateEntity();
  ASSERT_EQ(entity, 0);

  Signature signature;
  signature.set(0);
  signature.set(1);

  ASSERT_TRUE(entityManager.SetSignature(entity, signature));

  signature = entityManager.GetSignature(entity);
  ASSERT_EQ(signature.to_ulong(), 3);
}
