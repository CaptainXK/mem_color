.PHONY:clean

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS) )

test.app:$(OBJS)
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@

test:test.app
	$(EXEC) ./test.app

clean:
	rm -r *.o *.app