import time
import sys
import os
import socket
from threading import Thread
###
from Queue import Queue
from User import User


online_users = []
id = 0

def setup(max):
    os.system('clear')
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind( ('localhost', 1234) )
    sock.listen(max) # Maximum ammount of chat users

    print("Servidor aguardando conexoes...")
    return sock

def printUsers():
    global online_users
    print("Usuarios online: ")

    for u in online_users:
        print( "\t" + u.nickname)

def printCommands():
    print("Comandos:")
    print("  ~> /online: para ver os usuarios online")
    print("  ~> /sair: para sair do chat")

def addUser(name, client, address):
    global id
    global online_users

    # for user in online_users:
    #     if client == user.socket:
    #         return User(-1, "", "", "")

    user = User(id, name, client, address)
    id += 1

    online_users.append(user)
    return user

def delUser(user):
    global id
    global online_users

    online_users.remove(user)

def sendMessages(user, data):
    global online_users

    for u in online_users:
        u.socket.send(user.nickname + "%" + data)

def receiveMessages(client, user, sock):
    global online_users
    server = User(-1, "&SERVER&", "", "")

    while True:
        data = client.recv(1024)
        if(not data): break

        if (data == "/online"):
            printUsers()

        elif (data == "/comandos"):
            printCommands()

        elif(data == "/sair"):
            print(user.nickname + " saiu do chat")
            client.send("/sair")

            delUser(user)
            sendMessages(server, user.nickname + " saiu do chat")
            break

        else:
            sendMessages(user, data)
            user.say(data)

def main():
    global online_users
    server = User(-1, "&SERVER&", "", "")

    sock = setup(5)

    while True:
        (client, address) = sock.accept()
        name = client.recv(1024)

        print(name + " se conectou!")
        sendMessages(server, name + " se conectou!")
        user = addUser(name, client, address)

        if(user.id != -1):
            ct = Thread(target = receiveMessages, args = (client, user, sock, ) )
            ct.start()



if __name__ == "__main__": main()
