import csv
#print ("hello")
num = 0
sum = 0
long = 7
lat = 8

with open('../data/file1.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    for row in reader:
        #print("---------------------------")
        #print('\ndata: '.join(row))
        num += 1
        if num == 1:
            continue

        val_lat = int(row[lat])/1000/3600
        val_long = int(row[long])/1000/3600
#        print("lat=", val_lat, " long=", val_long)
        print("{ latitude: ",val_lat ,", longitude: ",val_long," },")
#        print(val_lat,  val_long)

#{ latitude: 56.249452, longitude: 43.883379 },
#{ latitude: 56.247892, longitude: 43.884382 },
#{ latitude: 56.248537, longitude: 43.880477 }

        #print("num=", num, "val=", val)
        #sum += val
        if num > 500:
            break

#print("n=",num)
#print("mean=", sum/num)
