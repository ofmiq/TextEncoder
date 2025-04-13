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

protected:
    /**
     * @brief Handles drag enter events to accept potential file drops.
     * @param event The drag enter event details.
     */
    void dragEnterEvent(QDragEnterEvent *event) override;

    /**
     * @brief Handles drop events to process dropped files.
     * @param event The drop event details.
     */
    void dropEvent(QDropEvent *event) override;

private slots:
    /**
     * @brief Slot triggered when the encrypt button is clicked.
     */
    void on_encryptButton_clicked();

    /**
     * @brief Slot triggered when the decrypt button is clicked.
     */
    void on_decryptButton_clicked();

    /**
     * @brief Slot triggered when the generate key button is clicked.
     */
    void on_generateKeyButton_clicked();

    /**
     * @brief Slot triggered when the select file button is clicked.
     */
    void on_selectFileButton_clicked();

    /**
     * @brief Slot triggered when the save result button is clicked.
     */
    void on_saveResultButton_clicked();

private:
    /**
     * @brief Updates the encryption service based on the selected cipher type and key from UI.
     */
    void updateEncryptionService();

    Ui::MainWindow *ui;
    std::unique_ptr<EncryptionService> encryptionService;

    /**
     * @brief Generates a random string of a given length.
     * @param length The length of the string to generate.
     * @param generator A function that generates a single random character.
     * @return The generated random string.
     */
    QString generateRandomString(int length, std::function<QChar()> generator);

    /**
     * @brief Generates a random uppercase or lowercase letter.
     * @return A random uppercase or lowercase letter.
     */
    QChar generateRandomUpperOrLower();

    /**
     * @brief Generates a random printable ASCII character.
     * @return A random printable ASCII character.
     */
    QChar generateRandomPrintableAscii();

    /**
     * @brief Loads content from the specified file path into the input text area.
     * @param filePath The absolute path to the file to load.
     */
    void loadFile(const QString& filePath);
};

#endif // MAINWINDOW_H
