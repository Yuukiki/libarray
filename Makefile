LIBNAME=libarray
SRC=array.c
OBJ=array.o

all: static-lib dynamic-lib

static-lib:
	$(CC) -c $(SRC) -o $(OBJ) -DLIBARRAY_STATIC -Iinclude
	@ar -rcu $(LIBNAME).a $(OBJ)
	@ranlib $(LIBNAME).a

dynamic-lib:
	$(CC) -shared -fPIC -o $(LIBNAME).so $(SRC) -Iinclude


.PHONY: clean

clean:
	@rm -f $(OBJ) $(LIBNAME).a $(LIBNAME).so
