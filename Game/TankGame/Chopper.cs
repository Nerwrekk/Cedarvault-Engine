using System;
using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Chopper : MeanScriptBehaviour
{

    private RigidBodyComponent _rigidBodyComponent;
    public override void OnStart()
    {
        Transform.Position.X = 100;
        Transform.Position.Y = 440;

        _rigidBodyComponent = AddComponent<RigidBodyComponent, InitRigidBodyComponent>(new InitRigidBodyComponent()
        {
            Velocity = new Vector2()
            {
                X = 50,
                Y = 0,
            }
        });
    }

    public override void OnUpdate(float deltaTime)
    {
        if (Transform.Position.X >= 600)
        {
            _rigidBodyComponent.Velocity.X = -50;
        }
        else if (Transform.Position.X <= 100)
        {
            _rigidBodyComponent.Velocity.X = 50;
        }

        Console.WriteLine($"Chopper id: {Entity.Id} position is [x: {Transform.Position.X}, y: {Transform.Position.Y}]");
    }
}