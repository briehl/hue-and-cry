class Bridge():
    def __init__(self, ip=None, username=None):
        if ip is not None:
            self._ip = ip
        # TODO: scan local network for ip
        if username is not None:
            self._username = username
        # TODO: look first in config file for username, then prompt
        # to push The Button then listen for a new username

