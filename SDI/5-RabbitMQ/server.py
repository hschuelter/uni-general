import pika
import os
from threading import Thread, Lock

a = 0
ch = None

clients = []
connection = None

def callback(ch, method, properties, body):

	m = str(body, "utf-8")
	print(m)
	analyze(m)

	sendToAll(m)

def analyze(msg):
	client = ""
	for c in msg:
		if c == ":":
			break
		client += c
	addClient(client)

def addClient(cl):
	global clients
	b = True

	for i in clients:
		if i == cl:
			b = False
			break
	if(b == True):
		clients.append(cl)

def sendToAll(msg):
	global clients, connection

	for c in clients:
		ch = connection.channel()
		ch.queue_declare(queue = "chat-" + c)
		ch.basic_publish(exchange='', routing_key = "chat-" + c, body = msg)

def main():
	global connection
	connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost'))

#	ct = Thread(target = receiveConnections, args = (connection, ) )
#	ct.start

	channel = connection.channel()
	channel.queue_declare(queue='server')
	channel.basic_consume(callback,
                          queue='server',
                          no_ack=True)

	print(' [*] Waiting for messages. To exit press CTRL+C')
	channel.start_consuming()

if __name__ == "__main__": main()
