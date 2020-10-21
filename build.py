from cpt.packager import ConanMultiPackager
import os

if __name__ == "__main__":

    if os.environ["CONAN_USE_DOCKER"] == "1"
        os.environ["CONAN_DOCKER_IMAGE"] = os.environ["THIS_JOB_DOCKER_IMAGE"]

    print "Operating system = ", os.uname().sysname

    # builder = ConanMultiPackager(archs=["x86_64"])
    # builder.add_common_builds()
    # builder.run()
