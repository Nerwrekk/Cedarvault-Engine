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

        public T AddComponent<T>()
        where T : unmanaged, IComponent
        {
            MeanNativeApi.AddComponent<T>(Entity);

            return MeanNativeApi.GetComponent<T>(Entity);
        }
    }
}