#CPPFLAGS=  -Wall -g -O -fPIC
CPPFLAGS= -fPIC -g 

all: bin
#all: lib

bin: KinAna BJetAna
lib: libweight.so

######################## Main library ###############################################
KinAna: KinAna.C KinAna.h
	g++ $(CPPFLAGS) -o $@ `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE KinAna.C -lEG -lProof

BJetAna: BJetAna.C BJetAna.h
	g++ $(CPPFLAGS) -o $@ `root-config --libs` -I`root-config --incdir` -I${CMSSW_RELEASE_BASE}/src -L${CMSSW_RELEASE_BASE}/lib/${SCRAM_ARCH} -std=c++17 -D STANDALONE BJetAna.C -lEG -lProof

libweight.so: KinAna.C KinAna.h BJetAna.C BJetAna.h
	g++ $(CPPFLAGS) -shared -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE KinAna.C
	g++ $(CPPFLAGS) -shared -o $@ `correction config --cflags --ldflags --rpath` `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE BJetAna.C

######################## Main library ###############################################

clean:
	rm -f src/*.o *.so *.root KinAna BJetAna

