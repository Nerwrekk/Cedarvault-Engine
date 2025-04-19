using System.Reflection;
using System.Runtime.InteropServices;

namespace MeanScriptEngine
{
    public static class MeanScriptEngine
    {
        private static List<MeanScriptBehaviour> _scripts = new();

        [UnmanagedCallersOnly]
        public static void Initialize()
        {
            Console.WriteLine("[ScriptEngine] Initializing...");
        }

        [UnmanagedCallersOnly]
        public static void InstantiateScriptToEntity(nint typeNamePtr, Entity entity)
        {
            string typeName = Marshal.PtrToStringAnsi(typeNamePtr)!;
            var type = Type.GetType(typeName);
            if (type == null || !typeof(MeanScriptBehaviour).IsAssignableFrom(type))
            {
                Console.WriteLine($"[ScriptEngine] Invalid script type: {typeName}");
                return;
            }

            var script = (MeanScriptBehaviour)Activator.CreateInstance(type)!;
            script.Entity = entity;
            script.OnStart(); //Maybe call OnStart here?

            _scripts.Add(script);
        }

        [UnmanagedCallersOnly]
        public static void OnUpdateAll(float deltaTime)
        {
            foreach (var s in _scripts)
            {
                s.OnUpdate(deltaTime);
            }
        }
    }
}