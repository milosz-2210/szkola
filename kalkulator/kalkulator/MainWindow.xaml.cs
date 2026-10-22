
using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;

namespace kalkulator
{
    public partial class MainWindow : Window
    {
        // Przechowuje pierwszą liczbę w działaniu matematycznym.
        // Typ double pozwala zapisywać również liczby dziesiętne.
        private double pierwszaLiczba = 0;

        // Przechowuje wybrane działanie: +, -, * lub /.
        private string dzialanie = "";

        // Określa, czy użytkownik zaczyna wpisywać nową liczbę.
        // true oznacza, że następna cyfra zastąpi aktualny wynik.
        private bool nowaLiczba = true;

        // Ustawia polskie formatowanie liczb, np. 2,5 zamiast 2.5.
        private readonly CultureInfo kultura =
            CultureInfo.GetCultureInfo("pl-PL");

        // Konstruktor okna. Uruchamia się podczas otwierania kalkulatora.
        public MainWindow()
        {
            // Wczytuje elementy interfejsu z pliku MainWindow.xaml.
            InitializeComponent();
        }

        // FUNKCJA WPISYWANIA CYFR
        // Uruchamia się po kliknięciu przycisku od 0 do 9.
        private void Cyfra_Click(object sender, RoutedEventArgs e)
        {
            // Pobiera cyfrę z przycisku, który został kliknięty.
            // sender oznacza element wywołujący tę funkcję.
            string cyfra = ((Button)sender).Content.ToString();

            // Jeżeli zaczynamy nową liczbę albo na ekranie jest zero,
            // zastępujemy dotychczasową zawartość nową cyfrą.
            if (nowaLiczba || Wynik.Text == "0")
            {
                Wynik.Text = cyfra;
                nowaLiczba = false;
            }
            else
            {
                // Dopisuje cyfrę na końcu aktualnej liczby.
                Wynik.Text += cyfra;
            }
        }

        // FUNKCJA WPISYWANIA PRZECINKA
        // Pozwala wprowadzać liczby dziesiętne, np. 3,14.
        private void Przecinek_Click(object sender, RoutedEventArgs e)
        {
            // Jeżeli zaczynamy nową liczbę, wyświetlamy 0,
            // a następnie przecinek.
            if (nowaLiczba)
            {
                Wynik.Text = "0,";
                nowaLiczba = false;
            }
            // Nie pozwala dodać drugiego przecinka do tej samej liczby.
            else if (!Wynik.Text.Contains(","))
            {
                Wynik.Text += ",";
            }
        }

        // FUNKCJA WYBORU DZIAŁANIA
        // Uruchamia się po kliknięciu +, −, × lub ÷.
        private void Dzialanie_Click(object sender, RoutedEventArgs e)
        {
            // Zamienia tekst wyświetlany na ekranie na liczbę typu double.
            // TryParse sprawdza, czy tekst jest poprawną liczbą.
            // Wynik konwersji zostaje zapisany w pierwszaLiczba.
            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out pierwszaLiczba))
            {
                // Jeżeli konwersja się nie powiedzie, kończy funkcję.
                return;
            }

            // Pobiera znak z klikniętego przycisku.
            string znak = ((Button)sender).Content.ToString();

            // Wybiera działanie na podstawie klikniętego znaku.
            switch (znak)
            {
                case "+":
                    dzialanie = "+";
                    break;

                case "−":
                    // Znak widoczny na przycisku jest zamieniany
                    // na standardowy minus używany w obliczeniach.
                    dzialanie = "-";
                    break;

                case "×":
                    // Gwiazdka oznacza mnożenie w języku C#.
                    dzialanie = "*";
                    break;

                case "÷":
                    // Ukośnik oznacza dzielenie w języku C#.
                    dzialanie = "/";
                    break;
            }

