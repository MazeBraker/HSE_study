import sys
sys.path.append('/Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/site-packages')
import json
import re
import requests
from bs4 import BeautifulSoup
from datetime import datetime
import time

# парсим вручную через код элемента
def get_first_news():
    HEADERS = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/91.0.4472.106 Mobile Safari/537.36"
    }
    URL = "https://kg-portal.ru/news/anime/"
    r = requests.get(url=URL, headers=HEADERS)

    soup = BeautifulSoup(r.text, "lxml")
    news_cards = soup.find_all(class_="ten_col2_content")
    news_dict = {}
    # news_cards = soup.find_all(class_="news_box anime_cat")
    # print(news_cards)
    # название, дата, краткое описание
    # 1 самая последняя новость, если несколько, то надо парсить через findAll
    for article in news_cards:
        news_title = article.find("a", class_="news_card_link").text.strip()

        news_description = article.find('div', class_="news_text",
                                        itemprop="articleBody").text.strip()

        article_url_link = article.find("a", class_="news_card_link").get("href")
        article_url = f'https://kg-portal.ru{article_url_link}'

        # time
        article_date_time = article.find("div", class_="date").get("content")
        date_from_iso = datetime.fromisoformat(article_date_time)
        date_time = datetime.strftime(date_from_iso, "%Y-%m-%d %H:%M:%S")
        article_date_timestamp = time.mktime(
            datetime.strptime(date_time, "%Y-%m-%d %H:%M:%S").timetuple())

        # print(f"{news_title} | {news_description} | {article_url} | {article_date_timestamp}")
        # id
        article_id_full = article_url.split("/"[-1])
        article_id_full = article_id_full[4]  # содержит id-название
        article_id = article_id_full[:6]
        article_id = article_id.replace('-', '')
        #print(article_id)

        news_dict[article_id] = {
            "article_date_timestamp": article_date_timestamp,
            "news_title": news_title,
            "article_url": article_url,
            "news_description": news_description
        }
    with open("news_dict.json", "w") as file:
        json.dump(news_dict, file, indent=4, ensure_ascii=False)


# сохраняем последний id, чтобы не повторяться
def check_news_update():
    with open("news_dict.json") as file:
        news_dict = json.load(file)

    HEADERS = {
        "user-agent": "Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) "
                      "Chrome/91.0.4472.106 Mobile Safari/537.36"
    }
    URL = "https://kg-portal.ru/news/anime/"
    r = requests.get(url=URL, headers=HEADERS)

    soup = BeautifulSoup(r.text, "lxml")
    news_cards = soup.find_all(class_="ten_col2_content")
    fresh_news = {}

    for article in news_cards:
        article_url_link = article.find("a", class_="news_card_link").get("href")
        article_url = f'https://kg-portal.ru{article_url_link}'
        # id
        article_id_full = article_url.split("/"[-1])
        article_id_full = article_id_full[4]  # содержит id-название
        article_id = article_id_full[:6]
        article_id = article_id.replace('-', '')

        if article_id in news_dict:
            continue  # скипаем
        else:  # собрать теже данные на новость
            news_title = article.find("a", class_="news_card_link").text.strip()
            news_description = article.find('div', class_="news_text",
                                            itemprop="articleBody").text.strip()
            # time
            article_date_time = article.find("div", class_="date").get("content")
            date_from_iso = datetime.fromisoformat(article_date_time)
            date_time = datetime.strftime(date_from_iso, "%Y-%m-%d %H:%M:%S")
            article_date_timestamp = time.mktime(
                datetime.strptime(date_time, "%Y-%m-%d %H:%M:%S").timetuple())
            # Добавляем новикну в словарь

            news_dict[article_id] = {
                "article_date_timestamp": article_date_timestamp,
                "news_title": news_title,
                "article_url": article_url,
                "news_description": news_description
            }

            # если запускаем не часто, то может успеть выйти >1 новости, но они новые и надо их
            # вместе показать, поэтому еще один словарь для только новых новостей

            fresh_news[article_id] = {
                "article_date_timestamp": article_date_timestamp,
                "news_title": news_title,
                "article_url": article_url,
                "news_description": news_description
            }
    # print(news_dict)
    # ее задача отработать 1 раз и собрать новые новости
    with open("news_dict.json", "w") as file:
        json.dump(news_dict, file, indent=4, ensure_ascii=False)
    return fresh_news


def main():
    # get_first_news()
    print(check_news_update())


if __name__ == "__main__":
    main()
