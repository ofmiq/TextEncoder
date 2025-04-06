#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CipherFactory.h"
#include "FileProcessor.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        if (event->mimeData()->urls().count() == 1) {
            const QUrl url = event->mimeData()->urls().first();
            if (url.isLocalFile()) {
                event->acceptProposedAction();
            } else {
                event->ignore();
            }
        } else {
            event->ignore();
        }
    } else {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();
            if (!filePath.isEmpty()) {
                loadFile(filePath);
                event->acceptProposedAction();
            } else {
                event->ignore();
            }
        } else {
            event->ignore();
        }
    } else {
        event->ignore();
    }
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

void MainWindow::on_selectFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Text File"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (filePath.isEmpty()) {
        statusBar()->showMessage(tr("File selection canceled"), 3000);
        return;
    }

    loadFile(filePath);
}

void MainWindow::on_saveResultButton_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Result As"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (filePath.isEmpty()) {
        statusBar()->showMessage(tr("Save canceled"), 3000);
        return;
    }

    QString contentToSave = ui->outputTextEdit->toPlainText();

    bool success = FileProcessor::saveToFile(filePath, contentToSave);

    if (success) {
        statusBar()->showMessage(tr("File saved successfully: %1").arg(QFileInfo(filePath).fileName()), 3000);
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Cannot save file: %1").arg(filePath));
        statusBar()->showMessage(tr("Error saving file"), 3000);
    }
}

void MainWindow::loadFile(const QString& filePath) {
    if (filePath.isEmpty()) {
        statusBar()->showMessage(tr("Invalid file path provided."), 3000);
        return;
    }

    QFile testFile(filePath);
    if (!testFile.exists()) {
        QMessageBox::critical(this, tr("Error"), tr("File does not exist: %1").arg(filePath));
        statusBar()->showMessage(tr("Error loading file"), 3000);
        return;
    }

    QString fileContent = FileProcessor::loadFromFile(filePath);

    if (fileContent.isEmpty() && testFile.size() > 0) {
        QMessageBox::critical(this, tr("Error"), tr("Could not read content from file: %1").arg(filePath));
        statusBar()->showMessage(tr("Error reading file content"), 3000);
        return;
    }

    ui->inputTextEdit->setPlainText(fileContent);
    statusBar()->showMessage(tr("File loaded successfully: %1").arg(QFileInfo(filePath).fileName()), 3000);
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
