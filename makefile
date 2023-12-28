CC := gcc
CPPFLAGS := -MMD
CFLAGS := -Wall -march=native -Ofast
LDFLAGS := -lSDL2

SRCDIR := ./src
OBJDIR := ./obj

SRCS := $(patsubst ${SRCDIR}/%,%,$(wildcard ${SRCDIR}/*.c))
OBJS := $(patsubst %.c,%.o,${SRCS})

BIN := $(shell basename ${CURDIR})

${BIN}: $(addprefix ${OBJDIR}/,${OBJS})
ifndef LDFLAGS
	${CC} -o $@ $^
else
	${CC} ${LDFLAGS} -o $@ $^
endif

${OBJDIR}/%.o: ${SRCDIR}/%.c | ${OBJDIR}
ifndef CFLAGS
	${CC} ${CPPFLAGS} -o $@ -c $<
else
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $<
endif

${OBJDIR}:
	mkdir ${OBJDIR}

.PHONY: clean
clean:
	rm -r ${BIN} $(wildcard ${OBJDIR}/*)

-include $(addprefix ${OBJDIR}/,$(patsubst %.o,%.d,${OBJS}))
