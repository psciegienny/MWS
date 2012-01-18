LDFLAGS= -lboost_filesystem -lboost_thread
CXX=g++
BASE=${CURDIR}
SRC=${BASE}/src
INCLUDE=${BASE}/include
BIN=${BASE}/bin
TMP=${BASE}/tmp
CXXFLAGS= -I${BASE}/include/ -I${BASE}/include/utils/
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
export TMP
export BASE
export SRC
export INCLUDE
RTTT: torgiren creammy czaju
	${CXX} ${BIN}/*.o ${BIN}/utils -o $@ ${LDFLAGS}
torgiren:
	${MAKE} -f src/Makefile.torgiren
torgiren_run: torgiren
	./tmp/main.torgiren
czaju:
	${MAKE} -f src/Makefile.czaju
czaju_run: czaju
	./tmp/main.czaju
creammy:
	${MAKE} -f src/Makefile.creammy
creammy_run: creammy
	./tmp/main.creammy
docs:
	doxygen Doxyfile
clean:
	rm -f ${BIN}/*

.PHONY: torgiren creammy czaju clean docs
