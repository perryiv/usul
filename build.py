# from cpt.packager import ConanMultiPackager
import sys
import os

if __name__ == "__main__":

    if os.getenv ( "THIS_JOB_USE_DOCKER" ) == "1":
        os.environ["CONAN_DOCKER_IMAGE"] = os.environ["THIS_JOB_DOCKER_IMAGE"]
        os.environ["CONAN_USE_DOCKER"] = "1"
        print ( "Going to use docker" )

    if sys.platform.startswith ( "linux" ):
        os.environ["CONAN_GCC_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "This is Linux" )

    if sys.platform.startswith ( "darwin" ):
        os.environ["CONAN_APPLE_CLANG_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "This is Mac" )

    if sys.platform.startswith ( "win32" ):
        os.environ["CONAN_VISUAL_VERSIONS"] = os.environ["THIS_JOB_COMPILER_VERSION"]
        print ( "This is Windows" )

    print ( os.environ )

    # builder = ConanMultiPackager(archs=["x86_64"])
    # builder.add_common_builds()
    # builder.run()
