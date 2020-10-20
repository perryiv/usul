set -e
set -x
sudo python3 -m pip install --upgrade pip
sudo pip3 install conan --upgrade
sudo pip3 install conan_package_tools
conan user
