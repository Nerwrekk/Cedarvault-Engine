using MeanScriptEngine;
using MeanScriptEngine.Components;
using MeanScriptEngine.Input;

public class Chopper : MeanScriptBehaviour
{
    private RigidBodyComponent _rigidBodyComponent;
    private AnimationComponent _animationComponent;
    private SpriteComponent _spriteComponent;
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

        _animationComponent = GetComponent<AnimationComponent>();
        _spriteComponent = GetComponent<SpriteComponent>();

        _animationComponent.NumOfFrames = 2;
        Console.WriteLine($"animation FrameRateSpeed is: {_animationComponent.FrameRateSpeed}");
        Console.WriteLine($"animation NumOfFrames is: {_animationComponent.NumOfFrames}");
        Console.WriteLine($"animation ShouldLoop is: {_animationComponent.ShouldLoop}");

        _spriteComponent.TextureId = "chopper-spritesheet";
        _spriteComponent.SrcRect.y = _spriteComponent.Height * 1;
    }

    public override void OnUpdate(float deltaTime)
    {
        if (Transform.Position.X >= 600)
        {
            _rigidBodyComponent.Velocity.X = -50;
            _spriteComponent.SrcRect.y = _spriteComponent.Height * 3;
        }
        else if (Transform.Position.X <= 100)
        {
            _rigidBodyComponent.Velocity.X = 50;
            _spriteComponent.SrcRect.y = _spriteComponent.Height * 1;
        }

        if (Input.IsKeyPressed(Key.P))
        {
            _animationComponent.FrameRateSpeed = 100;
        }
        else if (Input.IsKeyReleased(Key.P))
        {
            _animationComponent.FrameRateSpeed = 10;
        }
    }
}