# Autobell


## Описание проекта
Устройство для автоматической подачи звонка для школ, колледжей и университетов. 

### Железо
- Проект собран на базе микроконтроллера ESP8266 (NodeMCU)
- Модуль часов реального времени (RTC) DS3231
- OLED-экран 128x64 пикселей (SSD1306)
- Модуль твердотельного реле на базе G3MB-202P

### Функционал
- Работа системы как в локальной сети, так и в режиме “точки доступа” 
- 4 режима звонка на выбор (выходной, будний, сокращенный, или праздничный день)
- Возможность изменения режимов звонка для каждого дня недели
- Возможность изменения времени звонков для каждого режима (кроме выходного дня)
- Возможность настройки режима звонка для определенных дней (например, для праздников)
- Можно подать звонок при нажатии на кнопку прямо из интерфейса
- Система синхронизирует время с NTP-сервером
- Возможность настройки данных WiFi, NTP-сервера и данных для авторизации в интерфейсе
- Вывод основной информации как на сайте, так и на дисплее

## Папки
- `Autobell` - исходный код проекта
- `libraries` - библиотеки для работы (TODO)
- `schemes` - схемы подключения компонентов (TODO)

## Схемы
TODO: добавить схемы подключения компонентов

## Применение
### Первое подключение
После первого включения устройство создаст собственную точку доступа без пароля. Подключитесь к ней, тогда будете перенаправлены на интерфейс системы.
Если перенаправления не произошло, то перейдите по адресу `autobell.local` в браузере. 
В интерфейсе перейдите во вкладку "Конфигурация". На ней настройте WiFi и NTP-сервер (а именно часовой пояс), а также данные для авторизации, затем нажав на кнопку "Сохранить". После этого устройство перезагрузится и подключится к вашей сети.

### Автономное использование
В случае, если вы не хотите использовать устройство в вашей сети, то можно настроить его на работу в автономном режиме. Для этого просто оставьте данные подключения WiFi пустыми. Устройство будет работать в режиме точки доступа с именем `Autobell` и без пароля.
Пароль и логин задаются отдельно, для авторизации на интерфейс устройства.

### Настройка устройства
Основные настройки располагаются во вкладках "Настройки звонков" и "Время звонков". 
На данных страницах можно выставить режимы звонов для дней недели (например, для выбора рабочих дней и выходных).
Можно установить режим звонка на определенные даты (например, на Новый год или 8 марта). Нажимая на "+" или "-", можно добавить или удалить дату.
Соответственным образом настраивается и время звонков для каждого из режимов звонка. В каждом режиме можно задать неограниченное количество звонков.

TODO:

- [ ] Добавить скриншот интерфейса и фото конечного устройства
- [ ] Добавить схемы работы устройства и файлы печатной платы
