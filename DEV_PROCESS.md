# Текущее состояние проекта
## **GUI**
Сделана очень упрощённая версия. Из трёх окон проработано только первое.

## **Карта**
Карта обёрнута в отдельный виджет и внедрена в gui (в оба окна, где должна быть). Добавлен searchbar, который должен "переносить" карту в точку с введёнными lat и lon, но пока он работает не правильно (что-то с системами координат). 

## **Связь с Pixhawk**
Осуществляется приём сообщений трёх типов - Attitude, Heartbeat и GlobalPositionInt (но без gps-антенны в этом сообщении приходят нули и шум). Установка частоты отправки pix-ом сообщений производилась с помощью missionplaner-а, делать это из кода пока не получается. Была попытка отправки сообщения, которое настраивает частоту отправки Heartbeat, но связь установить не удалось (в чём причина пока не понятно: то ли пакет на борт не приходит, то ли приходит, но не правильно обрабатывается).

# Текущие неразрешённые вопросы
пока нет

# Разрешённые вопросы
1) Как организовать cmakelist-ы при модульной разработке?
   -> будем работать с subdirectory и для каждой части проекта будет свой cmakelist
2) Как решить вопрос подключения подключения разных Pixhawk к разным компам? 
   -> делаем проект под ubuntu (под винду qgis собрать сложно)
3) Нужно ли писать обёртку над сгенерированным QtDesigner-ом gui? Если да, то какую? Можно ли в QtDesigner-е создавать объекты не по отдельности, а списком?
   -> будет что-то вроде менеджера 