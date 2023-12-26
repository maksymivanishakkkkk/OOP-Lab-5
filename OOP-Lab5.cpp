// OOP-Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

using System;
using System.Collections.Generic;
using System.IO;

public enum ProductType
{
    Electronics,
    Clothing,
    Food,
    Other
}

public struct Product
{
    public int WarehouseNumber;
    public ProductType Type;
    public string ProductCode;
    public string ProductName;
    public DateTime ArrivalDate;
    public int ShelfLifeDays;
    public int Quantity;
    public double PricePerUnit;
}

class Program
{
    static void Main(string[] args)
    {
        List<Product> products = new List<Product>();

        // Зчитуємо дані з файлу (якщо файл існує)
        if (File.Exists("products.txt"))
        {
            string[] lines = File.ReadAllLines("products.txt");
            foreach(string line in lines)
            {
                string[] data = line.Split(',');
                Product product = new Product
                {
                    WarehouseNumber = int.Parse(data[0]),
                    Type = (ProductType)Enum.Parse(typeof(ProductType), data[1]),
                    ProductCode = data[2],
                    ProductName = data[3],
                    ArrivalDate = DateTime.Parse(data[4]),
                    ShelfLifeDays = int.Parse(data[5]),
                    Quantity = int.Parse(data[6]),
                    PricePerUnit = double.Parse(data[7])
                };
                products.Add(product);
            }
        }

        // Введення даних користувачем
        Console.WriteLine("Введіть дані товару:");
        Product newProduct = new Product();
        Console.Write("Номер складу: ");
        newProduct.WarehouseNumber = int.Parse(Console.ReadLine());
        Console.Write("Вид товару (Electronics, Clothing, Food, Other): ");
        newProduct.Type = (ProductType)Enum.Parse(typeof(ProductType), Console.ReadLine());
        Console.Write("Код товару: ");
        newProduct.ProductCode = Console.ReadLine();
        Console.Write("Найменування товару: ");
        newProduct.ProductName = Console.ReadLine();
        Console.Write("Дата появи на складі (рррр-мм-дд): ");
        newProduct.ArrivalDate = DateTime.Parse(Console.ReadLine());
        Console.Write("Термін збереження в днях: ");
        newProduct.ShelfLifeDays = int.Parse(Console.ReadLine());
        Console.Write("Кількість одиниць товару: ");
        newProduct.Quantity = int.Parse(Console.ReadLine());
        Console.Write("Ціна за одиницю: ");
        newProduct.PricePerUnit = double.Parse(Console.ReadLine());

        // Додавання нового товару до колекції
        products.Add(newProduct);

        // Запис даних у файл
        using (StreamWriter writer = new StreamWriter("products.txt"))
        {
            foreach(Product product in products)
            {
                writer.WriteLine($"{product.WarehouseNumber},{product.Type},{product.ProductCode},{product.ProductName},{product.ArrivalDate},{product.ShelfLifeDays},{product.Quantity},{product.PricePerUnit}");
            }
        }

        // Пошук за номером складу
        Console.Write("Введіть номер складу для пошуку: ");
        int searchWarehouseNumber = int.Parse(Console.ReadLine());
        List<Product> productsInWarehouse = products.FindAll(product = > product.WarehouseNumber == searchWarehouseNumber);
        if (productsInWarehouse.Count > 0)
        {
            Console.WriteLine("Товари на складі з вказаним номером:");
            foreach(Product product in productsInWarehouse)
            {
                Console.WriteLine($"Тип: {product.Type}, Код: {product.ProductCode}, Назва: {product.ProductName}, Дата появи: {product.ArrivalDate}, Термін збереження: {product.ShelfLifeDays} днів, Кількість: {product.Quantity}, Ціна за одиницю: {product.PricePerUnit}");
            }
        }
        else
        {
            Console.WriteLine("Товари на складі з вказаним номером не знайдені.");
        }

        // Пошук за типом товару
        Console.Write("Введіть тип товару для пошуку: ");
        ProductType searchType = (ProductType)Enum.Parse(typeof(ProductType), Console.ReadLine());
        List<Product> productsOfType = products.FindAll(product = > product.Type == searchType);
        if (productsOfType.Count > 0)
        {
            Console.WriteLine("Товари з вказаним типом:");
            foreach(Product product in productsOfType)
            {
                Console.WriteLine($"Номер складу: {product.WarehouseNumber}, Код: {product.ProductCode}, Назва: {product.ProductName}, Дата появи: {product.ArrivalDate}, Термін збереження: {product.ShelfLifeDays} днів, Кількість: {product.Quantity}, Ціна за одиницю: {product.PricePerUnit}");
            }
        }
        else
        {
            Console.WriteLine("Товари з вказаним типом не знайдені.");
        }

        // Пошук за найменуванням товару
        Console.Write("Введіть найменування товару для пошуку: ");
        string searchProductName = Console.ReadLine();
        List<Product> productsByName = products.FindAll(product = > product.ProductName.Contains(searchProductName));
        if (productsByName.Count > 0)
        {
            Console.WriteLine("Товари з вказаним найменуванням:");
            foreach(Product product in productsByName)
            {
                Console.WriteLine($"Номер складу: {product.WarehouseNumber}, Тип: {product.Type}, Код: {product.ProductCode}, Дата появи: {product.ArrivalDate}, Термін збереження: {product.ShelfLifeDays} днів, Кількість: {product.Quantity}, Ціна за одиницю: {product.PricePerUnit}");
            }
        }
        else
        {
            Console.WriteLine("Товари з вказаним найменуванням не знайдені.");
        }
    }
}
