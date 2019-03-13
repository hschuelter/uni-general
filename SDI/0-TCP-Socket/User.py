class User:
    def __init__(self):
        self.id = -1
        self.nickname = ""
        self.socket = ""
        self.address = ""

    def __init__(self, id, nickname, socket, address):
        self.id = id
        self.nickname = nickname
        self.socket = socket
        self.address = address

    def say(self, data):
        print(self.nickname + " (#" + str(self.id) + ")" + ": " + data)
