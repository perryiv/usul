from conans import CMake, CMakeToolchain, ConanFile, tools
import os


class UsulConan(ConanFile):
    name = "usul"
    version = "3.1.0"
    license = "MIT"
    author = "Perry L Miller IV (perry@modelspace.com)"
    url = "https://github.com/perryiv/usul"
    description = "Low-level C++ utility code"
    topics = "low-level", "C++", "utility"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "run_tests": [True, False],
    }
    default_options = {"shared": False, "run_tests": True}

    scm = {"type": "git", "url": "auto", "revision": "auto"}
    revision_mode = "scm"

    no_copy_source = True
    generators = "cmake_find_package",

    def requirements(self):
        if self.options.run_tests:
            self.requires("catch2/2.13.0", private=True)

    def toolchain(self):
        toolchain = CMakeToolchain(self)
        toolchain.definitions["USUL_BUILD_TESTS"] = self.options.run_tests
        toolchain.definitions["USUL_ENABLE_CODE_COVERAGE"] = False
        toolchain.definitions["CMAKE_DEBUG_POSTFIX"] = ""
        toolchain.definitions["CMAKE_VERBOSE_MAKEFILE"] = True
        toolchain.write_toolchain_files()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.options.run_tests:
            cmake.test(output_on_failure=True)

    def package(self):
        cmake = CMake(self)
        cmake.install()
        self.copy(pattern="License.md", dst="licenses")

    def package_info(self):
        self.cpp_info.libs = ["usul"]
        if not self.options.shared:
            self.cpp_info.defines = ["USUL_STATIC_DEFINE"]
        if not self.in_local_cache:
            self.cpp_info.includedirs = [
                "source",
                os.path.join("build", self.settings.build_type.value, "config")
            ]

    def package_id(self):
        del self.info.options.run_tests
