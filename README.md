# Smart-Green-House
Привіт! Цей проект створений для полекшення роботи фермерам, для автоматизації системи вирощування сільськогосподарських культур. 

Використовуюючи мікроконтролер esp8266 та датчик для вимірювання вологості грунту hygrometer, датчик для вимірювання вологсті та температури повітря та деякі програмні рішення ми можемо спостерігати за теплицями, за рослинами на відстані, що значно спрощує процес.

Система працює на базі плати NodeMCU на мікроконтролері esp8266, до якого підєднано данчик вологості грунту гігрометра та датчик вимірювання вологсті та температури повітря DHT11. Контролер під'єднується до wifi мережі та хостить сервер на якому розміщено сайт для перегляду інформації з наявним API. Сайт написаний на html та css. Ви можете переглядати данні як напряму із сайту, так і з інших джерел. За допомогою API будь яка програма може дістати данні з датчиків. 

Телеграм бот відсилаючи get-запит обробляє отриману інформацію, зберігає її у файл для подальшого аналізу та надсилає користувачу на команду /data через модуль PyTelegramAPI для python.
При відкритті програми, python через бібліотеку eel через chrom запускає додаток, інтерфейс якого створений за допотогою html та css а мостом для GUI та логікою програми написаної на python є java script. На першій вкладці ви можете ознайомитись із показниками на данний момент, які беруться також через API напряму із сайту через відсилання запиту, у вкладці інформація дізнатися, як доглядати за рослиною (у мому випадку Фікус Бенжаміна), а у вкладці із графіками при виборі певної категорії програма створює графік через matplotlib, данні для якого беруться із файлу в який ці данні записав телеграм бот та подивитись на показники з датчиків біля вашої рослини за весь період часу, тим самим зробити висновки, провести певний аналіз. 
