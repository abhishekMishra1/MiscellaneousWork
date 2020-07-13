#!/usr/bin/python
import os

os.rename("sample.txt", "fileIO.txt")
os.remove("fileIO.txt")

os.mkdir("testDir")
os.getcwd()
os.chdir("testDir")
os.chdir("../")


