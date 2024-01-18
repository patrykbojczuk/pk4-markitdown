### To jest kopia projektu. Oryginalne repozytorium było hostowane przez uczelnię i nie jest już dostępne.

---

# Mark It Down

### markdown editor

|                |                |
| -------------- | -------------- |
| autor          | Patryk Bojczuk |
| rok akademicki | 2021/2022      |
| kierunek       | informatyka    |
| rodzaj studiów | SSI            |
| semestr        | 4              |
| grupa          | 1              |
| sekcja         | 1              |
| termin oddania | 22.06.2022 r.  |

## Opis tematu

Aplikacja z interfejsem graficznym umożliwiająca tworzenie oraz edytowanie plików w formacie markdown.

Pozwala na tworzenie dokumentów z wykorzystaniem znaczników markdown z równoczesnym podglądem sformatowanego tekstu w podzielonym oknie aplikacji. Aplikacja posiada pasek narzędzi ułatwiających formatowanie oraz wstawianie znaczników do tekstu.

Do parsowania znaczników markdown wykorzystany jest parser oparty na maszynie stanów oraz wyrażeniach regularnych.

Parser jest niezależny od programu głównego, zaimplementowany w formie biblioteki, co umożliwia wykorzystanie go w innych projektach.

Poza funkcjonalnością zapisu pliku w formacie markdown, z wykorzystaniem konwerterów możliwe jest również wyeksportowanie dokumentu w formacie HTML, oraz PDF, a udostępniony interfejs pozwala na dodanie nowych sposobów konwersji.

## Interfejs użytkownika

Po naciśnięciu przycisku `New file` lub `Open` wyświetlony zostanie monit odpowiednio o zapis nowego pliku lub wybranie pliku do otwarcia. Możliwe jest również otworzenie jednego z ostatnio otwieranych plików.

Następnie użytkownik przenoszony jest do widoku edytora, w którym może modyfikować treść dokumentu.

## Specyfikacja wewnętrzna

Aplikacja stworzona jest w środowisku Qt i składa się z klas bezpośrednio powiązanych z edytorem: `ConfigManager`, `ConfigFileManager`, `FileManager`, `MarkdownFileManager`, `TabManager`, `Tab` oraz klasy `HtmlConverter` implementującej interfejs `IConverter`, a także pakietu `MarkdownParser` zawierającego klasę `MarkdownTokenizer`, `MarkdownInlineElementsParser`, `MarkdownParser` i klasy tokenów parsera oraz pakietu `MarkdownDocument` zawierającego klasę `MarkdownDocument` i składające się na nią klasy elementów markdown. Frontend wykonano w wykorzystywanym przez środowisko Qt języku QML. Komunikacja między elementami frontendu oraz backendu wykorzystuje klasy singleton oraz mechanizm sygnałów i slotów.

Klasa `MarkdownTokenizer` rozbija asynchronicznie, z wykorzystaniem wyrażeń regularnych, ciąg wejściowy na tokeny.

Klasa `MarkdownInlineElementsParser` przetwarza elementy zagnieżdżalne przez stworzenie wektora podstawień, zastąpienie elementu zagnieżdżalnego w tekście źródłowym sekwencją `\0x07{ix}\0x07`, gdzie `{ix}` oznacza indeks elementu w wektorze podstawień, a następnie zamianie wszystkich podstawień na odpowiadające im elementy w strukturze dokumentu markdown (`MarkdownDocument`).

Klasa `MarkdownParser` implementuje maszynę stanów, która na podstawie tokenów wygenerowanych przez obiekt klasy `MarkdownTokenizer`, wykorzystując również `MarkdownInlineElementsParser`, generuje dokument `MarkdownDocument` składający się z elementów markdown. Ze względu na możliwość zagnieżdżania list nieuporządkowanych, aktualny stan maszyny (`stateStack`), poziom zagnieżdżenia (`indentLevel`) oraz aktualnie przetwarzany element (`currentElementStack`) przechowywany jest na stosie.

Klasa `FileManager` w celu zapisu/odczytu plików wykorzystuje mechanizm wielowątkowości, co pozwala na wyeliminowanie blokowania głównego wątku, a w efekcie braku responsywności aplikacji, a także bibliotekę `filesystem`.

Klasa `ConfigManager` implementuje wzorzec projektowy singleton i przechowuje zdefiniowane przez użytkownika preferencje dotyczące autozapisu oraz fontu. W przypadku zmiany wartości któregoś parametru, zgłaszany jest odpowiadający mu sygnał, na który może zareagować interfejs użytkownika.
W celu sprawdzenia, czy plik konfiguracyjny istnieje, korzysta ona z klasy `ConfigFileManager`, która wykorzystuje metody klasy `FileManager`. W przypadku, gdy plik nie istnieje, jest on tworzony i wypełniany domyślnymi wartościami.

Klasa `Tab` przechowuje dane karty edytora takie jak jej id, nazwę pliku na jakim operuje, aktualną zawartość markdown oraz zawartość skonwertowaną do HTML. Pozwala na ustawienie zawartości, zapisanie pliku oraz wyeksportowanie go do pliku w formacie HTML oraz PDF. W przypadku zmiany właściwości karty, rozgłaszany jest odpowiedni sygnał.

W celu wykonywania operacji na plikach, korzysta ona z klasy `MarkdownFileManager` - singletonu implementującego mechanizm strategii w celu konwersji dokumentu markdown (`MarkdownDocument`) do odpowiedniego formatu.

