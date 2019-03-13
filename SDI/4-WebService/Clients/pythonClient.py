import os
import time

from threading import Thread
from threading import Lock
from zeep.client import Client

name = ""
start = 0
done = False
msgList = []

lock = Lock()

def threadGet(client):

    while(not done):
        time.sleep(2)
        cont = len(msgList)

        lock.acquire()
        while(  client.service.compareSizes(start + len(msgList)) ):
            msg = client.service.getMessage( len(msgList) + start )
            msgList.append(msg)
        lock.release()

        if(cont != len(msgList) ):
            printMessages()


def quickGet(client):
    os.system('clear')

    cont = len(msgList)
    lock.acquire()
    while(  client.service.compareSizes(start + len(msgList)) ):
        msg = client.service.getMessage( len(msgList) + start )
        msgList.append(msg)

    lock.release()

    if(cont != len(msgList) ):
        return True
    else:
        return False


def printMessages():
    os.system('clear')
    for mes in msgList:
        print(mes)
    print('-------------')

def chat(client):
    global done
    os.system('clear')
    print("Bem vindo ao chat!")
    msg = ""
    while( not done ):
        if(quickGet(client)):
            printMessages()

        msg = input()

        if(msg == "/quit"):
            done = True

        client.service.sendMessage(msg, name)


def main():
    os.system('clear')

    global name
    global start

    print("Digite o seu nome: ")
    name = input()

    client = Client('http://192.168.100.7:9998/WSHello?wsdl')
    start = client.service.chatConnect(name)

    ct = Thread(target = threadGet, args = (client, ) )
    ct.start()

    chat(client)


if __name__ == "__main__": main()


'''
# Is this what you call backup?

def threadGet(client):
    global start

    cont = start
    while(not done):
        os.system('clear')
        msg = ""
        while(msg != "#end#"):
            msg = client.service.getMessage(cont)
            print(msg)
            cont = cont + 1
        print(">> ", end="")

        time.sleep(5)


def quickGet(client):
    os.system('clear')
    global start

    cont = start
    msg = ""

    while(msg != "\n"):
        msg = client.service.getMessage(cont)
        if(msg == "\n"):
            break
        print(msg)
        cont = cont + 1

    print(">> ", end="")
'''
