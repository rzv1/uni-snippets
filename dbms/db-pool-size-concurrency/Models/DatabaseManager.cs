using System;

namespace L01.Models;
using System.Data;
using Npgsql;

public class DatabaseManager(string connectionString)
{
    private readonly string _connectionString = connectionString;
    private readonly NpgsqlConnection? _instance = null;

    private NpgsqlConnection GetNewConnection()
    {
        try
        {
            var conn = new NpgsqlConnection(_connectionString);
            conn.Open();
            return conn;
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
    }

    public NpgsqlConnection GetConnection()
    {
        try
        {
            if (_instance == null || _instance.State == ConnectionState.Closed)
                return GetNewConnection();
            return _instance!;
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
    }

    public void CloseConnection()
    {
        _instance!.Close();
    }
}