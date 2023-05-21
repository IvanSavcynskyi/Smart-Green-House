import eel
import matplotlib.pyplot as plt
import requests
import lxml
from bs4 import BeautifulSoup

def sort(data): 
    for i in range(len(data)):
        minimum = i
        for j in range(i + 1, len(data)):
            if data[j] < data[minimum]:
                minimum =j 
            data[minimum], data[i] = data[i], data[minimum]
    return data

def get_data_from_site():

    url = "http://192.168.0.111/api"

    req = requests.get(url)
    src = req.text
    soup = BeautifulSoup(src, "lxml")

    data = []

    data.append(soup.find(class_="humidity").text)
    data.append(soup.find(class_="air_humidity").text + "%")
    data.append(soup.find(class_="air_temperature").text + "*")
    
    return(data)

def get_data():

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

    air_humidity = sort(air_humidity)
    humidity = sort(humidity)
    air_temperature = sort(air_temperature)

    return(humidity, air_humidity, air_temperature)

@eel.expose
def create_graph_air_humidity():

    air_humidity=get_data()[0]

    plt.plot(air_humidity)
    plt.title("Air Humidity")
    plt.show()

@eel.expose
def create_graph_humidity():

    humidity=get_data()[1]

    plt.plot(humidity)
    plt.title("Humidity")
    plt.show()

@eel.expose
def graph_air_temperature():

    air_temperature=get_data()[2]

    plt.plot(air_temperature)
    plt.title("Air Temperature")
    plt.show()

@eel.expose
def send_humidity_now():
    return(get_data_from_site()[0])

@eel.expose
def send_air_humidity():
    return(get_data_from_site()[1])

@eel.expose
def send_air_temperature():
    return(get_data_from_site()[2])

def main():
    eel.init("./program/web")
    eel.start("index.html", size=(930, 800))

if __name__=="__main__":
    main()

