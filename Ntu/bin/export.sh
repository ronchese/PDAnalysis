#!/bin/sh

cd `dirname $0`/../../..
export PD_PATH=PDAnalysis/Ntu
export PD_PACK=`pwd`/pdAnalysis.tgz
rm -f ${PD_PACK}
tar -czf ${PD_PACK}                   \
${PD_PATH}/interface/*.h              \
${PD_PATH}/interface/*.icc            \
${PD_PATH}/src/*.cc                   \
${PD_PATH}/bin/*.h                    \
${PD_PATH}/bin/*.cc                   \
${PD_PATH}/bin/compile.sh             \
${PD_PATH}/bin/compile.csh            \
${PD_PATH}/bin/PDMacro.C              \
${PD_PATH}/bin/PDProof.mac            \
${PD_PATH}/bin/setupMacroAnalysis.csh \
${PD_PATH}/bin/export.sh
echo ${PD_PACK}
