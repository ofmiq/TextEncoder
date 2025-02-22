#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "EncryptionService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Main window for the CryptoScribe application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructor for MainWindow.
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot triggered when the encrypt button is clicked.
     */
    void on_encryptButton_clicked();

    /**
     * @brief Slot triggered when the decrypt button is clicked.
     */
    void on_decryptButton_clicked();

private:
    /**
     * @brief Updates the encryption service based on the selected cipher type and key from UI.
     */
    void updateEncryptionService();

    Ui::MainWindow *ui;
    std::unique_ptr<EncryptionService> encryptionService;
};

#endif // MAINWINDOW_H
