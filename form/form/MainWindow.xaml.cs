using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;

namespace form
{
    public partial class MainWindow : Window
    {
        private readonly string plik = Path.Combine(
            AppDomain.CurrentDomain.BaseDirectory,
            "ankieta.txt");

        public MainWindow()
        {
            InitializeComponent();
            PokazWyniki();
        }

        private void Zapisz_Click(object sender, RoutedEventArgs e)
        {
            string plec = "";

            if (rbMezczyzna.IsChecked == true)
                plec = "Mężczyzna";
            else if (rbKobieta.IsChecked == true)
                plec = "Kobieta";
            else if (rbInne.IsChecked == true)
                plec = "Inne";

            if (plec == "")
            {
                MessageBox.Show("Wybierz płeć!");
                return;
            }

            if (!int.TryParse(txtWiek.Text, out int wiek)
                || wiek < 0 || wiek > 120)
            {
                MessageBox.Show(
                    "Wpisz poprawny wiek od 0 do 120!");
                return;
            }

            if (cmbKolor.SelectedItem is not ComboBoxItem item)
            {
                MessageBox.Show("Wybierz kolor!");
                return;
            }

            string kolor = item.Content.ToString()!;
            bool zgoda = chkZgoda.IsChecked == true;

            string dane = $"{plec};{wiek};{kolor};{zgoda}";

            try
            {
                File.AppendAllText(
                    plik,
                    dane + Environment.NewLine);

                MessageBox.Show("Ankieta została zapisana!");

                // Czyszczenie formularza
                rbMezczyzna.IsChecked = false;
                rbKobieta.IsChecked = false;
                rbInne.IsChecked = false;

                txtWiek.Clear();

                cmbKolor.SelectedIndex = 0;
                chkZgoda.IsChecked = false;

                // Aktualizacja wyników
                PokazWyniki();
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    "Błąd zapisu: " + ex.Message);
            }
        }

        private void PokazWyniki()
        {
            var osoby = File.Exists(plik)
                ? File.ReadAllLines(plik)
                    .Where(l => !string.IsNullOrWhiteSpace(l))
                    .Select(l => l.Split(';'))
                    .Where(p => p.Length == 4
                        && int.TryParse(p[1], out _)
                        && (p[3] == "True"
                            || p[3] == "False"))
                    .Select(p => new
                    {
                        Plec = p[0],
                        Wiek = int.Parse(p[1]),
                        Kolor = p[2],
                        Zgoda = p[3] == "True"
                    })
                    .ToList()
                : new();

            if (osoby.Count == 0)
            {
                txtSredniWiek.Text = "Średni wiek: 0";
                txtKolor.Text = "Najczęstszy kolor: brak";
                txtMezczyzni.Text = "Liczba mężczyzn: 0";
                txtKobiety.Text = "Liczba kobiet: 0";
                txtZgody.Text = "Liczba zgód: 0";
                return;
            }

            double sredniWiek =
                osoby.Average(o => o.Wiek);

            string kolor = osoby
                .GroupBy(o => o.Kolor)
                .OrderByDescending(g => g.Count())
                .First()
                .Key;

            int mezczyzni =
                osoby.Count(o => o.Plec == "Mężczyzna");

            int kobiety =
                osoby.Count(o => o.Plec == "Kobieta");

            int zgody =
                osoby.Count(o => o.Zgoda);

            txtSredniWiek.Text =
                   $"Średni wiek: {Math.Round(sredniWiek, MidpointRounding.AwayFromZero):F0} lat";

            txtKolor.Text =
                $"Najczęstszy kolor: {kolor}";

            txtMezczyzni.Text =
                $"Liczba mężczyzn: {mezczyzni}";

            txtKobiety.Text =
                $"Liczba kobiet: {kobiety}";

            txtZgody.Text =
                $"Liczba zgód: {zgody}";
        }
    }
}