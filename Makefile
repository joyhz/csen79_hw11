# Names: Abraham Bhatti, David Lopez-Ryan, Sebastian Ortiz Ayala, Joy Zhu
# Emails: abhatti@scu.edu, rlopezryan@scu.edu, sortizayala@scu.edu, jhzhu@scu.edu
CXX=c++
OPT=-g
STD=-std=c++20
CXXFLAGS=$(OPT) $(STD)

%.o:	%.cxx
	$(CXX) -c $(CXXFLAGS) $<

SRCS=bag.cxx bagtest.cxx
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
bag.o: bag.cxx bag.h
bagtest.o: bagtest.cxx bag.h
