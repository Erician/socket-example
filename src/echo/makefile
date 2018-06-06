.PHONY: clean 

OBJDIR = ../../obj/echo

SERVER = $(OBJDIR)/server
CLIENT = $(OBJDIR)/client
PRODUCTS = $(SERVER) $(CLIENT)
default: $(PRODUCTS)

include server/makefile
include client/makefile

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  

# Define the tools we are going to use
CC= gcc
LD = gcc

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -I.

LIBS = -lc -lm

start: $(PRODUCTS)
	@$(SERVER) &
	@netstat -lpn | grep "server" | grep "^tcp" 

stop: $(PRODUCTS)
	@for pid in `ps -ef | grep '../../obj/echo/server' | grep -v 'grep' | tr -s " " | cut -d " " -f 2`; do echo "kill "$${pid}; kill $${pid}; done
	
#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest

clean:
	@rm -f $(JUNK) $(PRODUCTS) 


