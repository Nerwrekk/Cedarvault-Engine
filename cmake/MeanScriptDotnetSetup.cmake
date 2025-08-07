set(DOTNET_VERSION "8.0.19")

# Define DOTNET RID (Runtime Identifier)
if(WIN32)
set(DOTNET_RID "win-x64")
elseif(UNIX AND NOT APPLE)
set(DOTNET_RID "linux-x64")
endif()

set(DOTNET_PACK_NAME "Microsoft.NETCore.App.Host.${DOTNET_RID}")

#/usr/share/dotnet/packs/Microsoft.NETCore.App.Host.linux-x64/8.0.15/runtimes/linux-x64
#usr/share/dotnet/packs/Microsoft.NETCore.App.Host.linux-x64/8.0.15/runtimes/linux-x64/native
#/usr/share/dotnet/packs/Microsoft.NETCore.App.Host.linux-x64/8.0.15/runtimes/linux-x64/native
# nethost.h (shared across platforms)
set(NETHOST_INCLUDE "/usr/share/dotnet/packs/${DOTNET_PACK_NAME}/${DOTNET_VERSION}/runtimes/${DOTNET_RID}/native")
if(WIN32)
    set(NETHOST_INCLUDE "$ENV{ProgramFiles}/dotnet/packs/${DOTNET_PACK_NAME}/${DOTNET_VERSION}/include")
endif()

# Native library path
set(NETHOST_NATIVE_PATH "/usr/share/dotnet/packs/${DOTNET_PACK_NAME}/${DOTNET_VERSION}/runtimes/${DOTNET_RID}/native")
if(WIN32)
    set(NETHOST_NATIVE_PATH "$ENV{ProgramFiles}/dotnet/packs/${DOTNET_PACK_NAME}/${DOTNET_VERSION}/runtimes/${DOTNET_RID}/native")
endif()

include_directories(${NETHOST_INCLUDE})

# Platform-specific copy
if(WIN32)
    set(NETHOST_DLL "${NETHOST_NATIVE_PATH}/nethost.dll")
elseif(UNIX)
    set(NETHOST_DLL "${NETHOST_NATIVE_PATH}/libnethost.so")
endif()