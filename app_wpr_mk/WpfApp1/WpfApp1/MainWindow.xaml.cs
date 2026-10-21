using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;

namespace WpfApp1
{
    public partial class MainWindow : Window
    {
        private ObservableCollection<ShoppingItem> products =
            new ObservableCollection<ShoppingItem>();

        public MainWindow()
        {
            InitializeComponent();

            ShoppingList.ItemsSource = products;
            ProductBox.Focus();
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            string name = ProductBox.Text.Trim();

            if (string.IsNullOrWhiteSpace(name))
            {
                MessageBox.Show("Wpisz nazwę produktu!");
                return;
            }

            products.Add(new ShoppingItem
            {
                Name = name,
                IsBought = false
            });

            ProductBox.Clear();
            ProductBox.Focus();
        }

        private void RemoveBought_Click(object sender, RoutedEventArgs e)
        {
            var boughtProducts = products
                .Where(p => p.IsBought)
                .ToList();

            foreach (var product in boughtProducts)
            {
                products.Remove(product);
            }
        }

        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            if (products.Count == 0)
                return;

            MessageBoxResult result = MessageBox.Show(
                "Czy na pewno chcesz wyczyścić całą listę?",
                "Czyszczenie listy",
                MessageBoxButton.YesNo,
                MessageBoxImage.Question);

            if (result == MessageBoxResult.Yes)
            {
                products.Clear();
            }
        }
    }

    public class ShoppingItem : INotifyPropertyChanged
    {
        private string name = "";
        private bool isBought;

        public string Name
        {
            get => name;
            set
            {
                name = value;
                OnPropertyChanged(nameof(Name));
            }
        }

        public bool IsBought
        {
            get => isBought;
            set
            {
                isBought = value;
                OnPropertyChanged(nameof(IsBought));
            }
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(
                this,
                new PropertyChangedEventArgs(propertyName));
        }
    }
}