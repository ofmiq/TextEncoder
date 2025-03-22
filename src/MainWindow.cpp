#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CipherFactory.h"
#include <QMessageBox>
#include <QRandomGenerator>

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
    } else if (type == "Playfair") {
        cipher = CipherFactory::createCipher(CipherFactory::Playfair);
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

    QString plainText = encryptionService->decrypt(cipherText, key);
    ui->outputTextEdit->setPlainText(plainText);
}

void MainWindow::on_generateKeyButton_clicked() {
    QString cipherType = ui->cipherComboBox->currentText();
    QString generatedKey;

    if (cipherType == "Caesar") {
        int shift = QRandomGenerator::global()->bounded(1, 26);
        generatedKey = QString::number(shift);
    } else if (cipherType == "Vigenere") {
        generatedKey = generateRandomString(6, [this](){ return generateRandomUpperOrLower(); });
    } else if (cipherType == "XOR") {
        generatedKey = generateRandomString(8, [this](){ return generateRandomPrintableAscii(); });
    } else if (cipherType == "Atbash") {
        generatedKey = ""; // Atbash does not require a key
    } else if (cipherType == "Playfair") {
        generatedKey = generateRandomString(6, [this](){ return generateRandomUpperOrLower(); });
    } else {
        generatedKey = "";
    }

    ui->keyLineEdit->setText(generatedKey);
}

QString MainWindow::generateRandomString(int length, std::function<QChar()> generator) {
    QString result = "";
    for (int i = 0; i < length; ++i) {
        result.append(generator());
    }
    return result;
}

QChar MainWindow::generateRandomUpperOrLower() {
    int r = QRandomGenerator::global()->bounded(0, 52);
    if (r < 26) {
        return QChar(QChar('A').unicode() + r);
    } else {
        return QChar(QChar('a').unicode() + (r - 26));
    }
}

QChar MainWindow::generateRandomPrintableAscii() {
    return QChar(QRandomGenerator::global()->bounded(33, 127));
}
