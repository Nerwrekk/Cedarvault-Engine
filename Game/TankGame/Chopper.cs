using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Chopper : MeanScriptBehaviour
{
    private RigidBodyComponent _rigidBodyComponent;
    private AnimationComponent _animationComponent;
    private SpriteComponent _spriteComponent;

    private float _movespeed = 100;
    public override void OnStart()
    {
        _rigidBodyComponent = AddComponent<RigidBodyComponent>();
        _rigidBodyComponent.Velocity = new Vector2(500, 0);

        _animationComponent = GetComponent<AnimationComponent>();
        _spriteComponent = GetComponent<SpriteComponent>();

        _animationComponent.NumOfFrames = 2;
    }

    public override void OnUpdate(float deltaTime)
    {
        if (Transform.Position.X >= 600)
        {
            _rigidBodyComponent.Velocity.X = -50 * (_movespeed * deltaTime);
        }
        else if (Transform.Position.X <= 100)
        {
            _rigidBodyComponent.Velocity.X = 50 * _movespeed * deltaTime;
        }

        if (Input.IsKeyPressed(Key.P))
        {
            Log.Error("P is pressed");
            _animationComponent.FrameRateSpeed = 100;
            // _movespeed += 100;
        }
        else if (Input.IsKeyReleased(Key.P))
        {
            Log.Error("P is released");
            _animationComponent.FrameRateSpeed = 10;
        }
    }
}