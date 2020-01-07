import socket
import sys 

hote = "localhost"
port = 2222

if len(sys.argv) != 3:
    sys.stderr.write("Usage: %s host port\n" % sys.argv[0])
    sys.exit(1)

#name = input("Enter your name: ")

#Création du socket pour la connexion côté client
connection_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Connecter le client
connection_server.connect((hote, port))

print(" {}".format(port))


msg_send = b""
while msg_send != b"BYE":
	msg_send = input("> ")
	msg_send = msg_send.encode()
	connection_server.send(msg_send)
	msg_received  = connection_server.recv(2000)
	print(msg_received .decode())

#Fermer la connexion
print("closed connection")
connection_server.close()

