using System;
using System.Diagnostics;
using System.Linq;
using L01.Models;
using Microsoft.EntityFrameworkCore;

namespace L01.Services;

public class L04Demo(AppDbContext dbContext)
{
   private readonly AppDbContext _db = dbContext;

    public void SeedData(int customerCount = 10, int paymentsPerCustomer = 1000)
    {
        Console.WriteLine("Seeding data...");
        if (_db.Customer.Count() >= customerCount)
        {
            Console.WriteLine("Data already seeded.");
            return;
        }

        for (int i = 0; i < customerCount; i++)
        {
            var customer = new Customer($"Customer {i}", $"555-{i:D4}");
            _db.Customer.Add(customer);
            _db.SaveChanges(); 

            for (int j = 0; j < paymentsPerCustomer; j++)
            {
                var type = j % 2 == 0 ? "cash" : "card";
                var payment = new Payment(100 + j, type, "Bank", customer.Id);
                _db.Payment.Add(payment);
                
                // batch saves to improve performance during seeding
                if (j % 500 == 0)
                {
                    _db.SaveChanges();
                }
            }
            _db.SaveChanges();
        }
        Console.WriteLine("Seeding completed.");
    }

    // Task 1: N+1
    public void DemonstrateNPlusOne()
    {
        _db.ChangeTracker.Clear();
        _db._queryCount = 0; 
    
        Console.WriteLine("\n--- N+1 Query Problem ---");
        var sw = Stopwatch.StartNew();

        var customers = _db.Customer.ToList();
    
        foreach (var c in customers)
        {
            var payments = _db.Payment.Where(p => p.CustomerId == c.Id).ToList();
        }
        foreach (var c in customers)
        {
            // Access data
            var count = c.Payments.Count;
        }

        sw.Stop();
        Console.WriteLine($"Results: {customers.Count} Customers processed.");
        Console.WriteLine($"Time Taken: {sw.ElapsedMilliseconds} ms");
        Console.WriteLine($"Database Requests: {_db._queryCount}");
    }

    public void SolveNPlusOne()
    {
        _db.ChangeTracker.Clear(); 
        _db._queryCount = 0;
    
        Console.WriteLine("\n--- Eager Loading Solution ---");
        var sw = Stopwatch.StartNew();

        // JOIN operation on Customer and Payments tables 
        var customers = _db.Customer.Include(c => c.Payments).AsSplitQuery().ToList();
        Console.WriteLine(_db._queryCount);
        Console.WriteLine(_db.Customer.ToList().Count);
        foreach (var c in customers)
        {
            // Access data
            var count = c.Payments.Count;
        }

        sw.Stop();
        Console.WriteLine($"Results: {customers.Count} Customers processed.");
        Console.WriteLine($"Time Taken: {sw.ElapsedMilliseconds} ms");
        Console.WriteLine($"Database Requests: {_db._queryCount}");
    }

    // Task 2: Indexing
    public void BenchmarkQueries()
    {
        Console.WriteLine("\n--- Query Benchmarks ---");
        MeasureQuery("Search by Type", () => _db.Payment.Where(p => p.Type == "cash").ToList());
        MeasureQuery("Search by Customer", () => _db.Payment.Where(p => p.CustomerId == 1).ToList());
        MeasureQuery("Range Query (Amount)", () => _db.Payment.Where(p => p.Amount > 500 && p.Amount < 1000).ToList());
        MeasureQuery("Multi-column Search", () => _db.Payment.Where(p => p.CustomerId == 1 && p.Amount > 500).ToList());
    }

    public void AddIndexes()
    {
        Console.WriteLine("\n--- Adding Indexes ---");
        _db.Database.ExecuteSqlRaw("CREATE INDEX IF NOT EXISTS idx_payment_type ON Payment(type);");
        _db.Database.ExecuteSqlRaw("CREATE INDEX IF NOT EXISTS idx_payment_customer ON Payment(id_customer);");
        _db.Database.ExecuteSqlRaw("CREATE INDEX IF NOT EXISTS idx_payment_amount ON Payment(amount);");
        _db.Database.ExecuteSqlRaw("CREATE INDEX IF NOT EXISTS idx_payment_customer_amount ON Payment(id_customer, amount);");
        Console.WriteLine("Indexes added.");
    }
    
