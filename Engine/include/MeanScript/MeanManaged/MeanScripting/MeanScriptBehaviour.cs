using System.Runtime.InteropServices;
using MeanScriptEngine.Components;

namespace MeanScriptEngine
{
    public abstract class MeanScriptBehaviour
    {
        public Entity Entity { get; internal set; } // Set by native when instantiating
        public TransformComponent Transform { get; internal set; }

        public virtual void OnStart() { }
        public virtual void OnUpdate(float deltaTime) { }

        public void SetEntityPosition(float x, float y)
        {
            MeanNativeApi.SetEntityPosition(Entity, x, y);
        }

        public T GetComponent<T>()
        {
            return MeanNativeApi.GetComponent<T>(Entity);
        }

        public T AddComponent<T, I>(I initComponent)
        where T : unmanaged, IComponent
        where I : unmanaged, IComponentInit
        {
            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf<T>());
            Marshal.StructureToPtr(initComponent, ptr, false);

            MeanNativeApi.AddComponent(Entity, initComponent);

            Marshal.FreeHGlobal(ptr);

            return MeanNativeApi.GetComponent<T>(Entity);
        }
    }
}