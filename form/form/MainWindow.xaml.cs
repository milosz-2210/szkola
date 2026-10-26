
using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace form
{
    public partial class MainWindow : Window
    {
        // Ścieżka do pliku, w którym będą zapisywane odpowiedzi ankiety.
        // Plik ankieta.txt znajdzie się w katalogu uruchomionego programu.
        private readonly string plik = Path.Combine(
            AppDomain.CurrentDomain.BaseDirectory,
            "ankieta.txt");

        public MainWindow()
        {
            InitializeComponent(); // Inicjalizacja elementów okna z XAML.

            PokazWyniki(); // Wyświetlenie wyników zapisanych wcześniej w pliku.
        }

        // Metoda wykonywana po kliknięciu przycisku „Zapisz”.
        private void Zapisz_Click(object sender, RoutedEventArgs e)
        {
            string plec = "";

            // Sprawdzenie, która opcja płci została zaznaczona.
            if (rbMezczyzna.IsChecked == true)
                plec = "Mężczyzna";
            else if (rbKobieta.IsChecked == true)
                plec = "Kobieta";
            else if (rbInne.IsChecked == true)
                plec = "Inne";

            // Sprawdzenie, czy użytkownik wybrał płeć.
            if (plec == "")
            {
                MessageBox.Show("Wybierz płeć!");
                return; // Przerwanie metody, jeśli dane są niepoprawne.
            }

            // TryParse sprawdza, czy wpisany tekst można zamienić na liczbę.
            // Wiek musi mieścić się w zakresie od 0 do 120 lat.
            if (!int.TryParse(txtWiek.Text, out int wiek)
                || wiek < 0 || wiek > 120)
            {
                MessageBox.Show(
                    "Wpisz poprawny wiek od 0 do 120!");
                return;
            }

            // Sprawdzenie, czy wybrano pozycję z listy kolorów.
            if (cmbKolor.SelectedItem is not ComboBoxItem item)
            {
                MessageBox.Show("Wybierz kolor!");
                return;
            }

            // Pobranie nazwy wybranego koloru.
            string kolor = item.Content.ToString()!;

            // Sprawdzenie, czy pole zgody jest zaznaczone.
            bool zgoda = chkZgoda.IsChecked == true;

            // Połączenie odpowiedzi w jeden tekst oddzielony średnikami.
            // Kolejność: płeć;wiek;kolor;zgoda.
            string dane = $"{plec};{wiek};{kolor};{zgoda}";

            try
            {
                // Dopisanie odpowiedzi na końcu pliku.
                // Environment.NewLine dodaje nową linię.
                File.AppendAllText(
                    plik,
                    dane + Environment.NewLine);

                MessageBox.Show("Ankieta została zapisana!");

                // Czyszczenie formularza po zapisaniu odpowiedzi.
                rbMezczyzna.IsChecked = false;
                rbKobieta.IsChecked = false;
                rbInne.IsChecked = false;

                txtWiek.Clear(); // Usunięcie wpisanego wieku.

                cmbKolor.SelectedIndex = 0; // Powrót do pierwszego koloru.
                chkZgoda.IsChecked = false; // Odznaczenie zgody.

                // Ponowne obliczenie i wyświetlenie statystyk.
                PokazWyniki();
            }
            catch (Exception ex)
            {
                // Wyświetlenie komunikatu, jeśli zapis do pliku się nie uda.
                MessageBox.Show(
                    "Błąd zapisu: " + ex.Message);
            }
        }

        // Metoda odczytuje zapisane ankiety i oblicza statystyki.
        private void PokazWyniki()
        {
            // Jeśli plik istnieje, odczytujemy wszystkie jego linie.
            // Jeśli nie istnieje, tworzymy pustą listę osób.
            var osoby = File.Exists(plik)
                ? File.ReadAllLines(plik)

                    // Pominięcie pustych linii w pliku.
                    .Where(l => !string.IsNullOrWhiteSpace(l))

                    // Podział każdej linii na pola przy średniku.
                    .Select(l => l.Split(';'))

                    // Sprawdzenie poprawności liczby pól,
                    // wieku oraz zapisanego statusu zgody.
                    .Where(p => p.Length == 4
                        && int.TryParse(p[1], out _)
                        && (p[3] == "True"
                            || p[3] == "False"))

                    // Zamiana tekstu z pliku na dane osoby.
                    .Select(p => new
                    {
                        Plec = p[0],
                        Wiek = int.Parse(p[1]),
                        Kolor = p[2],
                        Zgoda = p[3] == "True"
                    })
                    .ToList() // Utworzenie listy wszystkich osób.
                : new();

            // Jeśli nie ma żadnych poprawnych ankiet,
            // ustawiamy domyślne wyniki i kończymy metodę.
            if (osoby.Count == 0)
            {
                txtSredniWiek.Text = "Średni wiek: 0";
                txtKolor.Text = "Najczęstszy kolor: brak";
                txtMezczyzni.Text = "Liczba mężczyzn: 0";
                txtKobiety.Text = "Liczba kobiet: 0";
                txtZgody.Text = "Liczba zgód: 0";
                return;
            }

            // Obliczenie średniego wieku wszystkich osób.
            // Average sumuje wartości i dzieli je przez ich liczbę.
            double sredniWiek =
                osoby.Average(o => o.Wiek);

            // Grupowanie osób według wybranego koloru.
            // Następnie sortowanie grup od najliczniejszej.
            // First().Key pobiera nazwę najczęściej wybieranego koloru.
            string kolor = osoby
                .GroupBy(o => o.Kolor)
                .OrderByDescending(g => g.Count())
                .First()
                .Key;

            // Zliczenie osób, które wybrały daną płeć.
            int mezczyzni =
                osoby.Count(o => o.Plec == "Mężczyzna");

            int kobiety =
                osoby.Count(o => o.Plec == "Kobieta");

            // Zliczenie osób, które zaznaczyły zgodę.
            int zgody =
                osoby.Count(o => o.Zgoda);

            // Wyświetlenie średniego wieku.
            // Round zaokrągla wynik do pełnej liczby lat.
            txtSredniWiek.Text =
                $"Średni wiek: {Math.Round(sredniWiek, MidpointRounding.AwayFromZero):F0} lat";

            // Wyświetlenie najczęściej wybieranego koloru.
            txtKolor.Text =
                $"Najczęstszy kolor: {kolor}";

            // Wyświetlenie liczby mężczyzn.
            txtMezczyzni.Text =
                $"Liczba mężczyzn: {mezczyzni}";

            // Wyświetlenie liczby kobiet.
            txtKobiety.Text =
                $"Liczba kobiet: {kobiety}";

            // Wyświetlenie liczby udzielonych zgód.
            txtZgody.Text =
                $"Liczba zgód: {zgody}";
        }
    }
}
