FLAGS = -Wall -g -std=gnu99 
DEPENDENCIES = helper.h

all: psort mkwords

mkwords: mkwords.o
	gcc ${FLAGS} -o $@ $^ -lm

psort: psort.o helper.o
	gcc ${FLAGS} -o $@ $^

%.o: %.c ${DEPENDENCIES}
	gcc ${FLAGS} -c $<

clean: 
	-rm -f *.o psort mkwords