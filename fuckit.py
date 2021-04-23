#! /usr/bin/python
from urllib.request import urlopen
import os

def Mount():
    os.system('mount //192.168.1.138/public/Music /harbinger/ -o user=orpheus -o password=kodi')

def Mpd():
    os.system('systemctl start mpd')

def ND():
    os.system('nd && poweroff')

def internet_on():
    try:
        response = urlopen('http://192.168.1.138', timeout=10)
        return True
    except: 
        return False


while(internet_on() == False):
    #sleep maybe?
    shitvar=1

Mount()
Mpd()
ND()

