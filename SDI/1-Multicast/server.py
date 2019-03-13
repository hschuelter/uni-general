import time
import sys
import struct
import os
import socket
from threading import Thread
##

MULTICAST = ('224.0.0.1', 12345)
HOST = '192.168.100.7'
PORT = 54321


def setup():
    global MULTICAST
    global HOST
    global PORT

    sckt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sckt.settimeout(10.0)
    ttl = struct.pack('b', 1)
    sckt.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)


    receiver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    receiver.bind((HOST, PORT))

    return sckt, receiver

def main():
    os.system('clear')
    sckt, receiver = setup()
    print("Aguardando conexoes...")
    _id_ = 0;

    while True:
        data, address = receiver.recvfrom(65536)

        ch = 0
        for i in range(0, len(data) ):
            if data[i] == '%':
                ch = i

        user = data[0:ch]
        msg = data[ch+1 : len(data) ]

        if(user == "&CONNECT&"):
            pack = str(_id_)

        receiver.sendto(pack, address)
        sckt.sendto("&SERVER&%" + msg, MULTICAST)

        print(msg)

    print("Ay-OK")

if __name__ == "__main__": main()
