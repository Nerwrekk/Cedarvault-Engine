using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public readonly struct Entity
    {
        public readonly uint Id;

        //this is for matching the memory layout of Enity inside c++ and should not be used at all!
        private readonly IntPtr doNotusePtr;

        public Entity(uint id)
        {
            Id = id;
        }

        public override string ToString() => $"Entity({Id})";

        public static implicit operator uint(Entity entity) => entity.Id;
        public static implicit operator Entity(uint id) => new Entity(id);
    }
}
