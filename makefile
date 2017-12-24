# Tomer Addady 207162678

CXX = g++
#CXXFLAGS = -std=c++0x
RM = rm -f
#LIBS = -pthread -lboost_serialization -I.


a.out: core.o makeO
	$(CXX) $(CXXFLAGS) @compile.txt

core.o:
	find src -name "*.cpp" > sources.txt
	$(CXX) $(CXXFLAGS) -c @sources.txt

makeO:
	find -name "*.o" > compile.txt
	sed -i '/cmake-build-debug/d' ./compile.txt

clean:
	$(RM) *.o
	$(RM) sources.txt
	$(RM) compile.txt
