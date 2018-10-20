#!/usr/bin/env python3
import csv
import datetime
from datetime import timezone
from datetime import timedelta

id_long = 7
id_lat = 8
id_time = 1
id_time_gps = 14

max_number = 3

# print(max_number)

# 2018-08-01 05:34:55 +0300 MSK


def convert_time(tm_str):
    date_time_obj = datetime.datetime.strptime(tm_str, '%Y-%m-%d %H:%M:%S +0300 MSK')
    delta = date_time_obj - datetime.datetime(1970, 1, 1)
    delta -= timedelta(hours=3)
    return int(delta.total_seconds())


def print_data(row):
    for value in row:
        print(value)


def print_data_full(row):
    print("-----------------------")
    for pos, value in enumerate(row):
        print(pos, " Data: ", value)

def print_data_file(resfile, row):
    for value in row:
        resfile.write(str(value) + '\n')

def process_file(file_base_name):
    num = 0
    file_name = "../data/" + file_base_name + ".csv"
    file_result = "../data/result/" + file_base_name + ".txt"

    with open(file_name, newline='') as csvfile:
        with open(file_result, "w" ) as resfile:
            reader = csv.reader(csvfile, delimiter=',', quotechar='"')
            for row in reader:

                #print_data_full(row)

                num += 1
                if num == 1:
                    continue

                row[id_lat] = float(row[id_lat])/1000.0/3600
                row[id_long] = float(row[id_long])/1000.0/3600

                row[id_time] = convert_time(row[id_time])
                row[id_time_gps] = convert_time(row[id_time_gps])

                #print_data_full(row)
                # print_data(row)
                print_data_file(resfile, row)

                #if num > max_number:
                #    break


def process_list(file_list):
    with open("../data/result/processed_files.txt", "w") as proc_files:
        for name in file_list:
            process_file(name)
            print(name + ".txt" + "\n")
            proc_files.write(name + ".txt" + "\n")


file_list_full = ["Q00000000000000D-1533081600-1535760000_1",
             "Q00000000000000D-1533945600-1535760000_2",
             "Q00000000000000D-1533945600-1535760000_3",
             "Q00000000000000E-1533081600-1535760000_1",
             "Q00000000000000E-1535155200-1535760000_2",
             "Q00000000000000F-1533081600-1535759999_1",
             "Q00000000000000F-1534291200-1535759999_2"
             ]

file_list_1 = ["file2"]

#process_list(file_list_1)
process_list(file_list_full)

#name = '../data/file1.csv'
#process_file(name)