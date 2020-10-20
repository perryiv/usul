set -e
set -x
python --version
pip --version
python -m pip install --upgrade pip
pip install conan --upgrade
pip install conan_package_tools
conan user
