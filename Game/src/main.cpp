#include "CedarVault.h"

#include <iostream>

struct TestComponent
{
	int test;

	TestComponent(int test = 0)
	{
		this->test = test;
	}
};

int main()
{
	cedar::Application app;
	app.Setup([&]()
	{
		auto entity = app.Manager()->CreateEntity();
		auto tank = app.Manager()->CreateEntity();
		tank.AddComponent<cedar::RigidBodyComponent>(glm::vec2(50.f, 0.f));
		tank.AddComponent<TestComponent>();

		auto comp = app.Manager()->GetComponent<cedar::RigidBodyComponent>(tank);
		CEDAR_INFO("finished");
	});

	app.Run();

	return 0;
}