LDFLAGS= -lboost_filesystem -lboost_thread
CXX=g++
BASE=${CURDIR}
SRC=${BASE}/src
INCLUDE=${BASE}/include
BIN=${BASE}/bin
TMP=${BASE}/tmp
CXXFLAGS= -I${BASE}/include/
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
export TMP
export BASE
export SRC
export INCLUDE

czaju:
	${MAKE} -f src/Makefile.czaju
czaju_client:
	${MAKE} -f src/Makefile.czaju.client
