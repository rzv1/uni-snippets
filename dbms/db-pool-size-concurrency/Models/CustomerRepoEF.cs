using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Caching.Memory;

namespace L01.Models;

public class CustomerRepoEF(AppDbContext db, IMemoryCache cache) : ICustomerRepo
{
    public IEnumerable<Customer> FindAll()
    {
        const string key = "Customer";
        var cd = db.Customer.FromSqlRaw("SELECT * FROM Customer;").ToList();
        
        if (!cache.TryGetValue(key, out IEnumerable<Customer>? customers))
        {
            customers = db.Customer.ToList();
            
            var cacheOptions = new MemoryCacheEntryOptions()
                .SetAbsoluteExpiration(TimeSpan.FromMinutes(10))
                .SetSlidingExpiration(TimeSpan.FromMinutes(2))
                .SetPriority(CacheItemPriority.High);
            
            cache.Set(key, customers, cacheOptions);
            Console.WriteLine("- DB Read (miss) -");
        }
        else
        {
            Console.WriteLine("- Cache Read (hit) -");
        }
        return customers!;
    }
}