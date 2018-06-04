SERVERDIR = server

SERVEROBJS = $(OBJDIR)/server_main.o

$(OBJDIR)/server_main.o: $(SERVERDIR)/main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(SERVER) : $(SERVEROBJS)
	$(LD) -o $@ $(SERVEROBJS) $(LIBS)

