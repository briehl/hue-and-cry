class Bridge():
    def __init__(self, ip=None, username=None):
        if ip is not None:
            self.ip = ip
        if username is not None:
            self.username = username