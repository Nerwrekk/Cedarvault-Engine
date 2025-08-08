using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Loader;


namespace MeanScriptEngine
{
    public static class MeanScriptEngine
    {
        private static List<MeanScriptBehaviour> _scripts = new();
        private static Assembly? _scriptDllAssembly;

        private static Type? meanScriptBehaviourBaseType;

        [UnmanagedCallersOnly]
        public static void Initialize(nint meanScriptingDllPath)
        {
            Console.WriteLine("[ScriptEngine] Initializing...");

            // This ensures we get the correct base type from the already-loaded MeanScripting.dll
            meanScriptBehaviourBaseType = typeof(MeanScriptBehaviour); // This is safe because we're using the "real" one

            // This should be the folder where MeanScripting.dll is built and expected to be
            ScriptAssemblyResolver.SetupDependencyResolver(new[]
            {
                Path.GetFullPath("./")
            });
        }

        [UnmanagedCallersOnly]
        public static unsafe void LoadDllScripts(nint assemblyPath)
        {
            string path = Marshal.PtrToStringAnsi(assemblyPath)!;
            if (string.IsNullOrEmpty(path))
            {
                Console.WriteLine("ERROR: Script path is null or empty.");
                return;
            }

            string fullPath = Path.GetFullPath(path);
            Console.WriteLine($"[MeanScriptEngine] Requested to load: '{path}'");
            if (!File.Exists(fullPath))
            {
                Console.WriteLine("[Error] not found at: " + fullPath);
                return;
            }

            try
            {
                _scriptDllAssembly = AssemblyLoadContext.Default.LoadFromAssemblyPath(fullPath);
                // _scriptDllAssembly = Assembly.Load(path);
            }
            catch (Exception ex)
            {
                Console.WriteLine("[Error] Failed to load script assembly:");
                Console.WriteLine(ex.ToString());
                throw;
            }

            foreach (var type in _scriptDllAssembly.GetExportedTypes())
            {
                Console.WriteLine($"[Debug] Found type: {type.FullName}");
            }
        }

        [UnmanagedCallersOnly]
        public static void InstantiateScriptToEntity(nint typeNamePtr, Entity entity)
        {
            if (_scriptDllAssembly == null)
            {
                Console.WriteLine("ERROR: ScriptDllAssembly is NULL!");

                return;
            }

            string typeName = Marshal.PtrToStringAnsi(typeNamePtr)!;

            var type = _scriptDllAssembly.GetType(typeName);
            Console.WriteLine($"Script type is: {type.FullName}");
            if (type == null || meanScriptBehaviourBaseType == null || !meanScriptBehaviourBaseType.IsAssignableFrom(type))
            {
                Console.WriteLine($"[MeanScriptEngine] Invalid script type: {typeName}");
                return;
            }

            var script = (MeanScriptBehaviour)Activator.CreateInstance(type)!;
            script.Entity = entity;
            script.Transform = MeanNativeApi.GetTransformComponent(entity);
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