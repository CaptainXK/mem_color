.PHONY:clean

SRCS := $(wildcard *.c)
OBJ_DIR := obj
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS) )


test.app:check_obj_dir $(OBJS)
	gcc $(OBJS) -o $@ -g

check_obj_dir:
	@if test ! -d $(OBJ_DIR);\
	then\
		mkdir $(OBJ_DIR);\
	fi

$(OBJ_DIR)/%.o:%.c
	gcc -c $< -o $@ -g

test:test.app
	$(EXEC) ./test.app

clean:
	rm -r $(OBJ_DIR)/*.o *.app