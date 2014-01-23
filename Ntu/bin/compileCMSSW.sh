#!/bin/sh

cd `dirname $0`/..
export PD_PACK_DIR=`/bin/pwd`
cd ../..
export PD_ROOT_DIR=`/bin/pwd`
echo $PD_PACK_DIR
echo $PD_ROOT_DIR

export PD_EXE_FILE=${PD_PACK_DIR}/bin/treeAnalyzeCMSSW
rm -f ${PD_EXE_FILE}

c++ -Wall `root-config --cflags`              \
-I ${PD_ROOT_DIR} -I ${NTU_TOOL_DIR}/include  \
-o ${PD_EXE_FILE}                             \
${PD_PACK_DIR}/src/*.cc                       \
${PD_PACK_DIR}/bin/PDAnalyzerInstance.cc      \
-L${NTU_TOOL_DIR}/lib/${SCRAM_ARCH} -lNtupleTool_${CMSSW_VERSION} `root-config --glibs`
#${PD_PACK_DIR}/src/PDAnalyzerFW.cc           \
#${PD_PACK_DIR}/src/PDNtuple.cc               \
#${PD_PACK_DIR}/src/PDNtupleData.cc           \
#${PD_PACK_DIR}/src/PDEventSelect.cc          \


echo ${PD_EXE_FILE}
