import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class MeanPixelRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/2.30.8")
        self.requires("sol2/3.3.1")
        self.requires("glm/cci.20230113")


    def layout(self):
        cmake_layout(self)