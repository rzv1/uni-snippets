using System.Collections.Generic;
using System.Linq;
using Npgsql;

namespace L01.Models;

public class CustomerRepo(DatabaseManager manager) : ICustomerRepo
{
    private readonly DatabaseManager _manager = manager;

    public IEnumerable<Customer> FindAll()
    {
        var customers = new List<Customer>();
        using var command = new NpgsqlCommand("SELECT * FROM customer", _manager.GetConnection());
        using var reader = command.ExecuteReader();
        while (reader.Read())
            customers.Add(GetCustomer(reader));
        return customers;
    }

    private Customer GetCustomer(NpgsqlDataReader reader)
    {
        return new Customer(reader.GetString(1), reader.GetString(2))
        {
            Id = reader.GetInt64(0),
        };
    }
}