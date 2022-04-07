import requests
import logging
import telebot
import time
import eventlet
import config
from time import sleep

# Каждый раз получаем по 10 последних записей со стены
vk_url = "https://api.vk.com/method/wall.get?https://vk.com/animevostorg=team&count=5"
wall_url = "https://vk.com/wall-1111111"

TOKEN = ""
channel = ""

bot = telebot.TeleBot(TOKEN)


def get_news():
    try:
        status = requests.get(vk_url)
        return status.json()
    except eventlet.timeout.Timeout:
        logging.warning(
            'Timeout while cancelling...')
        return None
    finally:
        eventlet.Timeout(10).cancel()
