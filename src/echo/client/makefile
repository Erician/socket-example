CLIENTDIR = client

CLIENTOBJS = $(OBJDIR)/client_main.o

$(OBJDIR)/client_main.o: $(CLIENTDIR)/main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(CLIENT) : $(CLIENTOBJS)
	$(LD) -o $@ $(CLIENTOBJS) $(LIBS)