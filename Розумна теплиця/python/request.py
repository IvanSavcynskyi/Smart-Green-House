import requests
import lxml
from bs4 import BeautifulSoup
import telebot

url = "http://192.168.0.111/"

req = requests.get(url)

src = req.text

soup = BeautifulSoup(src, "lxml")

text = soup.find(_class="wetdata")

print(text.text)


