from conans import ConanFile, CMake, tools
import os


class UsulConan(ConanFile):
    name = "usul"
    version = "3.1.0"
    license = "https://opensource.org/licenses/mit-license.html"
    author = "Perry L Miller IV (perry@modelspace.com)"
    url = "https://github.com/perryiv/usul"
    description = "Low-level C++ utility code"
    topics = ( "low-level", "C++", "utility" )
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "build_tests": [True, False]
    }
    default_options = {
        "shared": True,
        "build_tests": True
    }
    # no_copy_source = True
    # generators = "cmake"

    def config_options(self):
        if self.settings.build_type == "Release":
            self.options.shared = True

    def build_requirements(self):
        if self.options.build_tests:
            self.build_requires("Catch2/[^2.9.1]@catchorg/stable")

    def build(self):
        cmake = CMake(self)
        defs = {
            "USUL_BUILD_TESTS": self.options.build_tests,
            "CMAKE_ARCHIVE_OUTPUT_DIRECTORY": os.path.join(self.build_folder, "lib"),
            "CMAKE_DEBUG_POSTFIX": "",
            "CMAKE_INSTALL_RPATH": "\\$ORIGIN",
            "CMAKE_LIBRARY_OUTPUT_DIRECTORY": os.path.join(self.build_folder, "lib"),
            "CMAKE_RUNTIME_OUTPUT_DIRECTORY": os.path.join(self.build_folder, "bin"),
        }
        if self.options.build_tests:
            defs["Catch2_ROOT"] = self.deps_cpp_info["Catch2"].rootpath
        cmake.configure(defs=defs)
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["usul"]
        if not self.options.shared:
            self.cpp_info.defines = [
                "USUL_STATIC_DEFINE"
            ]
        if not self.in_local_cache:
            self.cpp_info.includedirs = [
                "source", os.path.join("build", self.settings.build_type.value, "config")
            ]

    def package_id(self):
        super().package_id()
        del self.info.options.build_tests
