import time
import sys
import os
import socket
from threading import Thread

import dropbox
# ------ #

folder = '/aluno4/'
token = "SEGURANCA_EM_PRIMEIRO_LUGAR"

clients = []
cl_messages = []
global_message_list = []

def setup():
    global token
    os.system('clear')

    dbx = dropbox.Dropbox(token)    

    return dbx

def roda(dbx):
    global folder, clients, cl_messages, global_message_list

    folders = []
    folder_list = dbx.files_list_folder(folder).entries
    for entry in folder_list:
        folders.append(entry.name)

        if(entry.name not in clients):
            clients.append(entry.name)

    for cl in clients:
        cl_messages.append([])


    while(True):
        folders = []
        new_clients = []

        # Verifica os clientes que ainda estão online
        folder_list = dbx.files_list_folder(folder).entries
        for entry in folder_list:
            new_clients.append(entry.name)

        new_cl_messages = []
        for cl in new_clients:
            new_cl_messages.append([])

        # Pega as mensagens dos arquivos dos clientes
        for i in range(0, len(new_clients)):
            mensagens = getMessages(dbx, new_clients[i])
            if(mensagens == -1):
                for j in range(0, len(clients)):
                    if(new_clients[i] == clients[j]):
                        new_cl_messages[i] = cl_messages[j]
            else:
                new_cl_messages[i] = mensagens


        # Verifica se existem mensagens novas
        # Em caso positivo adiciona no vetor de mensagens global
        for i in range(0, len(new_clients)):
            if(new_clients[i] not in clients):
                for m in new_cl_messages[i]:
                    global_message_list.append(m)
            else:
                for j in range(0, len(clients)):
                    if(new_clients[i] == clients[j]):
                        old_size = len(cl_messages[j])
                        new_size = len(new_cl_messages[i])

                        if(new_size > old_size):
                            for k in range(old_size, new_size):
                                global_message_list.append(new_cl_messages[i][k])
        
        os.system('clear')
        for m in global_message_list:
            print(m)

        packet = convertMessage(global_message_list).encode()

        for cli in new_clients:
            sendMessages(dbx, cli, packet)


        # list_debug(new_clients, folders, remove_list)
        clients = new_clients
        cl_messages = new_cl_messages
        time.sleep(2)

def sendMessages(dbx, client, packet):
    global folder

    over = False
    try:
        dbx.files_delete(folder + client + '/_READ_.txt')
        dbx.files_upload(packet, folder + client + '/_READ_.txt')
        over = True

    except Exception as err:
        over = False


def getMessages(dbx, cl):
    global folder, clients
    
    message_list = []

    try:
        meta, f = dbx.files_download(folder + cl + '/_SEND_.txt')
        message_list = str(f.content, 'utf-8').split('\n')
        
        return message_list[1:]

    except Exception as err:

        return -1

def convertMessage(message_list):
    new_message = ""
    for m in message_list:
        new_message += m
        new_message += '\n'
    
    new_message = new_message[0:-1]
    return new_message

def main():
    global folder

    dbx = setup()
    roda(dbx)
    


if __name__ == "__main__": 
    # parser = argparse.ArgumentParser(description="Chat Dropbox")

    # parser.add_argument('--port', '-p',
    #                     type=int,
    #                     help="Porta de rede",
    #                     default="10000")

    # args = parser.parse_args()
    main()