import asyncio
import json
import datetime
import logging
import sys

sys.path.append(
    '/Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/'
    'site-packages')
from sqlighter1 import SQLighter
from aiogram import Bot, Dispatcher, executor, types
from aiogram.utils.markdown import hbold, hunderline, hcode, hlink
from aiogram.dispatcher.filters import Text
from config import TOKEN, user_id
from main import check_news_update

# уровень логов
logging.basicConfig(level=logging.INFO)

# инит бота
bot = Bot(token=TOKEN, parse_mode=types.ParseMode.HTML)
dp = Dispatcher(bot)

# инит базу данных
db1 = SQLighter('db1.db')


# Команда подписки
@dp.message_handler(commands=['subscribe'])
async def subscribe(message: types.Message):
    if not db1.subscriber_exists(message.from_user.id):
        # если юзера нет в базе, добавляем его
        db1.add_subscriber(message.from_user.id)
    else:
        # если он уже есть, то просто обновляем ему статус подписки
        db1.update_subscription(message.from_user.id, True)

    await message.answer(
        "Вы успешно подписались на рассылку!\n"
        "Ждите, скоро выйдут новые обзоры и вы узнаете о них первыми =)")


# Команда отписки
@dp.message_handler(commands=['unsubscribe'])
async def unsubscribe(message: types.Message):
    if not db1.subscriber_exists(message.from_user.id):
        # если юзера нет в базе, добавляем его с неактивной подпиской и
        # запоминаем
        db1.add_subscriber(message.from_user.id, False)
        await message.answer("Вы сейчаси так были не подписаны.")
    else:
        # если он уже есть, то просто обновляем ему статус подписки
        db1.update_subscription(message.from_user.id, False)
        await message.answer("Вы успешно отписаны от рассылки.")


@dp.message_handler(commands="start")
async def start(message: types.Message):
    await message.reply("What's going on, bro? Gonna get it today, bro!")
    start_buttons = ["Все новости", "Последние 5 новостей", "Свежие новости"]
    keyboard = types.ReplyKeyboardMarkup(
        resize_keyboard=True)  # уменьшаем клавиатуру
    keyboard.add(*start_buttons)  # добавляем кнопки

    await message.answer("Лента новостей", reply_markup=keyboard)


# Теперь нужно привязать значения клавиатуры к функциям
# Заменяем название команд на имена в клавиатуре commands="all_news"
@dp.message_handler(Text(equals="Все новости"))
async def get_all_news(message: types.Message):
    with open("news_dict.json") as file:
        news_dict = json.load(file)

    for i, j in sorted(news_dict.items()):
        # название новости и ссылка повторяються, тут на свое усмотрение можно
        # убрать
        # f"{hunderline(j['news_title'])}\n" \
        news = f"{hbold(datetime.datetime.fromtimestamp(j['article_date_timestamp']))}\n" \
               f"{hcode(j['news_description'])}\n" \
               f"{hlink(j['news_title'], j['article_url'])}"  # вшиваем ссылку в имя
        # отформатируем вывод по красивше <b> -жирный, <u> -подчеркнуть
        await message.answer(news)


# last_5_news
@dp.message_handler(Text(equals="Последние 5 новостей"))
async def get_last_news(message: types.Message):
    with open("news_dict.json") as file:
        news_dict = json.load(file)

    for i, j in sorted(news_dict.items())[-5:]:  # собираем только 5 свежих
        news = f"{hbold(datetime.datetime.fromtimestamp(j['article_date_timestamp']))}\n" \
               f"{hcode(j['news_description'])}\n" \
               f"{hlink(j['news_title'], j['article_url'])}"  # вшиваем ссылку в имя

        await message.answer(news)


# fresh_news
@dp.message_handler(Text(equals="Свежие новости"))
async def get_fresh_news(message: types.Message):
    fresh_news = check_news_update()  # функция возвращает словарь со свежими новостями

    if len(fresh_news) >= 1:  # есть свежие новости и их выводим
        for i, j in sorted(fresh_news.items()):  # собираем только 5 свежих
            news = f"{hbold(datetime.datetime.fromtimestamp(j['article_date_timestamp']))}\n" \
                   f"{hcode(j['news_description'])}\n" \
                   f"{hlink(j['news_title'], j['article_url'])}"  # вшиваем ссылку в имя

        await message.answer(news)

    else:
        await message.answer("Нету свежих новостей :(")


# автоматизация бота, пока почему-то очень долго думает ~5мин
# async def scheduled(wait_for):
#     while True:
#         await asyncio.sleep(wait_for)
#         # проверяем наличие новых news
#         fresh_news = check_news_update()
#
#         if (len(fresh_news) >= 0):
#             for i, j in sorted(fresh_news.items()):  # собираем только 5 свежих
#                 news = f"{hbold(datetime.datetime.fromtimestamp(j['article_date_timestamp']))}\n" \
#                        f"{hcode(j['news_description'])}\n" \
#                        f"{hlink(j['news_title'], j['article_url'])}"  # вшиваем ссылку в имя
#                 subscriptions = db1.get_subscriptions()
#                 for user_ids in subscriptions:  # отправляем всем подпис из базы данных
#                     await bot.send_message(user_ids, news, disable_notification=True)
#
#         else:
#             subscriptions = db1.get_subscriptions()
#             for user_ids in subscriptions:  # отправляем всем подпис из базы данных
#                 await bot.send_message(user_id, "Свежих новостей пока нет",
#                                        disable_notification=True)
#
#         await asyncio.sleep(wait_for)  # время в секундах


# async def scheduled(wait_for):
#     while True:
#         await asyncio.sleep(wait_for)


if __name__ == "__main__":
    # создадим петлю для текущего цикла событий
    # loop = asyncio.get_event_loop()
    # loop.create_task(scheduled(10))
    executor.start_polling(dp, skip_updates=True)
