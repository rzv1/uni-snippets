using System;
using System.Collections.Generic;
using System.Diagnostics;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Data.Core.Plugins;
using System.Linq;
using Avalonia.Markup.Xaml;
using L01.Models;
using L01.ViewModels;
using L01.Views;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Caching.Memory;

namespace L01;

public partial class App : Application
{
    public override void Initialize()
    {
        AvaloniaXamlLoader.Load(this);
    }

    private void ConnectionsNonPooling()
    {
        var connectionString = "Data Source=sqlite.db;Pooling=false;";
        var contexts = new List<AppDbContext>();
        var meanTime = new List<double>();
        var sw = Stopwatch.StartNew();

        for (var i = 0; i < 100; i++)
        {
            var startTime = DateTime.Now;
            var connection = new AppDbContext(connectionString);
            connection.Database.OpenConnection();
            var endTime = DateTime.Now;
            meanTime.Add(endTime.Subtract(startTime).TotalMilliseconds);
            contexts.Add(connection);
        }
        sw.Stop();
        contexts.ForEach(c =>
        {
            c.Database.CloseConnection();
            c.Dispose();
        });
        Console.WriteLine("Created 100 connections in " + sw.ElapsedMilliseconds + "ms. Average 1 connection time " + meanTime.Sum()/meanTime.Count + "ms. (Pooling=false)");
    }

    private void ConnectionsPooling()
    {
        var connectionString = "Data Source=sqlite.db;Pooling=true;";
        var contexts = new List<AppDbContext>();
        var meanTime = new List<double>();
        var sw = Stopwatch.StartNew();

        for (var i = 0; i < 100; i++)
        {
            var startTime = DateTime.Now; 
            var connection = new AppDbContext(connectionString);
            connection.Database.OpenConnection();
            var endTime = DateTime.Now;
            meanTime.Add(endTime.Subtract(startTime).TotalMilliseconds);
            contexts.Add(connection);
        }
        sw.Stop();
        contexts.ForEach(c =>
        {
            c.Database.CloseConnection();
            c.Dispose();
        });
        Console.WriteLine("Created 100 connections in " + sw.ElapsedMilliseconds + "ms. Average 1 connection time " + meanTime.Sum()/meanTime.Count + "ms. (Pooling=true)");

    }

    private void ConnectionOverflow()
    {
        var connectionString = "Data Source=sqlite.db;Pooling=true;";
        var contexts = new List<AppDbContext>();

        try
        {
            Console.WriteLine("--- Demonstratie Connection Leak ---");
    
            for (var i = 1; i <= 10; i++)
            {
                Console.WriteLine($"Deschid conexiunea nr. {i}.");
                var db = new AppDbContext(connectionString);
                db.Database.OpenConnection(); 
                contexts.Add(db);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("\n[EROARE] Pool-ul a fost epuizat!");
            Console.WriteLine($"Mesaj: {ex.Message}");
        }
    }

    public void ConnectionOverflowSolution()
    {
        var connectionString = "Data Source=sqlite.db;Pooling=true;";

        for (var i = 1; i <= 10; i++)
        {
            using var db = new AppDbContext(connectionString);
            Console.WriteLine($"Deschid conexiunea nr. {i}.");
            db.Database.OpenConnection(); 
        }
        Console.WriteLine("10 conexiuni in pool size 5.");
    }

    public void GenerateSchema(string connectionString)
    {
        using (var db = new AppDbContext(connectionString))
        {
            db.Database.EnsureDeleted();
            db.Database.EnsureCreated();
        }
    }

    public override void OnFrameworkInitializationCompleted()
    {
        if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
        {
            // Avoid duplicate validations from both Avalonia and the CommunityToolkit. 
            // More info: https://docs.avaloniaui.net/docs/guides/development-guides/data-validation#manage-validationplugins
            DisableAvaloniaDataAnnotationValidation();
            ConnectionsNonPooling();
            ConnectionsPooling();
            ConnectionOverflow();
            ConnectionOverflowSolution();

            var connectionString = "Data Source=sqlite.db"; 


            var cache = new MemoryCache(new MemoryCacheOptions());
            
            /*
             string key = "timestamp_cache";
        
            for (int i = 0; i < 5; i++)
            {
                if (!cache.TryGetValue(key, out string time))
                {
                    time = DateTime.Now.ToString("HH:mm:ss.fff");
                    cache.Set(key, time, TimeSpan.FromSeconds(3));
                    Console.WriteLine($"[DB/Logic] Generat: {time}");
                }
                else
                {
                    Console.WriteLine($"[CACHE] Luat din memorie: {time}");
                }

                Thread.Sleep(1000);
            }
            */
            
            //GenerateSchema(connectionString);
            
            //DatabaseManager manager = new DatabaseManager(connectionString);
            //var cRepo = new CustomerRepo(manager); 
            //var pRepo = new PaymentRepo(manager);
            
            var context = new AppDbContext(connectionString);
            var cRepoEF = new CustomerRepoEF(context, cache);
            var pRepoEF = new PaymentRepoEF(context, cache);
            desktop.MainWindow = new MainWindow
            {
                DataContext = new MainWindowViewModel(cRepoEF, pRepoEF),
            };
            //Inchidem conextiunea cu baza de date la terminarea aplicatiei
            //manager.CloseConnection();
        }

        base.OnFrameworkInitializationCompleted();
    }

    private void DisableAvaloniaDataAnnotationValidation()
    {
        // Get an array of plugins to remove
        var dataValidationPluginsToRemove =
            BindingPlugins.DataValidators.OfType<DataAnnotationsValidationPlugin>().ToArray();

        // remove each entry found
        foreach (var plugin in dataValidationPluginsToRemove)
        {
            BindingPlugins.DataValidators.Remove(plugin);
        }
    }
}