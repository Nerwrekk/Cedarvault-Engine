using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    /*
    Blittability is basically a fancy way of saying:
        "This C# type can be copied directly to and from unmanaged (native) memory without any conversion or rearranging."
    
    Vector2 is blittable with its native Vector2 as its struct layout is 1-1
    */

    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        public float X, Y;

        public Vector2()
        {
            X = 0f;
            Y = 0f;
        }

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }

        public override string ToString()
        {
            return $"X:{X}, Y:{Y}";
        }
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