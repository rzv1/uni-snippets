#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QPainter>
#include <map>

#include "Service.h"
#include "Tests.h"
#include "AbstractModel.h"

constexpr int ID = Qt::UserRole;
constexpr int TITLE = Qt::UserRole + 1;
constexpr int AUTHOR = Qt::UserRole + 2;
constexpr int GENRE = Qt::UserRole + 3;
constexpr int YEAR = Qt::UserRole + 4;


class CosCRUDGUI : public QWidget, public Observer {
private:
    Service& service;
    //QTableWidget table;
    CarteTableModel* model = new CarteTableModel(this);
    QTableView* table = new QTableView;
    QPushButton btnAddCos{ "Add" }, btnClearCos{ "Clear" }, btnRandomCos{ "Random" }, btnExportCos{ "Export" };
    QHBoxLayout mainLayout;
    QVBoxLayout vLeft, vRight;

    void initLayout() {
        vLeft.addWidget(table);

        vRight.addWidget(&btnAddCos);
        vRight.addWidget(&btnRandomCos);
        vRight.addWidget(&btnClearCos);
        vRight.addWidget(&btnExportCos);
        vRight.addStretch();

        mainLayout.addLayout(&vLeft);
        mainLayout.addLayout(&vRight);
        setLayout(&mainLayout);
    }
    void initConnections() {
        connect(&btnAddCos, &QPushButton::clicked, this, [this] {
            const QString text = QInputDialog::getText(this, "Adauga in cos", "Titlu");
            string t = text.toStdString();
            service.add_cart(t);
            reloadCart();
            });
        connect(&btnRandomCos, &QPushButton::clicked, this, [this] {
            const int number = QInputDialog::getInt(this, "Genreaza cos", "Numar generari", 0, 1, 100);
            service.generate_cart(number);
            reloadCart();
            });
        connect(&btnClearCos, &QPushButton::clicked, this, [this] {
            service.clear_cart();
            reloadCart();
            });
        connect(&btnExportCos, &QPushButton::clicked, this, [this] {
            const QString text = QInputDialog::getText(this, "Exporta cos", "Nume fisier");
            string t = text.toStdString();
            service.export_cart(t);
            });
    }
    void reloadCart() { //populateTable(service.cart_get_all());
        model->setCarti(service.cart_get_all());
    }
    //void populateTable(const std::vector<Carte>& books) {
    //    table.clear();
    //    table.setRowCount((int)books.size());
    //    table.setColumnCount(5);
    //    table.setHorizontalHeaderLabels({ "ID", "Title", "Author", "Genre", "Year" });
    //    int row = 0;
    //    for (const Carte& book : books) {
    //        table.setItem(row, 0, new QTableWidgetItem(QString::number(book.get_id())));
    //        table.setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.get_title())));
    //        table.setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.get_author())));
    //        table.setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.get_genre())));
    //        table.setItem(row, 4, new QTableWidgetItem(QString::number(book.get_year())));
    //        row++;
    //    }
    //}
public:
    CosCRUDGUI(Service& srv, QWidget* parent = nullptr) : QWidget(parent), service{ srv } {
        initLayout();
        initConnections();
        table->setModel(model);
        service.get_cart().addObserver(this);
        update();
    }
    void update() override {
        reloadCart();
    }
    ~CosCRUDGUI() {
        service.get_cart().removeObserver(this);
    }
};

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    Service& service;
public:
    CosReadOnlyGUI(Service& srv, QWidget* parent = nullptr) : QWidget(parent), service{ srv } {
        service.get_cart().addObserver(this);
        update();
    }
    void update() override {
        repaint();
    }
    void paintEvent(QPaintEvent* ev) override {
        (void)ev;
        QPainter p{ this };
        auto cart = service.cart_get_all();
        std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> distX(0, width() - 50), distY(0, height() - 50);
        for (size_t i = 0; i < cart.size(); ++i) {
            int x = distX(rng), y = distY(rng);
            p.drawEllipse(x, y, 30, 30);
        }
    }
    ~CosReadOnlyGUI() {
        service.get_cart().removeObserver(this);
    }
};

class ShopGUI : public QWidget {
public:
    explicit ShopGUI(Service& srv, QWidget* parent = nullptr)
        : QWidget(parent), service{ srv }
    {
        initWidgets();
        initLayouts();
        initConnections();
        rebuildDynamicButtons();
        setWindowTitle("Book shop GUI");
        resize(780, 420);
        reloadList();
    }

private:
    Service& service;

    QListWidget  listBox;
    QTableWidget table, tableList;

