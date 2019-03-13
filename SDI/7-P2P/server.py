import argparse
import time
import sys
import os
import socket
from threading import Thread, Lock

users = []
m_id = -1

dictionary = {}

def setup(port, max):
    global users, m_id

    os.system('clear')
    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    skt.bind( ('localhost', port) )

    # Maximum ammount of chat users
    skt.listen(max) 

    print("Servidor aguardando conexoes...")
    m_id = 0

    return skt

def printUsers():
    global users

    os.system('clear')
    print("Users online:")
    for u in users:
        print('\t', end="")
        print(u)

def main(port, max):
    global users, messages, msg_list, dictionary, m_id
    skt = setup(port, max)

    while True:
        (client, address) = skt.accept()
        info = str(client.recv(1024), 'utf-8')
        aux = info.split("$")

        if (aux[0] == "CONNECT"):
            packet = ""
            if(len(users) > 0):
                for u in users:
                    packet = packet + u[0] + "$" + str(u[1]) + '\n'
                packet = packet[:-1]
            
            if (packet == ""):
                packet = "$"
            
            client.send( packet.encode() )            
            client.close()
            users.append( (aux[1], int(aux[2])) )

        elif (aux[0] == "LOGOUT"):
            tu = ((aux[1], int(aux[2])))
            if(tu in users):
                users.remove(tu)
            client.send("OK".encode())

            for i in dictionary:
                if(tu in dictionary[i]):
                    dictionary[i].remove(tu)

            client.close()

        elif (aux[0] == "MSG"):
            client.send(str(m_id).encode())

            address = ( address[0], int(aux[2]) )

            dictionary[m_id] = []
            dictionary[m_id].append(address)

            m_id += 1
            client.close()

        elif (aux[0] == "UPDATE"):
            client.send(str(m_id).encode())
            client.close()

        elif (aux[0] == "GET"):
            num = int(aux[1])

            packet = str(dictionary[num][0][0]) + "$" + str(dictionary[num][0][1]) 
            client.send(packet.encode())

            dictionary[num].append(address)         

            client.close()

        printUsers()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Chat P2P")

    parser.add_argument('--port', '-p',
                        type=int,
                        help="Porta de rede",
                        default="10000")

    parser.add_argument('--max', '-m',
                        type=int,
                        help="Numero maximo de usuarios",
                        default=10)

    args = parser.parse_args()
    main(args.port, args.max)
