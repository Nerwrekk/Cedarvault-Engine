

using System.Runtime.InteropServices;
using MeanScriptEngine.Components;
using MeanScriptEngine.MeanPrimitives;

namespace MeanScriptEngine
{
    //Note all init components MUST start with "Init"
    public interface IComponentInit { }

    [StructLayout(LayoutKind.Sequential)]
    public struct InitSpriteComponent : IComponentInit
    {
        public int _width;
        public int _height;
        public UInt32 _zIndex;
        public SDL_Rect _srcRect;
        public MeanString _textureId;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct InitRigidBodyComponent : IComponentInit
    {
        public Vector2 Velocity;
    }
}