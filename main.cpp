#include "Coordinator.h"

Coordinator &gCoordinator = Coordinator::GetInstance();

struct Vec3 {
  float x, y, z;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
  Vec3 operator*(float dt) { return Vec3(x * dt, y * dt, z * dt); }
  Vec3 operator+(Vec3 const &other) {
    return Vec3(x + other.x, y + other.y, z + other.z);
  }
  Vec3 operator*(float dt) const { return Vec3(x * dt, y * dt, z * dt); }
  Vec3 operator+=(Vec3 const &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
};

struct Gravity {
  Vec3 force;
};

struct RigidBody {
  Vec3 velocity;
  Vec3 acceleration;
};

struct Transform {
  Vec3 position;
  Vec3 rotation;
  Vec3 scale;
};

struct PhysicsSystem : public System {
  void Update(float dt);
};
void PhysicsSystem::Update(float dt) {
  for (auto const &entity : GetEntities()) {
    auto &rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
    auto &transform = gCoordinator.GetComponent<Transform>(entity);
    auto const &gravity = gCoordinator.GetComponent<Gravity>(entity);

    transform.position += rigidBody.velocity * dt;

    rigidBody.velocity += gravity.force * dt;
  }
}

int main() {
  gCoordinator.Init();

  gCoordinator.RegisterComponent<Gravity>();
  gCoordinator.RegisterComponent<RigidBody>();
  gCoordinator.RegisterComponent<Transform>();

  auto physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();

  Signature signature;
  signature.set(gCoordinator.GetComponentType<Gravity>());
  signature.set(gCoordinator.GetComponentType<RigidBody>());
  signature.set(gCoordinator.GetComponentType<Transform>());
  gCoordinator.SetSystemSignature<PhysicsSystem>(signature);

  std::vector<Entity> entities(MAX_ENTITIES);

  std::default_random_engine generator;
  std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
  std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
  std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
  std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

  float scale = randScale(generator);

  for (auto &entity : entities) {
    entity = gCoordinator.CreateEntity();

    gCoordinator.AddComponent(
        entity, Gravity{Vec3(0.0f, randGravity(generator), 0.0f)});

    gCoordinator.AddComponent(
        entity, RigidBody{.velocity = Vec3(0.0f, 0.0f, 0.0f),
                          .acceleration = Vec3(0.0f, 0.0f, 0.0f)});

    gCoordinator.AddComponent(
        entity,
        Transform{
            .position = Vec3(randPosition(generator), randPosition(generator),
                             randPosition(generator)),
            .rotation = Vec3(randRotation(generator), randRotation(generator),
                             randRotation(generator)),
            .scale = Vec3(scale, scale, scale)});
  }

  float dt = 0.0f;
  bool quit = false;

  while (!quit) {
    auto startTime = std::chrono::high_resolution_clock::now();

    physicsSystem->Update(dt);

    auto stopTime = std::chrono::high_resolution_clock::now();

    dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime -
                                                                    startTime)
             .count();
  }
}
