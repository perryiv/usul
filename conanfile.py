from conans import python_requires
import glob, os, subprocess

intel = python_requires("intel_helper/0.0.0@vaone-dev/master")


class Usul(intel.ConanFile):
    name = "usul"
    version = "3.0.0"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "build_tests": [True, False]}
    default_options = {"shared": True, "build_tests": False}
    no_copy_source = True
    scm = {"type": "git", "url": "auto", "revision": "auto"}
    revision_mode = "scm"

    def build_requirements(self):
        if self.options.build_tests:
            self.build_requires("Catch2/[^2.9.1]@catchorg/stable")

    def build(self):
        cmake = intel.CMake(self)
        defs = {
            "CMAKE_BUILD_WITH_INSTALL_RPATH": True,
            "CMAKE_DEBUG_POSTFIX": "",
            "USUL_BUILD_TESTS": self.options.build_tests,
        }
        if self.options.build_tests:
            defs["Catch2_ROOT"] = self.deps_cpp_info["Catch2"].rootpath
        cmake.configure(defs=defs)
        cmake.build()

    def package(self):
        cmake = intel.CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["usul"]
        if not self.options.shared:
            self.cpp_info.defines = ["USUL_STATIC_DEFINE"]

    def package_id(self):
        super().package_id()
        del self.info.options.build_tests
