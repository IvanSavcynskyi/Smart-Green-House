import matplotlib.pyplot as plt

with open("data.txt", "r") as file:
    data = file.readlines()
    data_rep = []
    for n in data:
        n=n.replace("["," ")
        n=n.replace("]"," ")
        n=n.replace(","," ")
        n=n.replace("'"," ")
        n=n.strip()
        data_rep.append(n)

data_list=[]
for n in data_rep:
    n=n.split("    ")
    data_list.append(n)

humidity=[]
for n in data_list:
    humidity.append(n[0])

air_humidity=[]
for n in data_list:
    air_humidity.append(n[1])

air_temperature=[]
for n in data_list:
    air_temperature.append(n[2])

def selection_sort(arr): 
    for i in range(len(arr)):
        minimum = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[minimum]:
                minimum =j 
            arr[minimum], arr[i] = arr[i], arr[minimum]
    return arr

air_humidity = selection_sort(air_humidity)
humidity = selection_sort(humidity)
air_temperature = selection_sort(air_temperature)

# plt.figure()

# plt.subplot(1,2,1)
plt.plot(air_humidity)

# plt.subplot(1,2,2)
plt.plot(humidity)

# plt.subplot(2,1,1)
plt.plot(air_temperature)

plt.show()

