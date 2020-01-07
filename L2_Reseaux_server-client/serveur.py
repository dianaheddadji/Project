import socket
import select

hote = ''
port = 2222

#Création d'une socket pour établir une connexion côté serveur
main_connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#Connexion du socket côté serveur avec la méthode bind pour attendre une connexion du client
main_connection.bind((hote, port))

#Nombre maximum de connexions que le serveur peut recevoir sur ce port sans les accepter
main_connection.listen(5)

print("Connected now on the port {}".format(port))

serveur_on = True
connected_client = []

#Accepter une connexion venant du client
connection_client, connection_info = main_connection.accept()

while serveur_on:
	connexion_requested, list1, list2 = select.select([main_connection], [], [], 0.05)

	for connexion in connexion_requested:
		connection_client, connection_info = connexion.accept()
		#On ajoute le socket connecté à la liste des clients
		connected_client.append(connection_client)
	read_client = []
	try:
		read_client, list1, list2 = select.select(connected_client, [], [], 0.05)
	except select.error:
		pass
	else:#liste des clients à lire
		for client in read_client:
			msg_received = client.recv(2000)
			msg_received = msg_received.decode()
			msg_received = msg_received.rstrip()
			print(connection_info)
			print("Received {} ".format(msg_received))
			client.send(b"OK")
			if msg_received == "BYE":
				serveur_on = False

print("closed connection")
for client in  connected_client:
	client.close()
main_connection.close()
