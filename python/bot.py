import requests
import lxml
from bs4 import BeautifulSoup
import telebot
from telebot import types

bot = telebot.TeleBot("BotToken", parse_mode=None)

def get_data():
    
    url = "http://192.168.0.109/api"

    req = requests.get(url)
    src = req.text
    soup = BeautifulSoup(src, "lxml")

    data = []

    data.append(soup.find(class_="humidity").text)
    data.append(soup.find(class_="air_humidity").text + "%")
    data.append(soup.find(class_="air_temperature").text + "*")
    
    return(data)

def check_data(data):

    # Температура повітря: 18-25
    # Вологість грунту: 30 мм
    # Трохи більша ніж в людей
    
    check = []

    if int(data[0][:-1]) >= 60 and int(data[0][:-1]) <= 70:
        check.append("good")
    elif int(data[0][:-1]) >= 50 and int(data[0][:-1]) <= 80:
        check.append("normal")
    elif int(data[0][:-1]) <= 50:
        check.append("bad-")
    else:
        check.append("bad+")

    if float(data[1][:-1]) >= 55 and float(data[1][:-1])  <= 65:
        check.append("good")
    elif float(data[1][:-1]) >= 45 and float(data[1][:-1]) <= 70:
        check.append("normal")
    elif float(data[1][:-1]) <= 45:
        check.append("bad-")
    else:
        check.append("bad+")

    if float(data[2][:-1]) >= 19 and float(data[2][:-1]) <= 22:
        check.append("good")
    elif float(data[2][:-1]) >= 17.5 and float(data[2][:-1]) <= 25:
        check.append("normal")
    elif float(data[2][:-1]) <= 17.5:
        check.append("bad-")
    else:
        check.append("bad+")

    return(check)

def bot_send_data():

    @bot.message_handler(commands=['data'])
    def send_data(message):
        
        data = get_data()
        check = check_data(data)

        if check[0] == "good":
            bot.send_message(message.chat.id, f"Вологість грунту: {data[0]} \nЦе добре для вашої рослинки!")
        elif check[0] == "normal":
            bot.send_message(message.chat.id, f"Вологість грунту: {data[0]} \nЦе нормально для вашої рослинки!")
        elif check[0] == "bad+":
            bot.send_message(message.chat.id, f"Вологість грунту: {data[0]} \nЦе погано для вашої рослинки! Ви занадто сильно полилии  її!")
        elif check[0] == "bad-":
            bot.send_message(message.chat.id, f"Вологість грунту: {data[0]} \nЦе погано для вашої рослинки! Полийте рослинку!") 

        if check[1] == "good":
            bot.send_message(message.chat.id, f"Вологість повітря: {data[1]} \nЦе добре для вашої рослинки!")
        elif check[1] == "normal":
            bot.send_message(message.chat.id, f"Вологість повітря: {data[1]} \nЦе нормально для вашої рослинки!")
        elif check[1] == "bad+":
            bot.send_message(message.chat.id, f"Вологість повітря: {data[1]} \nЦе погано для вашої рослинки! Поставте її в холодок!")
        elif check[1] == "bad-":
            bot.send_message(message.chat.id, f"Вологість повітря: {data[1]} \nЦе погано для вашої рослинки! Зволожіть рослинку!") 

        if check[2] == "good":
            bot.send_message(message.chat.id, f"Температура повітря: {data[2]} \nЦе добре для вашої рослинки!")
        elif check[2] == "normal":
            bot.send_message(message.chat.id, f"Температура повітря: {data[2]} \nЦе нормально для вашої рослинки!")
        elif check[2] == "bad+":
            bot.send_message(message.chat.id, f"Температура повітря: {data[2]} \nЦе погано для вашої рослинки! Поставте її в холодок!")
        elif check[2] == "bad-":
            bot.send_message(message.chat.id, f"Температура повітря: {data[2]} \nЦе погано для вашої рослинки! Покладіть її на сонце!")        
        
        remember_data(data)

def remember_data(data):

    with open("data.txt", "a") as file:

        for d in data:
            file.write(d + " ")

        file.write("\n")


def main():
    bot_send_data()

if __name__=="__main__":
    main()

bot.polling()
            
