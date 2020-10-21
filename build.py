from cpt.packager import ConanMultiPackager
import sys
import os

if __name__ == "__main__":

    if os.environ["CONAN_USE_DOCKER"] == "1":
        os.environ["CONAN_DOCKER_IMAGE"] = os.environ["THIS_JOB_DOCKER_IMAGE"]
        print ( "Setting CONAN_DOCKER_IMAGE to ", os.environ["CONAN_DOCKER_IMAGE"] )

    print ( "Operating system = ", sys.platform )

    # builder = ConanMultiPackager(archs=["x86_64"])
    # builder.add_common_builds()
    # builder.run()