    public void DeleteIndexes()
    {
        Console.WriteLine("\n--- Deleting Indexes ---");
    
        _db.Database.ExecuteSqlRaw("DROP INDEX IF EXISTS idx_payment_type;");
        _db.Database.ExecuteSqlRaw("DROP INDEX IF EXISTS idx_payment_customer;");
        _db.Database.ExecuteSqlRaw("DROP INDEX IF EXISTS idx_payment_amount;");
        _db.Database.ExecuteSqlRaw("DROP INDEX IF EXISTS idx_payment_customer_amount;");
    
        Console.WriteLine("Indexes deleted.");
    }

    // Task 5: Bulk Operations
    public void BenchmarkBulkUpdates(long customerId)
    {
        Console.WriteLine("\n--- Bulk Updates Benchmarks ---");
        
        // Approach 1
        var sw = Stopwatch.StartNew();
        var payments1 = _db.Payment.Where(p => p.CustomerId == customerId).ToList();
        foreach (var p in payments1)
        {
            p.Amount = p.Amount * 1.1m;
            _db.Payment.Update(p);
        }
        _db.SaveChanges();
        sw.Stop();
        Console.WriteLine($"Approach 1 (Individual): {sw.ElapsedMilliseconds} ms");

        // Approach 2: ExecuteUpdateAsync
        sw.Restart();
        _db.Payment.Where(p => p.CustomerId == customerId).ExecuteUpdate(s => s.SetProperty(p => p.Amount, p => p.Amount * 1.1m));
        sw.Stop();
        Console.WriteLine($"Approach 2 (Mass Update): {sw.ElapsedMilliseconds} ms");

        // Approach 3: Batch
        sw.Restart();
        var payments3 = _db.Payment.Where(p => p.CustomerId == customerId).ToList();
        for (int i = 0; i < payments3.Count; i++)
        {
            var p = payments3[i];
            p.Amount = p.Amount * 1.1m;
            _db.Payment.Update(p);
            if (i % 50 == 0 && i > 0)
            {
                _db.SaveChanges();
                _db.ChangeTracker.Clear();
            }
        }
        _db.SaveChanges();
        sw.Stop();
        Console.WriteLine($"Approach 3 (Batch): {sw.ElapsedMilliseconds} ms");
    }

    // Task 6: Prepared Statement Caching
    public void BenchmarkPreparedStatements()
    {
        Console.WriteLine("\n--- Prepared Statements Benchmarks ---");
        
        var sw = Stopwatch.StartNew();
        for (long i = 1; i <= 1000; i++)
        {
            var p = _db.Payment.FirstOrDefault(x => x.Id == i);
        }
        sw.Stop();
        Console.WriteLine($"Test A (Dynamic LINQ): {sw.ElapsedMilliseconds} ms");

        sw.Restart();
        var compiledQuery = EF.CompileQuery((AppDbContext db, long id) => db.Payment.FirstOrDefault(x => x.Id == id));
        for (long i = 1; i <= 1000; i++)
        {
            var p = compiledQuery(_db, i);
        }
        sw.Stop();
        Console.WriteLine($"Test B (EF.CompileQuery): {sw.ElapsedMilliseconds} ms");
    }

    private void MeasureQuery(string name, Action queryAction, int runs = 100)
    {
        var sw = Stopwatch.StartNew();
        for (int i = 0; i < runs; i++)
        {
            queryAction();
        }
        sw.Stop();
        Console.WriteLine($"{name}: Avg {sw.ElapsedMilliseconds / (double)runs:F2} ms");
    } 
}