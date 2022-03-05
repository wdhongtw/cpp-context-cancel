
CPPFLAGS += -g

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(OBJS) $(TARGET)
