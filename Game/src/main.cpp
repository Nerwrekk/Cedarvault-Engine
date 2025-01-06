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
	});
	auto tank = app.Manager()->CreateEntity();
	app.Manager()->AddComponent<cedar::RigidBodyComponent>(tank, glm::vec2(50.f, 0.f));
	app.Manager()->AddComponent<TestComponent>(tank);

	app.Run();

	return 0;
}