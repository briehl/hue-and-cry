import requests

class Request:
    # All the methods are like this:
    # ip = ip address of the router
    # uid = username of the app
    # command = the full-on command. e.g. for modifying a light,
    #       it would be 'lights/<id>/state'
    # data = optional, should be a dict (will get JSONified)
    #       e.g. to shut off a light, {'on': False}
    def get(ip, uid, command, data=None):
        pass

    def put(ip, uid, command, data=None):
        pass

    def post(ip, uid, command, data=None):
        pass

    def delete(ip, uid, command, data=None):
        pass