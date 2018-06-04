# socket-example

this demo is from the book: Unix Network Programming Volume1: The Sockets NetWorking API

## echo (this is the first example)
(1)the client read a line from stdin and send to the server
(2)the server send the line to the client
(3)the client print it on the screen
tips: 
(1)use makefile to compile and run the server
make 
make start
make stop   #shut down the server
(2)you should start the client manually