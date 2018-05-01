LIBNAME=libarray
SRC=array.c
OBJ=array.o

all: static-lib dynamic-lib

static-lib:
	$(CC) -std=c99 -c $(SRC) -o $(OBJ) -DLIBARRAY_STATIC -Iinclude -g
	@ar -rcu $(LIBNAME).a $(OBJ)
	@ranlib $(LIBNAME).a

dynamic-lib:
	$(CC) -std=c99 -shared -fPIC -o $(LIBNAME).so $(SRC) -Iinclude

test: static-lib
	$(CC) -o test main.c -Iinclude -L. -larray -g

booltest: static-lib
	$(CC) -o booltest booltest.c -Iinclude -L. -larray -g

.PHONY: clean

clean:
	@rm -f $(OBJ) $(LIBNAME).a $(LIBNAME).so test booltest
