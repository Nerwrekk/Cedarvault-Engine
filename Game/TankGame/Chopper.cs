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
        Transform.Position.X = 100;
        Transform.Position.Y = 440;

        _rigidBodyComponent = AddComponent<RigidBodyComponent>();
        _rigidBodyComponent.Velocity = new Vector2(500, 0);


        _animationComponent = GetComponent<AnimationComponent>();
        _spriteComponent = GetComponent<SpriteComponent>();

        _animationComponent.NumOfFrames = 2;
        Log.Info($"animation FrameRateSpeed is: {_animationComponent.FrameRateSpeed}");
        Log.Trace($"animation NumOfFrames is: {_animationComponent.NumOfFrames}");
        Log.Debug($"animation ShouldLoop is: {_animationComponent.ShouldLoop}");
        Log.Warn("Warning log");
        Log.Error("Error log");

        _spriteComponent.TextureId = "chopper-spritesheet";
        _spriteComponent.SrcRect.y = _spriteComponent.Height * 1;

        Log.Info($"Transform position is: {Transform.Position}");
        Transform.Position = new Vector2(200, 400);
        Log.Info($"Transform position is: {Transform.Position}");

    }

    public override void OnUpdate(float deltaTime)
    {
        if (Transform.Position.X >= 600)
        {
            _rigidBodyComponent.Velocity.X = -50 * (_movespeed * deltaTime);
            _spriteComponent.SrcRect.y = _spriteComponent.Height * 3;
        }
        else if (Transform.Position.X <= 100)
        {
            _rigidBodyComponent.Velocity.X = 50 * _movespeed * deltaTime;
            _spriteComponent.SrcRect.y = _spriteComponent.Height * 1;
        }

        if (Input.IsKeyPressed(Key.P))
        {
            _animationComponent.FrameRateSpeed = 100;
            _movespeed += 100;
        }
        else if (Input.IsKeyReleased(Key.P))
        {
            _animationComponent.FrameRateSpeed = 10;
        }
    }
}