    QLabel lblId{ "Id" }, lblTitle{ "Title" }, lblAuthor{ "Author" }, lblGenre{ "Genre" }, lblYear{ "Year" };
    QLineEdit editId, editTitle, editAuthor, editGenre, editYear;

    QPushButton  btnAdd{ "Add" }, btnUpdate{ "Update" },
        btnRemove{ "Remove" }, btnSortTitle{ "SortByTitle" }, btnSortYearGenre{ "SortByYearGenre" },
        btnFilterTitle{ "FilterByTitle" }, btnFilterYear{ "FilterByYear" },
        btnUndo{ "Undo" }, btnShowTableCos{ "Cos" }, btnShowCos{ "Cos vizual" };

    QVBoxLayout dynButtonsLayout;

    QGridLayout gridForm;
    QHBoxLayout hAddUpd, hSort, hFilter, hUndo;
    QVBoxLayout vRight, vLeft, vCos, DynButtons;
    QHBoxLayout mainLayout;

    void initWidgets()
    {
        listBox.setMinimumSize(320, 240);
		tableList.setMinimumSize(420, 240);
        table.setMinimumWidth(500);
    }

    void initLayouts()
    {
        gridForm.addWidget(&lblId, 0, 0); gridForm.addWidget(&editId, 0, 1);
        gridForm.addWidget(&lblTitle, 1, 0); gridForm.addWidget(&editTitle, 1, 1);
        gridForm.addWidget(&lblAuthor, 2, 0); gridForm.addWidget(&editAuthor, 2, 1);
        gridForm.addWidget(&lblGenre, 3, 0); gridForm.addWidget(&editGenre, 3, 1);
        gridForm.addWidget(&lblYear, 4, 0); gridForm.addWidget(&editYear, 4, 1);

        hAddUpd.addWidget(&btnAdd);
        hAddUpd.addWidget(&btnUpdate);

        hFilter.addWidget(&btnFilterTitle);
        hFilter.addWidget(&btnFilterYear);

        hUndo.addWidget(&btnUndo);

        vRight.addLayout(&gridForm);
        vRight.addLayout(&hAddUpd);
        vRight.addLayout(&hFilter);
        vRight.addLayout(&hUndo);
        vRight.addStretch();

        DynButtons.addLayout(&dynButtonsLayout);
        DynButtons.addStretch();

        hSort.addWidget(&btnRemove);
        hSort.addWidget(&btnSortTitle);
        hSort.addWidget(&btnSortYearGenre);

        vLeft.addWidget(&listBox);
        vLeft.addLayout(&hSort);
		vLeft.addWidget(&tableList);
        vLeft.addStretch();

        vCos.addWidget(&btnShowTableCos);
        vCos.addWidget(&btnShowCos);
        vCos.addStretch();

        mainLayout.addLayout(&vLeft);
        mainLayout.addLayout(&vRight);
        mainLayout.addLayout(&DynButtons);
        mainLayout.addSpacing(30);
        mainLayout.addLayout(&vCos);
        setLayout(&mainLayout);
    }

