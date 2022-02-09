#!/bin/bash

# libs externes
export X11_ROOT=/usr/local/Cellar/libx11/1.7.0
export XEXT_ROOT=/usr/local/Cellar/libxext/1.3.4
export GLU_ROOT=/usr/local/Cellar/mesa-glu/9.0.1
export OMP_ROOT=/usr/local/Cellar/libomp/11.1.0
export CXX=/usr/local/opt/llvm/bin/clang

#useless if SOCLE_EXTERN_ROOT initialized
export QT5_ROOT=/Users/nbellaiche/dev/sd-externs/macosx-clang/qt-5.14.1
export BOOST_ROOT=/Users/nbellaiche/dev/sd-externs/macosx-clang/boost_1_73_0
export BOOST_VERSION=73

if [ "1$CXX" == "1" ]; then
    echo "env var CXX is required"
    exit 1
else
    echo compiler CXX: $CXX
fi

export LD=$CXX

if [ "1$SOCLE_EXTERN_ROOT" != "1" ]; then
    localenv=macosx-clang
    . $SOCLE_EXTERN_ROOT/$localenv/library_config.sh
    . $SOCLE_EXTERN_ROOT/$localenv/library_config_new.sh
    . $SOCLE_EXTERN_ROOT/$localenv/setenv.sh
    . $SOCLE_EXTERN_ROOT/$localenv/setdeps.sh
    echo QT5_ROOT: $QT5_ROOT
    export CMAKE_MODULE_PATH="$SOCLE_EXTERN_ROOT/CMakeModules"
else
    if [ "1$QT5_ROOT" == "1" ]; then
        echo "env var QT5_ROOT is required"
        exit 1
    fi
    if [ "1$X11_ROOT" == "1" ]; then
        echo "env var X11_ROOT is required"
        exit 1
    fi
    if [ "1$XEXT_ROOT" == "1" ]; then
        echo "env var XEXT_ROOT is required"
        exit 1
    fi
    if [ "1$GLU_ROOT" == "1" ]; then
        echo "env var GLU_ROOT is required"
        exit 1
    fi
    if [ "1$OMP_ROOT" == "1" ]; then
        echo "env var OMP_ROOT is required"
        exit 1
    fi
    if [ "1$BOOST_ROOT" == "1" ]; then
        echo "env var BOOST_ROOT is required"
        exit 1
    fi
fi

export BOOST_INCLUDES=$BOOST_ROOT/include/boost-1_$BOOST_VERSION

QTLIB_NAMES="QtCore QtGui QtXml QtOpenGL QtWidgets QtConcurrent"

export QT5_LIBS

for QTLIB_NAME in $QTLIB_NAMES
do
    export QT5_LIBS="$QT5_LIBS ${QT5_ROOT}/lib/$QTLIB_NAME\.framework/$QTLIB_NAME ${QT5_ROOT}/lib/$QTLIB_NAME.framework/$QTLIB_NAME"
done

export isdebug="" #"-g"

export ExtraLibsFlags="-L${OMP_ROOT}/lib -lc++ -headerpad_max_install_names $isdebug"

export CExtraFlags="\"-stdlib=libc++\" \"-Wno-inconsistent-missing-override\" \"-Wno-undefined-var-template\" \"-Wno-mismatched-tags\" \"-Wno-unused-value\" \"-Wno-delete-abstract-non-virtual-dtor\" \"-Wno-unused-private-field\" \"-Wno-unused-function\" \"-O3\" \"$isdebug\" \"-DFORSWIG\""

echo =============================
#make clean
#make -f Mk-MMVII.makefile -j4 VERBOSE=1
make -j4 VERBOSE=1

./MMVII  GenCodeSymDer
echo "**********************************************************************"
echo Pass 1
echo "**********************************************************************"

 make -j4 VERBOSE=1

# rpath
for QTLIB_NAME in $QTLIB_NAMES
do
    install_name_tool -change @rpath/$QTLIB_NAME.framework/Versions/5/$QTLIB_NAME $QT5_ROOT/lib/$QTLIB_NAME.framework/Versions/5/$QTLIB_NAME ./MMVII
done
otool -L MMVII
