LIBNAME=libarray
SRCS += array.c
SRCS += arraylog.c
OBJS = $(SRCS:.c=.o)
SOBJS = $(OBJS)
CFLAGS += -std=c99 -g -Werror -Wextra
CFLAGS += -Iinclude -fPIC -Wall -Werror -Wextra

all: static-lib dynamic-lib

static-lib: $(OBJS)
	@ar -rcu $(LIBNAME).a $(OBJS)
	@ranlib $(LIBNAME).a

dynamic-lib: $(OBJS)
	$(CC) -shared -fPIC -o $(LIBNAME).so $(OBJS)

test: static-lib
	$(CC) -o test main.c -Iinclude -L. -larray -g -Werror -Wextra -Wall -Wl,--rpath,$(PWD)

booltest: static-lib
	$(CC) -o booltest booltest.c -Iinclude -L. -larray -g -Werror -Wextra -Wall -Wl,--rpath,$(PWD)

.PHONY: clean

clean:
	@rm -f $(OBJS) $(LIBNAME).a $(LIBNAME).so test booltest
