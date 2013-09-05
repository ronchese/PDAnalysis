#!/bin/sh

cd `dirname $0`/..
export PD_PACK_DIR=`/bin/pwd`
cd ../..
export PD_ROOT_DIR=`/bin/pwd`

export PD_EXE_FILE=${PD_PACK_DIR}/bin/treeAnalyze
rm -f ${PD_EXE_FILE}

c++ `root-config --cflags --glibs` \
-I ${PD_ROOT_DIR} -I ${NTU_TOOL_DIR}/include \
-o ${PD_PACK_DIR}/bin/treeAnalyze \
${PD_PACK_DIR}/bin/PDAnalyzerInstance.cc \
${PD_PACK_DIR}/src/PDAnalyzerFW.cc \
${PD_PACK_DIR}/src/PDNtuple.cc \
${PD_PACK_DIR}/src/PDNtupleData.cc \
${PD_PACK_DIR}/src/PDEventSelect.cc \
-L${NTU_TOOL_DIR}/lib -lNtupleTool

echo ${PD_EXE_FILE}
