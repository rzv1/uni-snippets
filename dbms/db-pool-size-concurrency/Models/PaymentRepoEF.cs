using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Caching.Memory;

namespace L01.Models;

public class PaymentRepoEF(AppDbContext db, IMemoryCache cache) : IPaymentRepo
{
    private MemoryCacheEntryOptions _cacheOptions = new MemoryCacheEntryOptions()
        .SetAbsoluteExpiration(TimeSpan.FromMinutes(10))
        .SetSlidingExpiration(TimeSpan.FromMinutes(2))
        .SetPriority(CacheItemPriority.High);
    
    public IEnumerable<Payment> FindAll(long customerId)
    {
        var key = "payments_" + customerId;
        var cs = db.Payment.FromSqlRaw("SELECT * FROM payment where id_customer = {0}",  customerId).ToList();
        if (!cache.TryGetValue(key, out IEnumerable<Payment>? payments))
        {
            payments = db.Payment.AsNoTracking().Where(p => p.Customer == customerId).ToList();
            cache.Set(key, payments, _cacheOptions);
            Console.WriteLine("Cache miss: {0}", key);
        }
        else
        {
            Console.WriteLine("Cache hit");
        }
        return payments!;
    }

    public IEnumerable<Payment> FindAllByType(string type, long id)
    {
        var key = "payments_by_type_" +  id +  "_" + type;
        var cs = db.Payment.FromSqlRaw("SELECT * FROM payment where id_customer = {0} and type = {1}",  id, type).ToList();
        if (!cache.TryGetValue(key, out IEnumerable<Payment>? payments))
        {
            payments = db.Payment.AsNoTracking().Where(p => p.Type == type && p.Id == id).ToList();
            cache.Set(key, payments, _cacheOptions);
            Console.WriteLine("Cache miss: {0}", key);
        }
        else
        {
            Console.WriteLine("Cache hit");
        }
        return payments!;
    }

    public void Save(Payment payment)
    {
        var key = "payments_" + payment.Customer;
        cache.Remove(key);
        db.Payment.Add(payment);
        db.SaveChanges();
    }

    public void Update(Payment payment)
    {
        var key = "payments_" + payment.Customer;
        cache.Remove(key);
        db.Payment.Update(payment);
        db.SaveChanges();
    }

    public void Delete(long id)
    {
        var payment = db.Payment.Find(id)!;
        var key = "payments_" + payment.Customer;
        cache.Remove(key);
        db.Payment.Remove(payment);
        db.SaveChanges();
    }
}