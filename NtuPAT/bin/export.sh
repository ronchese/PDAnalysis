#!/bin/sh

cd `dirname $0`/../../..
export PD_PATH=PDAnalysis/NtuPAT
export PD_PACK=`pwd`/pdAnalysis.tgz
rm -f ${PD_PACK}
tar -czf ${PD_PACK} \
${PD_PATH}/interface/PDNtupleData.h     \
${PD_PATH}/interface/PDNtupleBranch.h   \
${PD_PATH}/interface/PDNtupleBranch.icc \
${PD_PATH}/interface/PDNtuple.h         \
${PD_PATH}/interface/PDEventSelect.h    \
${PD_PATH}/src/PDNtupleData.cc          \
${PD_PATH}/src/PDNtuple.cc              \
${PD_PATH}/src/PDEventSelect.cc         \
${PD_PATH}/src/PDAnalyzerFW.cc          \
${PD_PATH}/bin/PDAnalyzer.h             \
${PD_PATH}/bin/PDAnalyzer.cc            \
${PD_PATH}/bin/PDAnalyzerUtil.h         \
${PD_PATH}/bin/PDAnalyzerUtil.cc        \
${PD_PATH}/bin/PDAnalyzerInstance.cc    \
${PD_PATH}/bin/compile.csh               \
${PD_PATH}/bin/TreeLightReader.h         \
${PD_PATH}/bin/PDLightNtuple.h          \
${PD_PATH}/bin/PDLightNtuple.cc         \
${PD_PATH}/bin/PDMacro.C                \
${PD_PATH}/bin/setupMacroAnalysis.csh    \
${PD_PATH}/bin/export.sh
echo ${PD_PACK}
