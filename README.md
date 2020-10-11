Репозиторий для сдачи лабораторных работ по курсу "Обработка изображений"


Лабораторная работа 1(Объяснение и сравнение).


2. Оттенки серого. 

с. 
  
  Была выполнена конвертация цветного изображения в монохромное при помощи average-метрики. С использованием метрики среднеквадратической ошибки immse получаем, что отклонение нашего варианта реализации от реализации OpenCV равно 7678.7 единиц. Это означает, что разработчики OpenCV использовали другой способ такой обработки изображения, возможно, более сложный. Визуально изображения слабо различимы по цветовой гамме за исключением более темного тона у получившегося у нас варианта.


3. Конвертация м/у цветовыми моделями.

е.

  Мы реализовали прямую и обратную конвертацию исходного BGR изображения в цветовую модель YUV, а также фильтр увеличения яркости для изображения в различных цветовых схемах. В результате получаем по метрике immse разницу в 7.55675 единиц между следующими изображениями: 
* BGR изображение, на которое наложили фильтр увеличения яркости на некоторую величину;
*	BGR изображение, которое мы перевели по нашей схеме в модель YUV, использовали фильтр увеличения яркости уже для этой схемы, а затем перевели обратно в BGR схему.
  
  Тогда как при использовании переходов, реализованных в OpenCV, это значение составило 0.163105 единиц. Можно предположить, что разработчики этой библиотеки использовали алгоритмы оптимизации, значительно сокращающие время работы таких переходов. 
  
  Далее мы измерили время работы программы, состоящей из 1000 итераций увеличений яркости для некого BGR изображения и для YUV изображения. Получили время в 8.1292 секунды и 7.6022 секунды соответственно. Это можно объяснить тем, что в первом варианте нужно добавить константу по всем трем цветовым каналам, тогда как для второго – только к первому каналу.
  
  Работу выполнили студенты группы 381806-1: Гогов Владислав, Шагов Максим и Тактаев Артем.
