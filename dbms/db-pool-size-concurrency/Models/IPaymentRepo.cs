using System.Collections.Generic;

namespace L01.Models;

public interface IPaymentRepo
{
    IEnumerable<Payment> FindAll(long customerId);
    IEnumerable<Payment> FindAllByType(string type, long id);
    void Save(Payment payment);
    void Update(Payment payment);
    void Delete(long id);
}