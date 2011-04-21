import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('', 6667))
sock.listen(5)
while 1:
    clientsocket, address = sock.accept()
    print sock.recv(1024)

# This server will output all data sent to it, assuming the packets are one MB
# or smaller.  There is a bug in some releases of Python that causes this to
# crash on connect.
