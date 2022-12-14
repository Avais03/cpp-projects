# class Biginteger + Rational

<h2>Biginteger</h2>

<h3>Класс Biginteger для работы с целыми числами произвольной длины (сколько на куче влезет😉).</h3>
<h3>Поддерживаемые операции (положим `n` - это длина числа):</h3>


+ Сложение, вычитание. `O(n)`
+ Умножение. `O(n^2)`
+ Деление, остаток по модулю, `O(n^2 log_n)`; 
+ Составное присваивание с этими операциями.
+ 
+ Унарный минус, префиксный и постфиксный инкремент и декремент. Префиксный инкремент и декремент работают за `O(1)` в среднем.
+ Операторы сравнения `== != < > <= >=`
+ Вывод в поток и ввод из потока
+ Метод `toString()`, возвращающий строковое представление числа
+ Конструирование из `int` (в том числе неявное преобразование, когда это надо)
+ Неявное преобразование в `bool`, когда это надо (должно работать в условных выражениях)

<h2>Rational</h2>

<h3>Класс Rational для работы с рациональными числами сколь угодно высокой точности.</h3>



<h4>Rational представляются в виде несократимых обыкновенных дробей, где числитель и знаменатель – сколь угодно длинные целые числа. Поддерживаются операции:</h4>



+ Конструктор из `BigInteger`, из `int`
+ Сложение, вычитание, умножение, деление, составное присваивание с этими операциями (асимптотика аналогичная)
+ Унарный минус
+ Операторы сравнения `== != < > <= >=`
+ Метод `toString()`, возвращающий строковое представление числа (вида [минус]числитель/знаменатель), где числитель и знаменатель - взаимно простые числа; если число на самом деле целое, то знаменатель выводить не надо
+ Метод `asDecimal(sizet precision=0)`, возвращающий строковое представление числа в виде десятичной дроби с precision знаками после запятой
+ Оператор приведения к `double`

<h2>author: Vladimir Slastin🤙</h2>

+ [VK](https://vk.com/vovchik1902)
+ [Telegramm](https://www.t.me/SlastinVA)
+ [Instagram](https://www.instagram.com/dreaminngman) 
<li itemprop="email" aria-label="Email: Avais03@mail.ru" class="vcard-detail pt-1 css-truncate css-truncate-target "><svg class="octicon octicon-mail" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.75 2A1.75 1.75 0 000 3.75v.736a.75.75 0 000 .027v7.737C0 13.216.784 14 1.75 14h12.5A1.75 1.75 0 0016 12.25v-8.5A1.75 1.75 0 0014.25 2H1.75zM14.5 4.07v-.32a.25.25 0 00-.25-.25H1.75a.25.25 0 00-.25.25v.32L8 7.88l6.5-3.81zm-13 1.74v6.441c0 .138.112.25.25.25h12.5a.25.25 0 00.25-.25V5.809L8.38 9.397a.75.75 0 01-.76 0L1.5 5.809z"></path></svg>
          <a class="u-email Link--primary " href="mailto:Avais03@mail.ru">Avais03@mail.ru</a>
</li>
