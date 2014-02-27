#!/bin/sh

cd `dirname $0`/..
export PD_PACK_DIR=`/bin/pwd`
cd ../..
export PD_ROOT_DIR=`/bin/pwd`
echo $PD_PACK_DIR
echo $PD_ROOT_DIR

export PD_EXE_FILE=${PD_PACK_DIR}/bin/treeAnalyze
rm -f ${PD_EXE_FILE}

c++ -Wall `root-config --cflags`              \
-I ${PD_ROOT_DIR} -I ${NTU_TOOL_DIR}/include  \
-o ${PD_EXE_FILE}                             \
${PD_PACK_DIR}/src/*.cc                       \
${PD_PACK_DIR}/bin/PDAnalyzerInstance.cc      \
-L${NTU_TOOL_DIR}/lib -lNtupleTool            \
`root-config --glibs`


echo ${PD_EXE_FILE}
