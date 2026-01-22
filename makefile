CC = gcc
TARGET = stu_out

SRCS = main.c stu_execute.c 
OBJS = $(SRCS:.c=.o)
HDRS = stu_header.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC)  -o $(TARGET) $(OBJS)


%.o: %.c $(HDRS)
	$(CC)  -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)