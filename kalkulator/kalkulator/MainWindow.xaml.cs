using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;

namespace kalkulator
{
    public partial class MainWindow : Window
    {
        private double pierwszaLiczba = 0;
        private string dzialanie = "";
        private bool nowaLiczba = true;

        private readonly CultureInfo kultura =
            CultureInfo.GetCultureInfo("pl-PL");

        public MainWindow()
        {
            InitializeComponent();
        }

        // Wpisywanie cyfr
        private void Cyfra_Click(object sender, RoutedEventArgs e)
        {
            string cyfra = ((Button)sender).Content.ToString();

            if (nowaLiczba || Wynik.Text == "0")
            {
                Wynik.Text = cyfra;
                nowaLiczba = false;
            }
            else
            {
                Wynik.Text += cyfra;
            }
        }

        // Przecinek dziesiętny
        private void Przecinek_Click(object sender, RoutedEventArgs e)
        {
            if (nowaLiczba)
            {
                Wynik.Text = "0,";
                nowaLiczba = false;
            }
            else if (!Wynik.Text.Contains(","))
            {
                Wynik.Text += ",";
            }
        }

        // Wybór działania
        private void Dzialanie_Click(object sender, RoutedEventArgs e)
        {
            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out pierwszaLiczba))
            {
                return;
            }

            string znak = ((Button)sender).Content.ToString();

            switch (znak)
            {
                case "+":
                    dzialanie = "+";
                    break;

                case "−":
                    dzialanie = "-";
                    break;

                case "×":
                    dzialanie = "*";
                    break;

                case "÷":
                    dzialanie = "/";
                    break;
            }

            nowaLiczba = true;
        }

        // Obliczanie wyniku
        private void Wynik_Click(object sender, RoutedEventArgs e)
        {
            if (dzialanie == "" || nowaLiczba)
                return;

            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out double drugaLiczba))
            {
                return;
            }

            double wynik;

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
                    if (drugaLiczba == 0)
                    {
                        MessageBox.Show(
                            "Nie można dzielić przez zero!",
                            "Błąd",
                            MessageBoxButton.OK,
                            MessageBoxImage.Warning);
                        return;
                    }

                    wynik = pierwszaLiczba / drugaLiczba;
                    break;

                default:
                    return;
            }

            Wynik.Text = wynik.ToString("G", kultura);

            dzialanie = "";
            nowaLiczba = true;
        }

        // Czyszczenie kalkulatora
        private void Wyczysc_Click(object sender, RoutedEventArgs e)
        {
            Wynik.Text = "0";
            pierwszaLiczba = 0;
            dzialanie = "";
            nowaLiczba = true;
        }

        // Usuwanie ostatniej cyfry
        private void Usun_Click(object sender, RoutedEventArgs e)
        {
            if (nowaLiczba)
                return;

            if (Wynik.Text.Length > 1)
            {
                Wynik.Text = Wynik.Text.Substring(
                    0, Wynik.Text.Length - 1);

                if (Wynik.Text == "-" || Wynik.Text == "")
                    Wynik.Text = "0";
            }
            else
            {
                Wynik.Text = "0";
            }
        }

        // Zmiana znaku liczby
        private void Znak_Click(object sender, RoutedEventArgs e)
        {
            if (!double.TryParse(
                Wynik.Text,
                NumberStyles.Float,
                kultura,
                out double liczba))
            {
                return;
            }

            Wynik.Text = (-liczba).ToString("G", kultura);
            nowaLiczba = false;
        }
    }
}