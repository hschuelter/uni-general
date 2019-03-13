import time
import sys
import os
import socket
from threading import Thread
##

MULTICAST = ('224.0.0.1', 12345)
HOST = '192.168.100.7'
PORT = 54321

class User:
    def __init__(self, id, name):
        self.id = id
        self.name = name

def setup():

    multicast_addr = '224.0.0.1'
    bind_addr = '0.0.0.0'
    port = 12345

    sckt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    membership = socket.inet_aton(multicast_addr) + socket.inet_aton(bind_addr)
    sckt.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, membership)
    sckt.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sckt.bind((bind_addr, port))

    return sckt

def printChat(msg):
    os.system('clear')
    for m in msg:
        print(m)

    print("\n>> ")

def receiveMessages(sock, usuario):
    msg = [""]
    printChat(msg)
    while True:
        data = sock.recv(1024)

        ch = 0
        for i in range(0, len(data) ):
            if data[i] == '%':
                ch = i

        user = data[0:ch]
        mss = data[ch+1 : len(data) ]

        if(mss == "."):
            if(user == usuario.name):
                return
            else:
                print(user + " se desconectou!")

        pack = ""
        if( user == "&SERVER&"):
            pack = mss
        else:
            pack = user + ": " + mss


        if(len(msg) >= 30):
            del msg[0]
        msg.append(pack)

        printChat(msg)

def main():
    os.system('clear')
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    nome = raw_input("Digite seu nome: ")
    sock.sendto("&CONNECT&%" + nome + " se conectou!", (HOST, PORT) )
    data = sock.recvfrom(65536)

    user = User(int(data[0]), nome)

    sock = setup()


    ct = Thread(target = receiveMessages, args = (sock, user, ) )
    ct.start()

    while True:
        msg = raw_input(">>\n")
        sock.sendto(user.name + "%" +  msg, MULTICAST )
        if(msg == "."):
            break

    print("Ay-OK")

if __name__ == "__main__": main()
