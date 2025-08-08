using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        public float X, Y;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct SDL_Rect
    {
        public int x, y;
        public int w, h;
    }

    namespace Components
    {
        public interface IComponent { }
    }

}