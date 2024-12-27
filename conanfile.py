import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class MeanPixelRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("spdlog/1.14.1")
        self.requires("sdl/2.28.3")
        self.requires("sdl_image/2.6.3")
        self.requires("sol2/3.3.1")
        self.requires("glm/cci.20230113")


    def layout(self):
        cmake_layout(self)