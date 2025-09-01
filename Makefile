CFLAGS=-Wall -Werror -Wextra
SRCS = main.cpp Product.cpp ProductDatabase.cpp Receipt.cpp Shift.cpp
OBJS = $(SRCS:.cpp=.o)

all: clean rmk

rmk: $(OBJS)
	g++ $(CFLAGS) -o $@ $^

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

run: rmk
	./rmk

clean:
	rm -rf $(OBJS) rmk