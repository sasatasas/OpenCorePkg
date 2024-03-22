#!/bin/bash

abort() {
  echo "ERROR: $1!"
  exit 1
}

cd "$(dirname "$0")" || exit 1

# Build OpenCorePkg 
ARCHS=X64
NO_ARCHIVES=0
TOOLCHAINS=CLANGDWARF
TARGETS=DEBUG
SELFPKG=OpenCorePkg
DISCARD_SUBMODULES=OpenCorePkg
if [ "$OVMF_PATH" = "" ]; then
  OVMF_PATH='./UDK/Build'
fi
if [ "$GROUP" = "" ]; then
  GROUP=UNDEFINED
fi

export ARCHS
export NO_ARCHIVES
export TOOLCHAINS
export TARGETS
export SELFPKG
export DISCARD_SUBMODULES
export GROUP

BUILD_ARGUMENTS=-D"$GROUP"
export BUILD_ARGUMENTS

src=$(curl -LfsS https://raw.githubusercontent.com/acidanthera/ocbuild/master/efibuild.sh) || exit 1
eval "$src" || exit 1

for target in "${TARGETS[@]}"; do
  for arch in "${ARCHS[@]}"; do
    for toolchain in "${TOOLCHAINS[@]}"; do
      mkdir -p ./UDK/Build/OpenCorePkg/"$target"_"$toolchain"/"$arch"/EFI/BOOT
      cp ./UDK/Build/OpenCorePkg/"$target"_"$toolchain"/"$arch"/UbsanTester.efi ./UDK/Build/OpenCorePkg/"$target"_"$toolchain"/"$arch"/EFI/BOOT/BOOT"$arch".efi
    done
  done
done

# Test UBSan
if [ ! -f "./test_qemu_fw.py" ] || [ ! -f "./test_ubsan.py" ]; then
  curl -LfsSO https://raw.githubusercontent.com/sasatasas/ocbuild/master/test_ubsan.py || exit 1
  curl -LfsSO https://raw.githubusercontent.com/sasatasas/ocbuild/master/test_qemu_fw.py || exit 1
fi

for target in "${TARGETS[@]}"; do
  for arch in "${ARCHS[@]}"; do
    for toolchain in "${TOOLCHAINS[@]}"; do
      echo Checking Ovmf"$arch" "$target"_"$toolchain"
      mkdir -p ./TestsOutput/"$target"_tests
      python3 ./test_ubsan.py "$OVMF_PATH"/Ovmf"$arch"/"$target"_"$toolchain"/FV/OVMF.fd --build-path ./UDK/Build/OpenCorePkg/"$target"_"$toolchain"/"$arch"/ --fw-arch "$arch" --test-ubsan-group "$GROUP" --tests-dir-path ./TestsOutput/"$target"_tests
    done
  done
done
