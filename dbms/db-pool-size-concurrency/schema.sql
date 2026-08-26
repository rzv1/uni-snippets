--CREATE DATABASE gym;

DROP TABLE IF EXISTS Customer ;

CREATE TABLE Customer (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    phone_number TEXT,
    registeredAt TIMESTAMP WITHOUT TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO Customer (name, phone_number) VALUES ('Bob', '+314 242 4123'),
                                                   ('Michael', '+314 512 1324'),
                                                   ('Alice', '+12 4123 5123');

DROP TABLE IF EXISTS Payment ;

CREATE TABLE Payment (
    id INTEGER PRIMARY KEY,
    amount DECIMAL(10, 2) NOT NULL ,
    type TEXT NOT NULL ,
    bank_name TEXT DEFAULT 'not the case',
    id_customer INT,
    CONSTRAINT fk_customer FOREIGN KEY (id_customer) REFERENCES Customer (id) ON DELETE  CASCADE 
);

INSERT INTO Payment (amount, type, id_customer) VALUES ('195', 'cash', 1),
                                                       ('45', 'cash', 2),
                                                       ('120', 'cash', 3);

INSERT INTO Payment (amount, type, bank_name, id_customer) VALUES ('450', 'bank transfer', 'ING', 1),
                                                                  ('750', 'card', 'BRD', 3),
                                                                  ('2150', 'card', 'BCR', 2);

DROP TABLE IF EXISTS Membership ;

CREATE TABLE Membership (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    length INT NOT NULL,
    price INT NOT NULL
);

INSERT INTO Membership (name, length, price) VALUES ('Monthly Pro', 31, 195),
                                                    ('Monthly Basic', 31, 120),
                                                    ('Trial', 7, 45),
                                                    ('Annual', 365, 2150),
                                                    ('Trimestrial Pro', 100, 750),
                                                    ('Trimestrial Basic', 100, 450);

DROP TABLE IF EXISTS Customer_Membership ;

CREATE TABLE Customer_Membership (
    id_customer INT,
    id_membership INT,
    CONSTRAINT pk PRIMARY KEY (id_customer, id_membership),
    CONSTRAINT fk_customer FOREIGN KEY (id_customer) REFERENCES Customer (id) ON DELETE CASCADE,
    CONSTRAINT fk_membership FOREIGN KEY (id_membership) REFERENCES Membership (id) ON DELETE CASCADE 
);

INSERT INTO Customer_Membership (id_customer, id_membership)  VALUES (1, 1), (1, 6),
                                                                     (2, 3), (3, 2),
                                                                     (3, 5), (2, 4);