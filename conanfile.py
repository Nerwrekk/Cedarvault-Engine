import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class CederVaultRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("spdlog/1.14.1")
        self.requires("sdl/2.28.3")
        self.requires("sdl_image/2.6.3")
        self.requires("sol2/3.3.1")
        self.requires("glm/cci.20230113")
        self.requires("imgui/cci.20230105+1.89.2.docking")
        self.requires("glew/2.2.0")
        self.requires("stb/cci.20240531")

    def generate(self):
        copy(self, "*sdl*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(f"{self.source_folder}/Engine/vendor/imgui", "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(f"{self.source_folder}/Engine/vendor/imgui", "bindings"))


    def layout(self):
        cmake_layout(self)