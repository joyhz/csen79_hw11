# Names: Abraham Bhatti, David Lopez-Ryan, Sebastian Ortiz Ayala, Joy Zhu
# Emails: abhatti@scu.edu, rlopezryan@scu.edu, sortizayala@scu.edu, jhzhu@scu.edu
CXX=c++
OPT=-g
STD=-std=c++20
WARN=-Wall
CXXFLAGS=$(OPT) $(STD) $(WARN)

%.o:	%.cxx
	$(CXX) -c $(CXXFLAGS) $<

SRCS=bagtest.cxx person.cxx
OBJS=$(SRCS:.cxx=.o)

all: bag

bag:	$(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm bag $(OBJS)
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
bagtest.o: bagtest.cxx bag.h person.h
person.o: person.cxx person.h
