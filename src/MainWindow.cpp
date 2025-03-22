#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CipherFactory.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateEncryptionService() {
    QString type = ui->cipherComboBox->currentText();
    std::unique_ptr<IEncryptionAlgorithm> cipher;

    if (type == "Caesar") {
        cipher = CipherFactory::createCipher(CipherFactory::Caesar);
    } else if (type == "Vigenere") {
        cipher = CipherFactory::createCipher(CipherFactory::Vigenere);
    } else if (type == "XOR") {
        cipher = CipherFactory::createCipher(CipherFactory::XOR);
    } else if (type == "Atbash") {
        cipher = CipherFactory::createCipher(CipherFactory::Atbash);
    }

    encryptionService = std::make_unique<EncryptionService>(std::move(cipher));
}

void MainWindow::on_encryptButton_clicked() {
    updateEncryptionService();
    QString plainText = ui->inputTextEdit->toPlainText();
    QString key = ui->keyLineEdit->text();

    QString cipherText = encryptionService->encrypt(plainText, key);
    ui->outputTextEdit->setPlainText(cipherText);
}

void MainWindow::on_decryptButton_clicked() {
    updateEncryptionService();
    QString cipherText = ui->inputTextEdit->toPlainText();
    QString key = ui->keyLineEdit->text();

    if (ui->cipherComboBox->currentText() == "Caesar" && key.trimmed().isEmpty()) {
        key = "3";
    }

    QString plainText = encryptionService->decrypt(cipherText, key);
    ui->outputTextEdit->setPlainText(plainText);
}