            // Następna wpisywana cyfra rozpocznie drugą liczbę.
            nowaLiczba = true;
        }

        // FUNKCJA OBLICZANIA WYNIKU
        // Uruchamia się po kliknięciu przycisku "=".
        private void Wynik_Click(object sender, RoutedEventArgs e)
        {
            // Nie obliczamy, jeśli nie wybrano działania
            // albo użytkownik nie wpisał jeszcze drugiej liczby.
            if (dzialanie == "" || nowaLiczba)
                return;

            // Odczytuje drugą liczbę z wyświetlacza.
            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out double drugaLiczba))
            {
                return;
            }

            // Zmienna przechowująca końcowy wynik działania.
            double wynik;

            // Wykonuje działanie wybrane wcześniej przez użytkownika.
            switch (dzialanie)
            {
                case "+":
                    wynik = pierwszaLiczba + drugaLiczba;
                    break;

                case "-":
                    wynik = pierwszaLiczba - drugaLiczba;
                    break;

                case "*":
                    wynik = pierwszaLiczba * drugaLiczba;
                    break;

                case "/":
                    // Sprawdza, czy druga liczba nie jest zerem.
                    // Dzielenie przez zero jest niedozwolone.
                    if (drugaLiczba == 0)
                    {
                        // Wyświetla komunikat ostrzegawczy.
                        MessageBox.Show(
                            "Nie można dzielić przez zero!",
                            "Błąd",
                            MessageBoxButton.OK,
                            MessageBoxImage.Warning);

                        // Kończy funkcję bez wykonywania dzielenia.
                        return;
                    }

                    wynik = pierwszaLiczba / drugaLiczba;
                    break;

                default:
                    // Kończy funkcję, jeśli działanie jest nieznane.
                    return;
            }

            // Wyświetla wynik jako tekst.
            // Format "G" pokazuje liczbę w ogólnym formacie.
            Wynik.Text = wynik.ToString("G", kultura);

            // Czyści wybrane działanie.
            dzialanie = "";

            // Pozwala rozpocząć wpisywanie następnej liczby.
            nowaLiczba = true;
        }

        // FUNKCJA CZYSZCZENIA KALKULATORA
        // Uruchamia się po kliknięciu przycisku C.
        private void Wyczysc_Click(object sender, RoutedEventArgs e)
        {
            // Przywraca początkowy stan kalkulatora.
            Wynik.Text = "0";
            pierwszaLiczba = 0;
            dzialanie = "";
            nowaLiczba = true;
        }

        // FUNKCJA USUWANIA OSTATNIEJ CYFRY
        // Uruchamia się po kliknięciu przycisku ⌫.
        private void Usun_Click(object sender, RoutedEventArgs e)
        {
            // Nie usuwa cyfry, gdy oczekujemy na wpisanie nowej liczby.
            if (nowaLiczba)
                return;

            // Jeżeli tekst ma więcej niż jeden znak,
            // usuwa ostatni znak z wyświetlacza.
            if (Wynik.Text.Length > 1)
            {
                Wynik.Text = Wynik.Text.Substring(
                    0, Wynik.Text.Length - 1);

                // Jeśli po usunięciu pozostał sam minus,
                // przywraca zero.
                if (Wynik.Text == "-" || Wynik.Text == "")
                    Wynik.Text = "0";
            }
            else
            {
                // Jeśli pozostała tylko jedna cyfra,
                // zamiast pustego ekranu wyświetla zero.
                Wynik.Text = "0";
            }
        }

        // FUNKCJA ZMIANY ZNAKU LICZBY
        // Uruchamia się po kliknięciu przycisku ±.
        private void Znak_Click(object sender, RoutedEventArgs e)
        {
            // Odczytuje liczbę z wyświetlacza.
            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out double liczba))
            {
                return;
            }

            // Zmienia znak liczby na przeciwny.
            // Np. 5 zmienia się na -5, a -5 na 5.
            Wynik.Text = (-liczba).ToString("G", kultura);

            // Informuje kalkulator, że aktualna liczba jest edytowana.
            nowaLiczba = false;
        }
    }
}
