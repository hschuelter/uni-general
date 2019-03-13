import argparse
import time
import sys
import os
import socket
import random as rnd
from threading import Thread

ip_address = ''
server_port = -1
client_port = -1
users = []

#
messages = []
main_loop = True

def setup(address, sp):
    global ip_address, server_port, client_port, users

    ip_address = address

    # Setting up the server socket
    done = False
    while not done:
        try:
            server_port = rnd.randint(1026, 10000)

            server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server.bind( (ip_address, server_port) )
            server.listen(10)
            done = True

        except Exception as err:
            done = False

    users.append( (ip_address, server_port) )

    # Setting up the client socket
    done = False
    print("Aguardando servidor...")
    while not done:
        try:
            client_port = rnd.randint(1026, 10000)

            client = socket.socket()            
            client.bind( (ip_address, client_port) )
            client.connect( (ip_address, sp) )
            done = True

        except Exception as err:
            done = False    

    name = input("Digite seu nome: ")
    
    packet = "CONNECT$" + users[0][0] + "$" + str(users[0][1])
    client.send(packet.encode())

    packet = str(client.recv(1024), 'utf-8')

    if (packet != "$"):

        aux = packet.split("\n")
        for a in aux:
            t = a.split("$")
            users.append( (t[0], int(t[1])) )

    print(users)
    client.close()

    return server, name

def logout(address, sp):
    global server_port, ip_address

    done = False
    while not done:
        try:
            client_port = rnd.randint(1026, 10000)

            skt = socket.socket()            
            skt.bind( (ip_address, client_port) )
            skt.connect( (ip_address, sp) )
            done = True

        except Exception as err:
            done = False

    packet = "LOGOUT$" + users[0][0] + "$" + str(users[0][1])
    skt.send(packet.encode())
    packet = str(skt.recv(1024), 'utf-8')

    skt.close()

def printMessages():
    global messages

    os.system('clear')

    for m in messages:
        print(m)
    print("===")
    
def receivePeer(server):
    global messages, main_loop

    while(main_loop):
        (client, address) = server.accept()
        info = str(client.recv(1024), 'utf-8')
        aux = info.split("$")

        if (aux[0] == "GET"):
            num = int(aux[1])

            packet = str(messages[num])
            client.send(packet.encode())    

            client.close()

def receiveMessages(sp):
    global messages, main_loop, ip_address, new_message

    while(main_loop):

        done = False
        while not done:
            try:
                cp = rnd.randint(1026, 10000)

                skt = socket.socket()            
                skt.bind( (ip_address, cp) )
                done = True

            except Exception as err:
                done = False

        
        try:
            skt.connect( (ip_address, sp) )
            packet = "UPDATE"
            skt.send(packet.encode())

            msg = str(skt.recv(1024), 'utf-8')
            skt.close()
        
        except:
            a = False

        update = int(msg)

        while(update > len(messages)):
            messages.append("")
        
        flag = False

        for i in range(0, len(messages)):
            flag = True
            if(messages[i] == ""):
                address = getPeerAddress(i, sp)
                msg = getPeerMessage(i, address)
                messages[i] = msg

        if( flag ):
            printMessages()

        time.sleep(2)

def getPeerAddress(num, sp):
    done = False
    while not done:
        try:
            cp = rnd.randint(1026, 10000)

            skt = socket.socket()            
            skt.bind( (ip_address, cp) )
            done = True

        except Exception as err:
            done = False
    
    skt.connect( (ip_address, sp) )
    packet = "GET$" + str(num)
    print(packet)
    skt.send(packet.encode())

    msg = str(skt.recv(1024), 'utf-8')
    skt.close()
    
    msg = msg.split("$")
    return ( msg[0], int(msg[1]) )

def getPeerMessage(num, address):

    done = False
    while not done:
        try:
            cp = rnd.randint(1026, 10000)

            skt = socket.socket()            
            skt.bind( (ip_address, cp) )
            done = True

        except Exception as err:
            done = False

    print(address)

    skt.connect( address )
    packet = "GET$" + str(num)
    print(packet)
    skt.send(packet.encode())

    packet = str(skt.recv(1024), 'utf-8')
    skt.close()

    return packet



def sendAll(msg, sp):
    global users, ip_address, server_port

    remove_list = []
    done = False
    while not done:
        try:
            cp = rnd.randint(1026, 10000)

            skt = socket.socket()            
            skt.bind( (ip_address, cp) )
            done = True

        except Exception as err:
            done = False


    packet = "MSG$" + msg + "$" + str(server_port)
    skt.connect( (ip_address, sp) )
    skt.send(packet.encode())
    packet = str(skt.recv(1024), 'utf-8')

    num = int(packet)
    
    while( num >= len(messages) ):
        messages.append("")

    messages[num] = msg

    for rm in remove_list:
        users.remove(rm)


def main(address, sp):
    global main_loop, messages, lock

    server, name = setup(address, sp)
    printMessages()
    
    receiver = Thread(target = receiveMessages, args = (sp, ) )
    receiver.start()

    peers = Thread(target = receivePeer, args = (server, ) )
    peers.start()

    while(main_loop):
        msg = input()
        if (msg == ".exit"):
            logout(address, sp)
            print("Fim")
            main_loop = False

        else:
            msg = name + ": " + msg
            messages.append(msg)

            sendAll(msg, sp)
            printMessages()


if __name__== "__main__": 
    parser = argparse.ArgumentParser(description="Chat P2P")

    parser.add_argument('--address', '-a',
                        type=str,
                        help="Endereco IP",
                        default="localhost")

    parser.add_argument('--server_port', '-sp',
                        type=int,
                        help="Porta do Servidor",
                        default=1024)

    args = parser.parse_args()
    main(args.address, args.server_port)