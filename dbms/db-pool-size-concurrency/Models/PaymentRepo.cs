using System;
using System.Collections.Generic;
using System.Diagnostics;
using Npgsql;

namespace L01.Models;

public class PaymentRepo(DatabaseManager manager) : IPaymentRepo
{
    private readonly DatabaseManager _manager = manager;

    public IEnumerable<Payment> FindAll(long customerId)
    {
        var payments = new List<Payment>();
        var sw = Stopwatch.StartNew();
        using var command = new NpgsqlCommand("SELECT * FROM payment where id_customer = @id", _manager.GetConnection());
        command.Parameters.AddWithValue("id", customerId);

        using var reader = command.ExecuteReader();
        while (reader.Read())
            payments.Add(GetPayment(reader));
        sw.Stop();
        Console.WriteLine($"Total time: {sw.Elapsed.TotalMilliseconds:.4f} ms");
        Console.WriteLine("SQL: SELECT * FROM payment where id_customer = @id");
        return payments;
    }

    public IEnumerable<Payment> FindAllByType(string type, long id)
    {
        var payments = new List<Payment>();
        var sw = Stopwatch.StartNew();
        using var command = new NpgsqlCommand("SELECT * FROM payment where type = @type and id_customer = @id", _manager.GetConnection());
        command.Parameters.AddWithValue("type", type);
        command.Parameters.AddWithValue("id", id);

        using var reader = command.ExecuteReader();
        while(reader.Read())
            payments.Add(GetPayment(reader));
        sw.Stop();
        Console.WriteLine($"Total time: {sw.Elapsed.TotalMilliseconds:.4f} ms");
        Console.WriteLine("SQL: SELECT * FROM payment where type = @type and id_customer = @id");
        return payments;
    }

    private Payment GetPayment(NpgsqlDataReader reader)
    {
        var id = reader.GetInt64(0);
        var payment =new Payment(reader.GetInt32(1), reader.GetString(2), reader.GetString(3), reader.GetInt64(4))
        {
            Id = reader.GetInt64(0)
        }; 
        return payment;
    }

    public void Save(Payment payment)
    {
        // cazul in care numele bancii nu este disponibil (se pune valoarea default in baza de date)
        if (string.IsNullOrEmpty(payment.BankName))
        {
            using var command =
                new NpgsqlCommand(
                    "INSERT INTO payment (amount, type, id_customer) VALUES(@amount, @type, @id_customer)",
                    _manager.GetConnection());
            command.Parameters.AddWithValue("amount", payment.Amount);
            command.Parameters.AddWithValue("type", payment.Type);
            command.Parameters.AddWithValue("id_customer", payment.Customer);
            command.ExecuteNonQuery();
        }
        else // cazul in care numele bancii este disponibil
        {
            using var command1 =
                new NpgsqlCommand(
                    "INSERT INTO payment (amount, type, bank_name, id_customer) VALUES(@amount, @type, @bank_name, @id_customer)",
                    _manager.GetConnection());
            command1.Parameters.AddWithValue("amount", payment.Amount);
            command1.Parameters.AddWithValue("type", payment.Type);
            command1.Parameters.AddWithValue("bank_name", payment.BankName);
            command1.Parameters.AddWithValue("id_customer", payment.Customer);
            command1.ExecuteNonQuery();
        }
    }

    public void Update(Payment payment)
    {
        var sw = Stopwatch.StartNew();
        using var command =
            new NpgsqlCommand(
                "UPDATE payment SET amount = @amount, type = @type, bank_name = @bank_name where id = @id",
                _manager.GetConnection());
        command.Parameters.AddWithValue("amount", payment.Amount);
        command.Parameters.AddWithValue("type", payment.Type);
        //Desi bank name poate fi null la crearea obiectului, la update are obligatoriu o valoare si specificam asta
        //cu operatorul !
        command.Parameters.AddWithValue("bank_name", payment.BankName!);
        command.Parameters.AddWithValue("id", payment.Id);
        command.ExecuteNonQuery();
        sw.Stop();
        Console.WriteLine("Total time: " + sw.Elapsed.TotalMilliseconds);
        Console.WriteLine("SQL: UPDATE payment SET amount = @amount, type = @type, bank_name = @bank_name where id = @id");
    }

    public void Delete(long paymentId)
    {
        var sw = Stopwatch.StartNew();
        using var command = new NpgsqlCommand("DELETE FROM payment where id = @id", _manager.GetConnection());
        command.Parameters.AddWithValue("id", paymentId);
        command.ExecuteNonQuery();
        sw.Stop();
        Console.WriteLine("Total time: " + sw.Elapsed.TotalMilliseconds);
        Console.WriteLine("SQL: DELETE FROM payment where id = @id");
    }
}