using System.Reflection;
using System.Runtime.Loader;

namespace MeanScriptEngine
{
    internal static class ScriptAssemblyResolver
    {
        public static void SetupDependencyResolver(string[] probingPaths)
        {
            AppDomain.CurrentDomain.AssemblyResolve += (sender, args) =>
            {
                var requestedAssembly = new AssemblyName(args.Name).Name;

                // Check if assembly is already loaded
                var loadedAssembly = AppDomain.CurrentDomain.GetAssemblies()
                    .FirstOrDefault(a => a.GetName().Name == requestedAssembly);

                if (loadedAssembly != null)
                {
                    Log.Info($"[Resolver] Returning already loaded assembly: {requestedAssembly}");
                    return loadedAssembly;
                }

                foreach (var path in probingPaths)
                {
                    var candidate = Path.Combine(path, requestedAssembly + ".dll");
                    if (File.Exists(candidate))
                    {
                        try
                        {
                            Log.Info($"[Resolver] Resolved '{requestedAssembly}' from: {candidate}");
                            return AssemblyLoadContext.Default.LoadFromAssemblyPath(candidate);
                        }
                        catch (Exception ex)
                        {
                            Log.Error($"[Resolver] Failed to load {candidate}: {ex}");
                            return null;
                        }
                    }
                }

                Log.Error($"[Resolver] Could not resolve: {requestedAssembly}");

                return null;
            };
        }
    }
}
