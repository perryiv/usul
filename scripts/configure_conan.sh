set -e
set -x
python3 -m pip install --upgrade pip
pip3 install conan --upgrade
pip3 install conan_package_tools
conan user