Klasa `TabManager` - singleton, zarządza kartami edytora (`Tab`), tj. tworzy, zamyka, pozwala na pobranie karty na podstawie jej id oraz pozwala na zapisanie wszystkich kart. Przechowuje również hash MD4 ostatnio zapisanych danych, dzięki czemu pozwala uniknąć niepotrzebnych operacji zapisu tych samych danych do pliku. Wysyła sygnał po otworzeniu bądź zamknięciu karty oraz w przypadku gdy powinna zostać przełączona karta (np. po otwarciu nowej karty).

Interfejs `IConverter` pozwala w prosty sposób na zaimplementowanie konwertera struktury dokumentu markdown (`MarkdownDocument`) do określonego formatu, na przykład HTML.

Klasa `HtmlConverter` implementuje interfejs `IConverter` w celu zamiany dokumentu markdown w dokument HTML.

## Elementy z laboratorium

Do wykonania projektu wykorzystano poniższe elementy przedstawione w czasie zajęć laboratoryjnych oraz elementy dodatkowe:

-   biblioteka regex - wykorzystana do tokenizacji i parsowania składni markdown;
-   biblioteka variant - wykorzystana do przechowywania przetworzonej struktury markdown;
-   biblioteka future - async oraz future wykorzystane do tokenizacji składni dokumentu oraz obsługi systemu plików;
-   biblioteka ranges (w praktyce range-v3) - wykorzystana do przechodzenia przez strukturę dokumentu, split_view wykorzystane do podziału string_view na linie;
-   biblioteka semaphore - wykorzystana do synchronizacji operacji na plikach;
-   biblioteka atomic - wykorzystana do przechowania unikalnego identyfikatora karty edytora (Tab);
-   biblioteka filesystem - wykorzystana do wykonywania operacji na systemie plików (np. sprawdzanie, czy plik istnieje, tworzenie struktury katalogów itp.).

## Ciekawe elementy

Wielowątkowy tokenizer zaimplementowany z wykorzystaniem `std::regex` oraz `std::variant`.

Maszyna stanów zaimplementowana z wykorzystaniem stosu przechowującego aktualny poziom zagnieżdżenia parsowania, `std::variant` i `std::visit` służące do przechowywania i przechodzenia przez tokeny oraz strukturę dokumentu.

Interfejs konwertera pozwalający na tworzenie klas przetwarzających strukturę dokumentu na dowolny format (zaimplementowany został konwerter tworzący dokument w formacie HTML, na podstawie którego może zostać również stworzony plik w formacie PDF).

## Napotkane problemy

Początkowo problemem okazało się zagnieżdżanie elementów takich jak pogrubienie i kursywa. Z tego powodu stworzony został typ `std::variant` pozwalający na przechowanie obiektów klas, które mogą być zagnieżdżane.

Kolejnym problemem były cykliczne zależności, które w ww. sytuacji wystąpiły. W celu ich rozwiązania, wykorzystany został inteligentny wskaźnik współdzielony, co pozwoliło na predeklarowanie zagnieżdżalnych klas i wyeliminowanie konieczności dołączania ich właściwych deklaracji do czasu wykorzystania.

Z powodu braku bezpośredniego wsparcia `string_view` przez bibliotekę `ranges`, wykorzystano iteratory.

Ponieważ część standardu C++20 dotycząca biblioteki `ranges` nie została jeszcze w pełni zaimplementowana w kompilatorach, do projektu dołączona została biblioteka `range-v3`, na podstawie której powstała biblioteka znajdująca się w standardzie.

## Możliwości dalszego rozwoju

W przyszłości program mógłby zostać rozbudowany o:

-   implementację innych dialektów3 (ang. flavors) składni markdown parsera (przykładowo obsługa tabel czy wstawiania elementów interaktywnych takich jak pola wyboru albo filmy ze znanych serwisów takich jak YouTube czy vimeo);
-   możliwość wyboru fontu eksportowanego dokumentu w formacie PDF;
-   rozdzielenie fontu edytora od podglądu;
-   możliwość konwersji dokumentów innego formatu do formatu markdown;
-   połączenie za pomocą API z serwisami gita takimi jak GitHub czy GitLab w celu szybkiej aktualizacji treści plików markdown.

## Wykorzystanie elementów zewnętrznych

W projekcie wykorzystano następujące licencjonowane elementy:

|                     |                                                                                           |                                                                                           |
| ------------------- | ----------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| Qt 6                | https://www.qt.io/                                                                        | [GNU LGPL v3](https://doc.qt.io/qt-6/lgpl.html)                                           |
| range-v3            | [@ericniebler/range-v3](https://github.com/ericniebler/range-v3/)                         | [Boost Software License](https://github.com/ericniebler/range-v3/blob/master/LICENSE.txt) |
| BoxIcons            | https://boxicons.com/                                                                     | [The MIT License](https://boxicons.com/usage#license)                                     |
| Markdown Cheatsheet | [@adam-p/markdown-here](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) | [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/)                                 |

## Wnioski

Dzięki wykorzystaniu typu `std::variant`, parsowanie drzewa markdown zostało znacznie uproszczone (wykorzystanie polimorfizmu w tym przypadku byłoby o wiele mniej czytelne).

Do wstępnego przetwarzania składni markdown zdecydowanie przydała się biblioteka `regex`.

Kiedy wymagane jest połączenie różnych technologii, można rozważyć stworzenie biblioteki linkowanej.
