import time
import sys
import os
import socket
from threading import Thread

import dropbox

# ------ #

folder = '/aluno4/'
token = "SEGURANCA_EM_PRIMEIRO_LUGAR"

global_message_list = []
loop = True
# app_key = "KIBE"
# app_secret = "KIBE"

def setup():
    global token
    os.system('clear')

    dbx = dropbox.Dropbox(token)    

    return dbx

def login(dbx):
    global folder
    repete = True

    print("Bom dia fera!")

    folder_list = dbx.files_list_folder(folder).entries

    while(repete):
        print("Digite o seu nick: ", end="")
        nickname = input()
        repete = False
        os.system('clear')

        for entry in folder_list:
            if(entry.name == nickname):
                print("Este nick já está em uso...")
                repete = True

    print('Logando como ' + nickname + '...')
    try:
        dbx.files_upload("".encode(), folder + nickname + '/_SEND_.txt')
        dbx.files_upload("".encode(), folder + nickname + '/_READ_.txt')

    except Exception as err:
        print("OPS!\n%s" % err)

    return nickname

def logout(dbx, nickname):
    dbx.files_delete(folder + nickname)

def sendMessages(dbx, nickname):
    global folder, loop
    
    while(loop):
        meta, f = dbx.files_download(folder + nickname + '/_SEND_.txt')
        message_list = str(f.content, 'utf-8').split('\n')
        
        msg = nickname + ": " + input("")

        if('.exit' in msg):
            loop = False
            msg = nickname + " saiu"

        message_list.append(msg)
        packet = convertMessage(message_list).encode()


        dbx.files_delete(folder + nickname + '/_SEND_.txt')
        dbx.files_upload(packet, folder + nickname + '/_SEND_.txt')

def getMessages(dbx, nickname):
    global global_message_list, loop

    while(loop):
        
        try:
        
            meta, f = dbx.files_download(folder + nickname + '/_READ_.txt')
            message_list = str(f.content, 'utf-8').split('\n')

            if (message_list != global_message_list):
                global_message_list = message_list
                printMessages(global_message_list)

        except Exception as err:
            a = 0

        time.sleep(2)


def printMessages(message_list):
    os.system('clear')

    for m in message_list:
        print(m)

    print("====")


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
    nickname = login(dbx)

    ct = Thread(target = getMessages, args = (dbx, nickname, ) )
    ct.start()

    sendMessages(dbx, nickname)


    logout(dbx, nickname)
    


if __name__ == "__main__": 
    # parser = argparse.ArgumentParser(description="Chat Dropbox")

    # parser.add_argument('--port', '-p',
    #                     type=int,
    #                     help="Porta de rede",
    #                     default="10000")

    # args = parser.parse_args()
    main()