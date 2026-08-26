using System.Collections.Generic;

namespace L01.Models;

public interface ICustomerRepo
{
    IEnumerable<Customer> FindAll();
}