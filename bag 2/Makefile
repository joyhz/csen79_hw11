# Sin-Yaw Wang <swang24@scu.edu>
CXX=c++
OPT=-g
STD=-std=c++20
CXXFLAGS=$(OPT) $(STD)

%.o:	%.cxx
	$(CXX) -c $(CXXFLAGS) $<

SRCS=person.cxx bagtest.cxx
OBJS=$(SRCS:.cxx=.o)

all: bagtest

bagtest:	$(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f bagtest $(OBJS)
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
person.o: person.cxx person.h
bagtest.o: bagtest.cxx bag.h person.h
