#!/usr/bin/env python3
import csv
#print ("hello")
num = 0
sum = 0
long = 7
lat = 8

max_number = 10

print(max_number)

with open('../data/file1.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    for row in reader:
        num += 1
        if num == 1:
            continue

        val_lat = int(row[lat])/1000/3600
        val_long = int(row[long])/1000/3600

#        print("{ latitude: ",val_lat ,", longitude: ",val_long," },")
        print(val_lat,  val_long)


        if num > max_number:
            break

