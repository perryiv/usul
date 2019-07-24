from conans import python_requires
import glob, os, subprocess

intel = python_requires("intel_helper/0.0.0@vaone-dev/master")


class Usul(intel.ConanFile):
    name = "usul"
    version = "0.1.0"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False]}
    default_options = {"shared": True}
    no_copy_source = True
    scm = {"type": "git", "url": "auto"}

    def build(self):
        cmake = intel.CMake(self)
        cmake.configure(
            defs={"CMAKE_BUILD_WITH_INSTALL_RPATH": True, "CMAKE_DEBUG_POSTFIX": ""}
        )
        cmake.build()

    def package(self):
        cmake = intel.CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["usul"]
        if not self.options.shared:
            self.cpp_info.defines = ["USUL_STATIC_DEFINE"]
