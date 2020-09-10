from conans import ConanFile, CMake, tools


class UsulConan(ConanFile):
    name = "usul"
    version = "3.1.0"
    license = "https://opensource.org/licenses/mit-license.html"
    author = "Perry L Miller IV (perry@modelspace.com)"
    url = "https://github.com/perryiv/usul"
    description = "Low-level C++ utility code"
    topics = ( "low-level", "C++", "utility" )
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "build_tests": [True, False]}
    default_options = {"shared": True, "build_tests": False}
    generators = "cmake"

    def build_requirements(self):
        if self.options.build_tests:
            self.build_requires("Catch2/[^2.9.1]@catchorg/stable")

    def build(self):
        cmake = CMake(self)
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
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["usul"]
        if not self.options.shared:
            self.cpp_info.defines = ["USUL_STATIC_DEFINE"]

    def package_id(self):
        super().package_id()
        del self.info.options.build_tests