    void initConnections()
    {
        connect(&btnAdd, &QPushButton::clicked, this, [this] {
            try {
                service.add(editTitle.text().toStdString(),
                    editAuthor.text().toStdString(),
                    editGenre.text().toStdString(),
                    editYear.text().toInt());
                reloadList();
                rebuildDynamicButtons();
            }
            catch (const std::exception& ex) {
                QMessageBox::warning(this, "Error", ex.what());
            }
            });

        connect(&btnUpdate, &QPushButton::clicked, this, [this] {
            try {
                const int id = editId.text().toInt();
                if (!editTitle.text().isEmpty())  service.update_title(id, editTitle.text().toStdString());
                if (!editAuthor.text().isEmpty()) service.update_author(id, editAuthor.text().toStdString());
                if (!editGenre.text().isEmpty())  service.update_genre(id, editGenre.text().toStdString());
                if (!editYear.text().isEmpty())   service.update_year(id, editYear.text().toInt());
                reloadList();
                rebuildDynamicButtons();
            }
            catch (const std::exception& ex) {
                QMessageBox::warning(this, "Error", ex.what());
            }
            });

        connect(&btnRemove, &QPushButton::clicked, this, [this] {
            if (auto* it = listBox.currentItem()) {
                try {
                    service.remove(it->data(ID).toInt());
                    reloadList();
                    rebuildDynamicButtons();
                }
                catch (const std::exception& ex) {
                    QMessageBox::warning(this, "Error", ex.what());
                }
            }
            });

        connect(&btnSortTitle, &QPushButton::clicked, this, [this] {
            populate(service.sort_title());
            });
        connect(&btnSortYearGenre, &QPushButton::clicked, this, [this] {
            populate(service.sort_year_and_genre());
            });

        connect(&btnFilterTitle, &QPushButton::clicked, this, [this] {
            populate(service.filter_title(editTitle.text().toStdString()));
            });
        connect(&btnFilterYear, &QPushButton::clicked, this, [this] {
            populate(service.filter_year(editYear.text().toInt()));
            });

        connect(&btnUndo, &QPushButton::clicked, this, [this] {
            try {
                service.undo();
                reloadList();
                rebuildDynamicButtons();
            }
            catch (const std::runtime_error& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
            });

        connect(&listBox, &QListWidget::itemSelectionChanged, this, [this] {
            if (auto* it = listBox.currentItem()) {
                editId.setText(it->data(ID).toString());
                editTitle.setText(it->data(TITLE).toString());
                editAuthor.setText(it->data(AUTHOR).toString());
                editGenre.setText(it->data(GENRE).toString());
                editYear.setText(it->data(YEAR).toString());
            }
            });

        connect(&btnShowTableCos, &QPushButton::clicked, this, [this] {
            auto* wid = new CosCRUDGUI(service);
            wid->show();
            });
        connect(&btnShowCos, &QPushButton::clicked, this, [this] {
            auto* wid = new CosReadOnlyGUI(service);
            wid->show();
            });
    }

    void rebuildDynamicButtons()
    {
        while (auto item = dynButtonsLayout.takeAt(0)) {
            auto* w = item->widget();
            if (w)
                delete w;
            delete item;
        }
        const auto raport = service.get_map();
        for (const auto& [type, dto] : raport) {
            auto* btn = new QPushButton(QString::fromStdString(type));
            dynButtonsLayout.addWidget(btn);
            connect(btn, &QPushButton::clicked, this, [this, type] {
                try {
                    int f = service.get_map().at(type).get_freq();
                    QMessageBox::information(this, "Frecventa",
                        QString::fromStdString(type + " apare de " + std::to_string(f) + " ori"));
                }
                catch (const std::exception& ex) {
                    QMessageBox::warning(this, "Error", ex.what());
                }
                });
        }
        dynButtonsLayout.addStretch();
    }

    void reloadList() { populate(service.sort_title()); populateTableList(service.sort_title()); }
    void populate(const std::vector<Carte>& books)
    {
        listBox.clear();
        for (const auto& b : books) {
            auto* item = new QListWidgetItem(QString::fromStdString(b.get_title()));
            item->setData(ID, b.get_id());
            item->setData(TITLE, QString::fromStdString(b.get_title()));
            item->setData(AUTHOR, QString::fromStdString(b.get_author()));
            item->setData(GENRE, QString::fromStdString(b.get_genre()));
            item->setData(YEAR, b.get_year());
            listBox.addItem(item);
        }
    }

    void populateTableList(const std::vector<Carte>& books) {
        tableList.clear();
        tableList.setRowCount((int)books.size());
        tableList.setColumnCount(5);
        tableList.setHorizontalHeaderLabels({ "ID", "Title", "Author", "Genre", "Year" });
        int row = 0;
        for (const Carte& book : books) {
            tableList.setItem(row, 0, new QTableWidgetItem(QString::number(book.get_id())));
            tableList.setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.get_title())));
            tableList.setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.get_author())));
            tableList.setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.get_genre())));
            tableList.setItem(row, 4, new QTableWidgetItem(QString::number(book.get_year())));
            row++;
        }
    }

    void reloadCart() { populateTable(service.cart_get_all()); }
    void populateTable(const std::vector<Carte>& books) {
        table.clear();
        table.setRowCount((int)books.size());
        table.setColumnCount(5);
        table.setHorizontalHeaderLabels({ "ID", "Title", "Author", "Genre", "Year" });
        int row = 0;
        for (const Carte& book : books) {
            table.setItem(row, 0, new QTableWidgetItem(QString::number(book.get_id())));
            table.setItem(row, 1, new QTableWidgetItem(QString::fromStdString(book.get_title())));
            table.setItem(row, 2, new QTableWidgetItem(QString::fromStdString(book.get_author())));
            table.setItem(row, 3, new QTableWidgetItem(QString::fromStdString(book.get_genre())));
            table.setItem(row, 4, new QTableWidgetItem(QString::number(book.get_year())));
            row++;
        }
    }
};