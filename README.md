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

↳ [Описание на проекта](#-описание-на-проекта-)  
↳ [Архитектура на проекта](#-архитектура-на-проекта-)  
↳ [Йерархия на потребителите](#-йерархия-на-потребителите-)  
↳ [Йерархия на изключенията](#-йерархия-на-изключенията-)  
↳ [Модели](#-модели-)  
↳ [Запис на данните](#-запис-на-данните-)  
↳ **[Команди и Логика](#-команди-и-логика-)** <br>
&nbsp;&nbsp;&nbsp;&nbsp;• [Общи команди за всички](#общи-команди-за-всички)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Reader команди](#reader-команди)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Author команди](#author-команди)  
&nbsp;&nbsp;&nbsp;&nbsp;• [Publisher команди](#publisher-команди)  
↳ **[Примерни входни и изходни данни](#примерни-входни-и-изходни-данни-)**
<br>
↳ [Автор](#-автор-)

<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.3); width: 100%; margin: 20px 0;">

## 📖 Описание на проекта 📖
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

## 🏗 Архитектура на проекта 🏗
```
Goodreads/
├── 🎬 Goodreads.cpp            (main)
├── 🧠 GoodreadsApp.{h,cpp}     командите и цялата бизнес логика
├── 💾 FileManager.{h,cpp}      четене/запис на данните
│
├── 👤 User.{h,cpp}             базов клас за всеки акаунт
├── 📗 Reader.{h,cpp}           читател, съдържащ библиотека, рафтове, любими, inbox
├── ✍️  Author.{h,cpp}          автор (наследяващ Reader) — публикации, издателства
├── 🏢 Publisher.{h,cpp}        издателство — автори, публикувани книги
│
├── 📕 Book.{h,cpp}             книга — рейтинг, жанрове
├── 🔖 BookEntry.{h,cpp}        книга, която е в личния профил на човека
├── 🗂️  Shelf.{h,cpp}           рафт с книги
├── ✉️  Message.{h,cpp}         съобщение в inbox с тип и статус „прочетено"
├── 📅 Date.{h,cpp}             дата (ден/месец/година)
├── 🔍 Search.{h,cpp}           fuzzy case-insensitive  search
│
└── ⚠️  Exception.{h,cpp}       йерархия от изключения
```

Някои класове:

- **`Book`** — модел на книга (заглавие, автор, издателство, резюме, жанрове, среден рейтинг, брой оценки, дата на издаване, брой страници). Рейтингът се преизчислява (`addRating`/`updateRating`).
- **`BookEntry`** — представя книга в личната библиотека на читателя: статус (`plan-to-read` / `reading` / `paused` / `dropped`) и собствена оценка.
- **`Shelf`** —  рафт с дата на създаване и списък от заглавия.
- **`Message`** — съобщение в `inbox`, с подател, съдържание, тип (`Regular`, `FollowNotice`, `BookNotice`, `JobOffer`, `LikedNotice`, `FriendNotice`) и флаг „прочетено“.
- **`Date`** — наредена тройка ден/месец/година във формат `DD.MM.YYYY`.
- **`Search`** — статичен помощен клас за case-insensitive търсене.
- **`FileManager`** — четене/запис на цялото състояние (потребители, книги) във текстов файл.
- **`GoodreadsApp`** — команди: чете ред по ред от конзолата, препраща към съответната `cmd` функция и поддържа логнатия потребител в този момент.

Логиката е разделена в малки `validate`/`resolve`/`format` помощни функции, които се грижат за проверката на входа, намирането на обекти и форматирането на изхода.

## 👥 Йерархия на потребителите 👥

```
                ┌──────────┐
                │   User   │   username, password, registrationDate, followers
                └────┬─────┘
           ┌─────────┴─────────┐
           │                   │
     ┌─────▼──────┐     ┌──────▼──────┐
     │   Reader   │     │  Publisher  │   authors[], publishedBooks[]
     └─────┬──────┘     └─────────────┘
           │             books[], shelves[], favorites[],
           │             birthday(опционален), inbox[]
     ┌─────▼──────┐
     │   Author   │   publishedBooks[], publishers[]
     └────────────┘   (всичко от Reader класа)
```

- **`User`** — базов клас за всички потребители: потребителско име(6–24 символа), парола (12–36 символа, поне 1 малка буква + 1 главна буква + 1 не-буквен символ), дата на регистрация и последователи (`followers`). Деклариран е и чисто виртуалния метод `type()`, който всеки наследник реализира — оттук насетне приложението работи полиморфно с `User*`.
- **`Reader : User`** — добавя лична библиотека от книгите в профила (`BookEntry`), рафтовете (`Shelf`), любимите книги, опционален рожден ден и входящата кутия (`inbox`). Само Reader и неговите наследници (Author) имат `inbox` — издателствата не получават съобщения в системата, така че `Publisher` няма това поле (или няма достъп до това поле).
- **`Author : Reader`** — наследява всичко от читателя (авторите могат да четат, да следват, да имат рафтове и inbox) и добавя списък с публикувани книги и издателства, с които работи.
- **`Publisher : User`** — управлява списък с автори и публикувани книги. Командите `follow`, `show-inbox`, `read-msg`, `delete-msg` са недостъпни за издателства.

## ⚠️ Йерархия на изключенията ⚠️

```
std::runtime_error
        │
GoodreadsException                 базов клас за изключенията
        │
   ┌────┴──────────────┐
   │                   │
ValidationException   FileException     грешки при четене/запис във файла
   │
   ├── DateException       невалиден формат или невалидна календарна дата
   └── RatingException     рейтинг извън диапазона [1, 5]
```

Всяко изключение се хваща локално в съответната `cmd` функция и се връща съобщение към потребителя.

## 🎨 Модели 🎨

| Клас | Основни данни |
|---|---|
| `User` | `username`, `password`, `registrationDate`, `followers` |
| `Reader` | + `books` (`BookEntry`), `shelves`, `favorites`, `birthday` (опционално), `inbox` |
| `Author` | + `publishedBooks`, `publishers` |
| `Publisher` | `authors`, `publishedBooks` |
| `Book` | `title`, `author`, `publisher`, `summary`, `genres`, `averageRating`, `ratingCount`, `releaseDate`, `pageCount` |
| `Shelf` | `name`, `books`, `createdAt` (брой книги се връща чрез `size()`) |
| `Message` | `from`, `content`, `type`, `isRead` |
| `Date` | `day`, `month`, `year` |

> [!CAUTION]
> Заглавието на книгата служи като уникален идентификатор.

> [!NOTE]
> Рафтовете са уникални в рамките на един читателски профил.

## 💾 Запис на данните 💾

Цялото състояние се пази в обикновен текстов файл (`data.txt`) — по един ред за всяко поле, списъци отделени с разделител `|`.
Структура:

```
<брой потребители>
  за всеки потребител:
    тип (Reader/Author/Publisher)
    username
    password
    registrationDate
    followers (| -разделени)
    [ако Reader/Author: книги, рафтове, любими, рожден ден, inbox (брой и всяко съобщение: from, content, type, прочетено)]
    [ако Author: publishedBooks, publishers]
    [ако Publisher: authors, publishedBooks]
<брой книги>
  за всяка книга: title, author, publisher, summary, genres, averageRating, ratingCount, releaseDate, pageCount
```

Файлът се зарежда изцяло в паметта при старт (`FileManager::load`) и се записва изцяло при `exit` (`FileManager::save`).

## 🧠 Команди и Логика 🧠

> [!CAUTION]
> Всяка дата се подава във формат **`ДД.ММ.ГГГГ`** (точно 10 символа, с точки като разделители).

### Общи команди за всички

| Команда | Описание |
|---|---|
| `help` | Списък с позволените команди според типа на текущия потребител |
| `register <username> <password> <reader\|author\|publisher>` | Регистрация на нов потребител |
| `login <username> <password>` | Вход в системата |
| `logout` | Изход от текущия профил |
| `exit` | Запис на всички данни и спиране на програмата |

### Reader команди

| Команда | Описание |
|---|---|
| `search <name>` | Case-insensitive търсене на потребители и книги; точно съвпадение или съвпадение с до 2 грешки |
| `follow <username>` | Последване на потребител и изпращане на съобщение до него |
| `add-book <bookTitle> <status> [rating]` | Добавяне на книга в профила (`plan-to-read`, `reading`, `paused`, `dropped`) |
| `create-shelf <name>` / `delete-shelf <name>` | Управление на рафтове |
| `add-to-shelf <bookTitle> <shelfName>` / `remove-from-shelf <bookTitle> <shelfName>` | Поставяне/премахване на книга от рафт |
| `delete-book <bookTitle>` | Изтриване на книга от профила и от всички рафтове |
| `show-shelf [reader] <name>` | Показва съдържанието на рафт |
| `show-inbox [job-offers\|follow-notices]` | Показва входящата кутия, с опционален филтър |
| `read-msg <index>` / `delete-msg <index>` | Маркиране като прочетено / изтриване (само на прочетено съобщение) |
| `friends [reader]` | Списък с приятели (взаимни последователи) |
| `add-birthday [date]` | Задава рожден ден; без аргумент — премахва го |
| `profile [reader]` | Информация за профила: дата на регистрация, рожден ден, рафтове, любими книги, книги |
| `add-favorite <bookTitle>` / `remove-favorite <bookTitle>` | Управление на любими книги |

### Author команди

| Команда | Описание |
|---|---|
| `show-inbox [job-offers]` | Наследена команда, с допълнителен филтър за job offers |
| `accept-offer <index>` | Приема job offer от издателство |
| `leave <publisher>` | Прекратява съвместната работа с издателство |
| `followers` | Показва последователите на автора |

### Publisher команди

| Команда | Описание |
|---|---|
| `publish <title> <author> <date> <pages> <genre...>` | Публикува нова книга и известява последователите на автора и/или издателството |
| `add-synopsis <bookTitle> <text>` | Добавя резюме към публикувана от издателството книга |
| `offer <author>` | Изпраща job offer на автор |

При `publish` известието варира според това кого следва получателят:
```
[index] New book published by author <AuthorName>: <BookName>
[index] New book published by publisher <PublisherName>: <BookName>
[index] New book published by author <AuthorName> and publisher <PublisherName>: <BookName>
```

## Примерни входни и изходни данни

#### 🔹 `register`

```text
register annasmith Passw0rd!2025 reader
Registered successfully as reader: annasmith

register annasmith Passw0rd!2025 reader
Username already taken.

register ab Passw0rd!2025 reader
Registration failed: Username must be between 6 and 24 characters long.

register okusername short reader
Registration failed: Password must be between 12 and 36 characters.

register okusername alllowercase123 reader
Registration failed: Password must contain at least one uppercase letter.

register okusername ALLUPPERCASE123 reader
Registration failed: Password must contain at least one lowercase letter.

register okusername NoSpecialChar reader
Registration failed: Password must contain at least one non-letter character.

register baduser GoodPass#2025 something
Unknown type. Use: reader, author, publisher
```

#### 🔹 `login` / `logout`

```text
login annasmith WrongPassword#1
Invalid username or password.

login annasmith Passw0rd!2025
Welcome, annasmith! (Reader)

login annasmith Passw0rd!2025
Already logged in as annasmith. Logout first.

logout
Goodbye, annasmith!
```

#### 🔹 `help` (изходът зависи от ролята)

```text
help
Available Commands
help
register <username> <password> <reader|author|publisher>
login <username> <password>
logout
exit
```

```text
[след логин като Reader]
help
...
Reader
search <name>
follow <username>
add-book <bookTitle> <status> [rating]
status: plan-to-read | reading | paused | dropped
create-shelf <name>
delete-shelf <name>
add-to-shelf <bookTitle> <shelfName>
remove-from-shelf <bookTitle> <shelfName>
delete-book <bookTitle>
show-shelf [reader] <shelfName>
show-inbox [job-offers|follow-notices]
read-msg <index>
delete-msg <index>
friends [reader]
add-birthday [date]
profile [reader]
add-favorite <bookTitle>
remove-favorite <bookTitle>
```

```text
[след логин като Publisher]
help
...
Publisher
publish <bookTitle> <authorName> <releaseDate> <pageCount> <genres...>
add-synopsis <bookTitle> <synopsis>
offer <authorName>
search <name>
```

#### 🔹 `exit`

```text
exit
Saving data... Goodbye!
```

#### 🔍 `search <name>` — fuzzy, case-insensitive

Търси едновременно сред **потребителските имена** и **заглавията на книги**. Толерира до **2 грешки**

```text
search fire
Users:
firepress (Publisher)
Books:
FIRE (5.00)

search fyre
Users:
(none)
Books:
FIRE (5.00)

search xyzxyzxyz
Users:
(none)
Books:
(none)
```

#### ➕ `follow <username>`

Последва потребител и веднага му изпраща съобщение от тип "follow notice".

```text
follow fyrelord
You are now following fyrelord.

follow fyrelord
You already follow fyrelord.

follow annasmith
You cannot follow yourself.

follow ghostuser
User not found: ghostuser
```

#### 📕 `add-book <bookName> <status> [rating]`

`status` ∈ `{plan-to-read, reading, paused, dropped}`. 

`rating` е незадължителен и трябва да е цяло число от 1 до 5 — ако се подаде, директно влияе на средния рейтинг на книгата.

```text
add-book FIRE reading 5
FIRE added to ur profile.

add-book FIRE reading 5
You already have FIRE in your profile.

add-book Nonexistent reading
Book not found: Nonexistent

add-book FIRE badstatus
Invalid status. Helps for status: plan-to-read, reading, paused, dropped
```

#### 🗂️ `create-shelf` / `delete-shelf <name>`

```text
create-shelf want-to-reread
Shelf want-to-reread created.

create-shelf want-to-reread
A shelf named want-to-reread already exists.

delete-shelf want-to-reread
Shelf want-to-reread deleted.

delete-shelf want-to-reread
Shelf want-to-reread does not exist.
```

#### 📥 `add-to-shelf` / `remove-from-shelf <bookName> <shelfName>`

> [!CAUTION]
>  Книгата трябва вече да е добавена в профила (чрез `add-book`), преди да я сложим "на" рафта.

```text
add-to-shelf FIRE want-to-reread
FIRE added to shelf want-to-reread.

add-to-shelf FIRE want-to-reread
FIRE is already on shelf want-to-reread.

remove-from-shelf FIRE want-to-reread
FIRE removed from shelf want-to-reread.

remove-from-shelf FIRE want-to-reread
FIRE is not on shelf want-to-reread.
```

#### 🗑️ `delete-book <bookName>`

Маха книгата от профила **и** от всички рафтове, в които участва, и коректно изважда личната оценка от средния рейтинг на книгата.

```text
delete-book FIRE
FIRE removed from your profile.

delete-book FIRE
You don't have FIRE in ur profile.
```

#### 👀 `show-shelf [reader] <shelfName>`

Без аргумент за `reader` — гледаш собствените си рафтове. Със `reader` — гледаш чужди рафтове, **но само ако сте приятели**.

```text
show-shelf want-to-reread
Shelf: want-to-reread (1 books)
Created: 20.06.2026
 - FIRE (5.00)

show-shelf fyrelord want-to-reread
Access denied. You must be friends with fyrelord to view their shelves.

[след взаимно follow между двамата]
show-shelf fyrelord want-to-reread
Shelf: want-to-reread (0 books)
Created: 20.06.2026
(empty)
```

#### 📬 `show-inbox [follow-notices]`

```text
show-inbox
[1] * From annasmith: annasmith started following you.

show-inbox follow-notices
[1] * From annasmith [Follow]: annasmith started following you.
```

> [!CAUTION]
> `*` пред съобщението означава, че е непрочетено.

#### ✅🗑️ `read-msg <index>` / `delete-msg <index>`

Съобщение може да бъде изтрито **само след** като е било прочетено.

```text
read-msg 1
Message [1] marked as read.

delete-msg 1
Message deleted.

delete-msg 5
Invalid index.
```

```text
delete-msg 2
Cannot delete an unread message. Mark it as read first.
```

#### 🤝 `friends [reader]`

Приятел = потребител, когото следваш **и** който те следва обратно.

```text
friends
Friends of annasmith:
  fyrelord (Reader)

friends ghostuser
User not found: ghostuser
```

#### 🎂 `add-birthday [date]`

```text
add-birthday 14.03.1998
Birthday set to 14.03.1998.

add-birthday 31.02.2025
Invalid date: Invalid date for that month

//търка рожден ден
add-birthday
Birthday removed from your profile.
```

#### 🪪 `profile [reader]`

```text
profile
 annasmith (Reader)
Registered: 26.05.2026
Birthday: 14.03.1998
Followers: 1

Books (1):
 FIRE
Status: Reading
Your rating: 5/5
Author: tolkien
Publisher: firepress
Pages: 320
Avg rating: 5.00/5
Genres: Fantasy, Adventure

Shelves (1):
  want-to-reread (1 books)

Favorite books (1):
  FIRE
```

#### ⭐ `add-favorite` / `remove-favorite <bookName>`

```text
add-favorite FIRE
FIRE added to your favorites.

add-favorite FIRE
FIRE is already in your favorites.

remove-favorite FIRE
FIRE removed from your favorites.

remove-favorite FIRE
FIRE is not in your favorites.

add-favorite Nonexistent
You don't have Nonexistent in ur profile. Add it first.
```

#### 📬 `show-inbox job-offers`

> [!NOTE]
> Същата команда като при читателите, но с филтър само за job offer-и.

```text
show-inbox job-offers
[2]   From firepress [Job Offer]: Publisher firepress is offering you a collaboration.
```

#### 🤝 `accept-offer <index>`

```text
accept-offer 2
You accepted the offer from firepress. You are now working together.

accept-offer 1
Message [1] is not a job offer.

accept-offer 99
Invalid index.
```

#### 👋 `leave <publisher>`

```text
leave firepress
You left publisher firepress.

leave firepress
You are not working with publisher firepress.
```

#### 👥 `followers`

```text
followers
Followers of tolkien (1):
  annasmith (Reader)
```

#### 📖 `publish <bookTitle> <authorName> <releaseDate> <pageCount> <genre1> [genre2...]`

> [!CAUTION]
> Всеки токен след `<pageCount>` се счита за отделен жанр — може да подадете произволен брой. При успех всеки потребител, който следва **автора и/или издателството**, 
> получава автоматично известие.

```text
publish FIRE tolkien 12.05.2024 320 Fantasy Adventure
Book FIRE published successfully.

publish FIRE tolkien 12.05.2024 320 Fantasy
A book with title FIRE already exists.

publish FIRE tolkien notadate 320 Fantasy
Invalid date: Date format: DD.MM.YYYY

publish FIRE tolkien 12.05.2024 -5 Fantasy
Page count must be a positive number.
```

Известие до читател, който следва **само автора**:

```text
[1] * From system: New book published by author tolkien: FIRE
```

Известие до читател, който следва **само издателството**:

```text
[1] * From system: New book published by publisher firepress: FIRE
```

Известие до читател, който следва **и двамата**:

```text
[1] * From system: New book published by author tolkien and publisher firepress: FIRE
```

#### 📝 `add-synopsis <bookTitle> <synopsis>`

Синопсисът може да съдържа произволен брой думи — всичко след заглавието на книгата се събира в една анотация. Може да редактираме синопсис само на книга, която сме  публикували.

```text
add-synopsis FIRE A tale of dragons and fire.
Synopsis added to FIRE.

add-synopsis Ghost Nice book
Book not found: Ghost
```

#### 💼 `offer <author>`

```text
offer tolkien
Job offer sent to tolkien.

offer annasmith
annasmith is not an author.

offer ghostauthor
User not found: ghostauthor
```

## Автор 

<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.4); width: 100%; margin: 20px 0;">

```yaml
Име: "Katerina Dimitrova"
Факултет: Софийски университет „Св. Климент Охридски“, ФМИ  
Специалност: Софтуерно инженерство  
Курс: I
```
<br>

```yaml
Контакти: Това са социалните ми мрежи
```

<div align="center">
<a href="https://github.com/cathy-09">
  <img src="https://skillicons.dev/icons?i=github" height="48" />
</a>
<a href="https://instagram.com/dimitrova09">
  <img src="https://skillicons.dev/icons?i=instagram" height="48" />
</a>
<a href="mailto:dimitrovakaterina780@gmail.com">
  <img src="https://img.icons8.com/fluency/96/gmail-new.png" height="48"/>
</a>
<a href="https://discord.com/users/cathy09">
  <img src="https://skillicons.dev/icons?i=discord" height="48" />
</a>
<a href="https://www.facebook.com/Katerina Dimitrova">
  <img src="https://cdn.simpleicons.org/facebook/1877F2" height="48" />
</a>
<a href="https://www.threads.net/@dimitrova09">
  <img src="https://cdn.simpleicons.org/threads/FFFFFF" height="48" />
</a>
</div>

<hr style="height: 0.5px; border: none; background-color: rgba(106, 13, 173, 0.4); width: 100%; margin: 20px 0;">

<img src="https://capsule-render.vercel.app/api?type=waving&height=140&section=footer&color=gradient&customColorList=12,20,24,30" width="100%" />
