CXX=g++
RM=rm -rf
CPPFLAGS=-g
LDFLAGS=-g
SRCS:= $(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))
MAIN_BIN=mini_aes

all: $(MAIN_BIN)

$(MAIN_BIN): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(MAIN_BIN) $(OBJS)

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

COMPILE.c = $(CXX) $(DEPFLAGS) $(CPPFLAGS) -c

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d | $(DEPDIR)
	$(COMPILE.c) $<

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))

clean:
	$(RM) $(OBJS)
	$(RM) .deps

distclean: clean
	$(RM) $(MAIN_BIN)
