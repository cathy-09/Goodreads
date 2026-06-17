<img src="https://capsule-render.vercel.app/api?type=waving&height=250&color=gradient&customColorList=12,20,24,30&text=Goodreads&fontSize=54&desc=So%20many%20books,%20so%20little%20time...&descSize=18&descAlignY=65" width="100%" />

<div align="center">
<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.4); width: 100%; margin: 20px 0;">
<div style="margin-top: 15px; margin-bottom: 10px;">
  <h3>📚Курсов проект по Обектно-ориентирано програмиране (практикум)📚</h3>
</div>
<div style="margin-top: 5px; color: #555;">
  ФМИ, СУ „Св. Климент Охридски"
</div>
<div style="margin-top: 25px; font-weight: bold; color: #888;">
  2025/2026
</div>
</div>
<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.4); width: 100%; margin: 20px 0;">
<div align="center">
<blockquote>
“Читателят живее хиляди животи, преди да умре. Този, който не чете, живее само един.”
<div align="right"><cite style="color: #666; font-style: italic;">— Дж. Р. Р. Мартин</cite></div>
</blockquote>
</div>
</div>

## 📖 Съдържание

↳ [Описание на проекта](#-описание-на-проекта)  
↳ [Архитектура на проекта](#-архитектура-на-проекта)  
↳ [Йерархия на потребителите](#-йерархия-на-потребителите)  
↳ [Йерархия на изключенията](#-йерархия-на-изключенията)  
↳ [Модели](#️-модели)  
↳ [Запис на данните](#-запис-на-данните)  
↳ **[Команди и Логика](#-командите)** 
<br>
&nbsp;&nbsp;&nbsp;&nbsp;• [Общи команди за всички](#-общи-команди-всички-потребители)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Reader команди](#-reader-команди)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Author команди](#-author-команди-в-допълнение-към-reader)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Publisher команди](#-publisher-команди)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Специална логика](#-специални-логика)  
↳ [Примерни входни и изходни данни](#-примерни-входни-и-изходни-данни)
<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.3); width: 100%; margin: 20px 0;">

## 📖 Описание на проекта

Goodreads е конзолно приложение, моделиращо опростена и напълно функционална система за книги — перфектен старт за хората, обичащи да създават нещо, от което масата читатели имат нужда и за онези дръзки, запалени читатели, докоснали се до приложението Goodreads.

<div style="background-color: rgba(106, 13, 173, 0.04); padding: 15px; border-left: 3px solid #6a0dad; border-radius: 4px; margin: 18px 0;">

Системата разпознава **три типа потребители (читатели, автори и издателства)**, всеки със собствен набор от права, и поддържа пълен цикъл от взаимодействия:
* Регистрация на потребител и автентикация
* Последване на потребители
* Организация на лична библиотека в рафтове
* Размяна на съобщения
* Публикуване на книги
* Колаборация между автори и издателства
</div>

> 💾 Цялото състояние на системата (потребители, книги, рафтове, съобщения) се запазва в обикновен текстов файл при изход и се възстановява изцяло при последващо стартиране на програмата.

<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.3); width: 100%; margin: 25px 0;">


<img src="https://capsule-render.vercel.app/api?type=waving&height=140&section=footer&color=gradient&customColorList=12,20,24,30" width="100%" />
