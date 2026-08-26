using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace L01.Models;

[Table("Customer")]
public class Customer(string name, string phone) : Entity<long>
{
    [Column("name")]
    public string Name { get; set; } = name;
    [Column("phone_number")]
    public string Phone { get; set; } = phone;
    [Column("registeredAt")]
    public DateTime RegisteredAt { get; set; } = DateTime.Now;

    public ICollection<Payment> Payments { get; set; } = new List<Payment>();
}