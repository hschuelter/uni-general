import pika
import os
from threading import Thread, Lock


done = False
msgList = []

sender = None
receiver = None
name = ""

def setup():
	global sender, receiver, name

	connection = pika.BlockingConnection(pika.ConnectionParameters(
                                        host='localhost'))
	receiver = connection.channel()
	receiver.queue_declare(queue = ("chat-" + name) )

	sender = connection.channel()
	sender.queue_declare(queue='server')


def send(msg):
	global sender
	sender.basic_publish(exchange='',
                      routing_key='server',
                      body=msg)

def chat():
	global done, sender, name

	while(not done):
		print("> ", end = "")
		msg = input()

		if(msg == ".quit"):
			done = True
			send(name + " saiu")
		else:
			send(name + ": " + msg)

def receiveMessages():
	global receiver
	receiver.basic_consume(callback,
                          queue=('chat-' + name),
                          no_ack=True)

	receiver.start_consuming()

def callback(ch, method, properties, body):
	os.system("clear")
	msg = str(body, "utf-8")
	msgList.append(msg)

	for m in msgList:
		print(m)


def main():
	global name
	print("Bom dia, digite o seu nome: ", end="")
	name = input()

	setup()

	ct = Thread(target = receiveMessages, args = ( ) )
	ct.start()

	chat()
	connection.close()

if __name__ == "__main__": main()

