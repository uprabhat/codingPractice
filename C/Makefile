CC = gcc            # default is CC = cc
CFLAGS = -g -Wall -fsanitize=address    # default is CFLAGS = [blank]
CPPFLAGS =          # default is CPPFLAGS = [blank]
LDFLAGS = -lpthread -fsanitize=address  # default is LDFLAGS = [blank]
### File to compile $(CODE).c ###

# default compile command: $(CC) $(CFLAGS) $(CPPFLAGS) -c -o <foo>.o <foo>.c

all: code

code: $(CODE).c
	$(CC) -o $(CODE) $< $(CFLAGS) $(LDFLAGS)
#$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)
# default linking command: $(CC) $(LDFLAGS) <foo>.o -o <foo>

clean:
	$(RM) -f *.o $(CODE)
