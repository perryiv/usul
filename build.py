from cpt.packager import ConanMultiPackager
import sys
import os

if __name__ == "__main__":

    if sys.platform.startswith ( "linux" ):
        os.environ["CONAN_GCC_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "Building on Linux" )

    if sys.platform.startswith ( "darwin" ):
        os.environ["CONAN_APPLE_CLANG_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "Building on Mac" )

    if sys.platform.startswith ( "win32" ):
        os.environ["CONAN_VISUAL_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "Building on Windows" )

    if os.getenv ( "THIS_JOB_USE_DOCKER" ) == "1":
        os.environ["CONAN_DOCKER_IMAGE"] = os.environ["THIS_JOB_DOCKER_IMAGE"]
        os.environ["CONAN_USE_DOCKER"] = "1"
        print ( "Going to use docker" )

    standard = os.environ["THIS_JOB_CPP_STANDARD"]

    builder = ConanMultiPackager(
        archs=["x86_64"]
    )
    builder.add_common_builds()
    for conf in builder.items:
        conf.settings["compiler.cppstd"] = standard
    builder.run()
