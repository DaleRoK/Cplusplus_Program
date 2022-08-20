import re
import string

def ItemCount():

    f = open("Items.txt", "r")  ##opens file
    itemList = f.read().splitlines()    ##reads file into list
    f.close()   ##closes file
    occurrence = {item: itemList.count(item) for item in itemList}  ##Creates unique list of items from itemList
    
    for i in occurrence:    ##loop to iterate through occurrence list and output each item and their frequency of occurrence
        print(i, " - ", itemList.count(i))

def UniqueItemFrequency(i):

    f = open("Items.txt", "r")  ##opens file
    itemList = f.read().splitlines()    ##reads file into list
    f.close()   ##closes file
    
    return itemList.count(i)    ##returns the count of unique item passed from original function call

def DisplayHistogram():
    
    f = open("Items.txt", "r")  ##Opens file to read from
    itemList = f.read().splitlines()    ##Reads file into a list
    f.close()   ##Closes file
    occurrence = {item: itemList.count(item) for item in itemList}  ##Creates unique list of items from itemList

    f = open("frequency.dat", "w")  ##Opens file to write to
    for i in occurrence:    ##for loop to write unique items from occurrence list
        f.write(i + " " + str(itemList.count(i)))
    f.close ##closes file


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v



    
