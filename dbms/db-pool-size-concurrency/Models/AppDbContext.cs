using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Diagnostics;
using Microsoft.Extensions.Logging;

namespace L01.Models;

public class AppDbContext(string connectionString) : DbContext
{
    public int _queryCount;
    public DbSet<Customer> Customer { get; set; }
    public DbSet<Payment> Payment { get; set; }
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.LogTo(message =>
            {
                _queryCount++;
                Console.WriteLine(message);
            },
            new[] { DbLoggerCategory.Database.Command.Name },
            LogLevel.Information,
            DbContextLoggerOptions.None);
        optionsBuilder.UseSqlite(connectionString);
    }
}