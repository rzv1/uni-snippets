using System.ComponentModel.DataAnnotations.Schema;

namespace L01.Models;

[Table("Payment")]
public class Payment(decimal amount, string type, string bankName, long customerId) : Entity<long>
{
    [Column("amount")]
    public decimal Amount { get; set; } = amount;
    [Column("type")]
    public string Type { get; set; } = type;
    [Column("bank_name")]
    public string? BankName { get; set; } = bankName;

    [ForeignKey("id_customer")]
    [Column("id_customer")]
    public long CustomerId { get; set; } = customerId;

    [NotMapped]
    public long Customer
    {
        get => CustomerId;
        set => CustomerId = value;
    }

    [ForeignKey(nameof(CustomerId))]
    public Customer? CustomerNavigation { get; set; }
}