import time
import sys
import os
import socket
from threading import Thread
###
from Queue import Queue
from User import User

def printChat(msg):
    os.system('clear')
    for m in msg:
        print(m)

    print("\n>> ")

def receiveMessages(server):
    msg = []
    while True:
        data = server.recv(1024)
        if(data == "/sair"): break

        else:
            ch = 0
            for i in range(0, len(data) ):
                if data[i] == '%':
                    ch = i
            m = ""

            if(data[0:ch] == "&SERVER&"):
                m += data[ch+1 : len(data) ]
            else:
                m += data[0:ch]
                m += ": "
                m += data[ch+1 : len(data) ]


            if(len(msg) >= 30):
                del msg[0]
            msg.append(m)

        printChat(msg)

def main():
    os.system('clear')

    sock = socket.socket()
    sock.connect( ('localhost', 1234))
    packet = raw_input("Digite seu nome: ")
    sock.send(packet)


    os.system('clear')
    print("Seja bem-vindo(a), " + packet)

    ct = Thread(target = receiveMessages, args = (sock, ) )
    ct.start()

    while True:
        data = raw_input(">>\n")

        if( data == "/sair"):
            sock.send(data)
            break
        else:
            sock.send(data)


    # data = sock.recv(1024)
    # print(data)

if __name__ == "__main__": main()
