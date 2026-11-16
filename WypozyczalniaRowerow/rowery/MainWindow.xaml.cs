
using System;
using System.Collections.ObjectModel;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace rowery
{
    // Klasa przechowująca informacje o jednym rowerze
    public class Rower
    {
        public int Id { get; set; }
        public string Opis { get; set; }
        public string Rodzaj { get; set; }
        public double Cena { get; set; }
        public bool Wypozyczony { get; set; }

        // Właściwość zwracająca aktualny status roweru
        public string Status
        {
            get
            {
                return Wypozyczony ? "Wypożyczony" : "Dostępny";
            }
        }
    }

    public partial class MainWindow : Window
    {
        // Lista przechowująca wszystkie rowery
        ObservableCollection<Rower> rowery =
            new ObservableCollection<Rower>();

        // Konstruktor głównego okna programu
        public MainWindow()
        {
            InitializeComponent();

            // Połączenie listy rowerów z tabelą
            TabelaRowerow.ItemsSource = rowery;
        }

        // FUNKCJA WYSZUKUJĄCA ROWER PO ID
        private Rower ZnajdzRower(int id)
        {
            // Wyszukanie roweru o podanym numerze ID
            return rowery.FirstOrDefault(r => r.Id == id);
        }

        // FUNKCJA DODAJĄCA NOWY ROWER
        private void DodajRower_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // Sprawdzenie, czy podano poprawne ID
                if (!int.TryParse(IdBox.Text, out int id) || id < 0)
                {
                    MessageBox.Show("Podaj poprawne ID!");
                    return;
                }

                // Pobranie opisu roweru
                string opis = OpisBox.Text.Trim();

                // Sprawdzenie, czy opis nie jest pusty
                if (opis == "")
                {
                    MessageBox.Show("Podaj opis roweru!");
                    return;
                }

                // Sprawdzenie, czy wybrano rodzaj roweru
                if (!(RodzajBox.SelectedItem is ComboBoxItem item))
                {
                    MessageBox.Show("Wybierz rodzaj roweru!");
                    return;
                }

                // Pobranie wybranego rodzaju roweru
                string rodzaj = item.Content.ToString();

                // Zamiana przecinka na kropkę w cenie
                string tekstCeny = CenaBox.Text.Replace(',', '.');

                // Sprawdzenie, czy cena jest poprawną liczbą
                if (!double.TryParse(
                    tekstCeny,
                    NumberStyles.Any,
                    CultureInfo.InvariantCulture,
                    out double cena))
                {
                    MessageBox.Show("Podaj poprawną cenę!");
                    return;
                }

                // Sprawdzenie, czy cena nie jest ujemna
                if (cena < 0)
                {
                    MessageBox.Show("Cena nie może być ujemna!");
                    return;
                }

                // Sprawdzenie, czy rower o takim ID już istnieje
                if (ZnajdzRower(id) != null)
                {
                    MessageBox.Show("Rower o takim ID już istnieje!");
                    return;
                }

                // Utworzenie nowego obiektu roweru
                Rower nowyRower = new Rower
                {
                    Id = id,
                    Opis = opis,
                    Rodzaj = rodzaj,
                    Cena = cena,
                    Wypozyczony = false
                };

                // Dodanie roweru do listy
                rowery.Add(nowyRower);

                // Odświeżenie tabeli
                TabelaRowerow.Items.Refresh();

                // Wyświetlenie komunikatu o powodzeniu
                MessageBox.Show("Dodano rower!");

                // Wyczyszczenie pól formularza
                IdBox.Clear();
                OpisBox.Clear();
                CenaBox.Clear();
                RodzajBox.SelectedIndex = -1;
            }
            catch (Exception ex)
            {
                // Wyświetlenie informacji o błędzie
                MessageBox.Show("Wystąpił błąd: " + ex.Message);
            }
        }

        // FUNKCJA WYPOŻYCZAJĄCA ROWER
        private void WypozyczRower_Click(object sender, RoutedEventArgs e)
        {
            // Sprawdzenie, czy wybrano rower z tabeli
            if (!(TabelaRowerow.SelectedItem is Rower rower))
            {
                MessageBox.Show("Najpierw wybierz rower z tabeli!");
                return;
            }

            // Sprawdzenie, czy rower nie jest już wypożyczony
            if (rower.Wypozyczony)
            {
                MessageBox.Show("Ten rower jest już wypożyczony!");
                return;
            }

            // Zmiana statusu roweru na wypożyczony
            rower.Wypozyczony = true;

            // Odświeżenie tabeli
            TabelaRowerow.Items.Refresh();

            // Wyświetlenie zdjęcia wybranego roweru
            PokazZdjecie(rower);

            // Wyświetlenie komunikatu
            MessageBox.Show(
                "Rower został wypożyczony!",
                "Wypożyczalnia rowerów",
                MessageBoxButton.OK,
                MessageBoxImage.Information
            );
        }

        // FUNKCJA ZWRACAJĄCA ROWER I OBLICZAJĄCA KOSZT
        private void ZwrocRower_Click(object sender, RoutedEventArgs e)
        {
            // Sprawdzenie, czy wybrano rower
            if (!(TabelaRowerow.SelectedItem is Rower rower))
            {
                MessageBox.Show("Najpierw wybierz rower z tabeli!");
                return;
            }

            // Sprawdzenie, czy rower jest wypożyczony
            if (!rower.Wypozyczony)
            {
                MessageBox.Show("Ten rower nie jest wypożyczony!");
                return;
            }

            // Pobranie liczby godzin i zamiana przecinka na kropkę
            string tekstGodzin = GodzinyBox.Text.Replace(',', '.');

            // Sprawdzenie poprawności liczby godzin
            if (!double.TryParse(
                tekstGodzin,
                NumberStyles.Any,
                CultureInfo.InvariantCulture,
                out double godziny) || godziny <= 0)
            {
                MessageBox.Show("Podaj poprawną liczbę godzin!");
                return;
            }

            // Obliczenie całkowitego kosztu wypożyczenia
            double koszt = godziny * rower.Cena;

            // Przygotowanie treści rachunku
            string rachunek =
                "========== RACHUNEK ==========\n\n" +
                "ID roweru: " + rower.Id + "\n" +
                "Opis: " + rower.Opis + "\n" +
                "Rodzaj: " + rower.Rodzaj + "\n\n" +
                "Cena za godzinę: " +
                rower.Cena.ToString("F2") + " zł\n" +
                "Liczba godzin: " + godziny + "\n\n" +
                "==============================\n" +
                "DO ZAPŁATY: " + koszt.ToString("F2") + " zł\n" +
                "==============================\n\n" +
                "Dziękujemy za skorzystanie z naszych usług!";

            // Zmiana statusu roweru na dostępny
            rower.Wypozyczony = false;

            // Odświeżenie tabeli po zwrocie roweru
            TabelaRowerow.Items.Refresh();

            // Wyczyszczenie pola z liczbą godzin
            GodzinyBox.Clear();

            // Wyświetlenie rachunku w osobnym komunikacie
            MessageBox.Show(
                rachunek,
                "Rachunek za wypożyczenie",
                MessageBoxButton.OK,
                MessageBoxImage.Information
            );
        }

        // FUNKCJA WYŚWIETLAJĄCA ZDJĘCIE ROWERU
        private void PokazZdjecie(Rower rower)
        {
            // Zmienna przechowująca nazwę pliku ze zdjęciem
            string plik = "";

            // Wybranie zdjęcia na podstawie rodzaju roweru
            switch (rower.Rodzaj)
            {
                case "Górski":
                    plik = "gorski.jpg";
                    break;

                case "Miejski":
                    plik = "miejski.jpg";
                    break;

                case "Szosowy":
                    plik = "szosowy.jpg";
                    break;
            }

            // Zakończenie funkcji, jeśli nie znaleziono nazwy pliku
            if (plik == "")
                return;

            // Utworzenie pełnej ścieżki do zdjęcia
            string sciezka = Path.Combine(
                AppDomain.CurrentDomain.BaseDirectory,
                "Images",
                plik
            );

            try
            {
                // Sprawdzenie, czy plik ze zdjęciem istnieje
                if (!File.Exists(sciezka))
                {
                    ZdjecieRoweru.Source = null;

                    MessageBox.Show(
                        "Nie znaleziono zdjęcia!\n\n" +
                        "Szukana lokalizacja:\n" + sciezka +
                        "\n\nSprawdź ustawienia pliku w Visual Studio."
                    );

                    return;
                }

                // Utworzenie obiektu zdjęcia
                BitmapImage obraz = new BitmapImage();

                // Rozpoczęcie wczytywania zdjęcia
                obraz.BeginInit();

                // Wczytanie zdjęcia do pamięci
                obraz.CacheOption = BitmapCacheOption.OnLoad;

                // Ustawienie ścieżki do zdjęcia
                obraz.UriSource = new Uri(
                    sciezka,
                    UriKind.Absolute
                );

                // Zakończenie wczytywania zdjęcia
                obraz.EndInit();

                // Wyświetlenie zdjęcia w oknie programu
                ZdjecieRoweru.Source = obraz;
            }
            catch (Exception ex)
            {
                // Obsługa błędu podczas wczytywania zdjęcia
                MessageBox.Show(
                    "Błąd wczytywania zdjęcia:\n" + ex.Message
                );
            }
        }

        // FUNKCJA URUCHAMIANA PO WYBRANIU ROWERU W TABELI
        private void TabelaRowerow_SelectionChanged(
            object sender,
            SelectionChangedEventArgs e)
        {
            // Sprawdzenie, czy wybrano rower
            if (TabelaRowerow.SelectedItem is Rower rower)
            {
                // Wyświetlenie zdjęcia wybranego roweru
                PokazZdjecie(rower);
            }
        }
    }
}
