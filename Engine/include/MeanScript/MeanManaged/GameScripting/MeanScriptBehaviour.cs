namespace MeanScriptEngine
{
    public abstract class MeanScriptBehaviour
    {
        public Entity Entity { get; internal set; } // Set by native when instantiating

        public virtual void OnStart() { }
        public virtual void OnUpdate(float deltaTime) { }

        public void SetEntityPosition(float x, float y)
        {
            MeanNativeApi.SetEntityPosition(Entity, x, y);
        }
    }
}