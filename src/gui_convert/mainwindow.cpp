/**
 * @brief
 * @author Sebastian Lau <lauseb644 [at] gmail [dot] com>
 **/
/*
	LibMdHtml++: A library for converting markdown to html
	Copyright (C) 2017-2018 Sebastian Lau <lauseb644@gmail.com>


	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "markdown_document.hpp"

#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QString>
#include <QWidget>


MainWindow::MainWindow( QWidget* parent )
    :   QMainWindow( parent )
    ,   mw_file_dialog( 0 )
    ,   ui( new Ui::MainWindow )
{    
    ui->setupUi(this);

    this->setWindowTitle( "MarkdownToHtml" );
    ui->status->setText("MarkdownToHtml v" + QString(LIBMDHTML_VERSION));
    
    QObject::connect( ui->button_choose_md_file, &QPushButton::clicked
                    , this, &MainWindow::on_choose_MarkdownFile );
    QObject::connect( ui->button_choose_file, &QPushButton::clicked
                    , this, &MainWindow::on_choose_File );
    QObject::connect( ui->button_generate, &QPushButton::clicked
                    , this, &MainWindow::on_generate );
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_choose_MarkdownFile() {
    if ( ui->md_file->text().length() > 0 ) {
        if ( QFile::exists( ui->md_file->text() ) ) {
            mw_file_dialog = new QFileDialog( 0, "Datei zum Konvertieren wählen..."
                                            , ui->md_file->text() );
        }
    } else {
        mw_file_dialog = new QFileDialog( 0, "Datei zum Konvertieren wählen..." );
    }
    
    mw_file_dialog->setFileMode( QFileDialog::AnyFile );
    
    QObject::connect( mw_file_dialog, &QFileDialog::accepted
                    , this, &MainWindow::on_choose_MarkdownFile_Chosen );
    QObject::connect( mw_file_dialog, &QFileDialog::rejected
                    , this, &MainWindow::on_choose_FileDialog_Close );

    mw_file_dialog->show();
}


void MainWindow::on_choose_File() {
    if ( ui->file->text().length() > 0 ) {
        if ( QFile::exists( ui->file->text() ) ) {
            mw_file_dialog = new QFileDialog( 0, "HTML-Ausgabe-Datei wählen..."
                                            , ui->file->text() );
        }
    } else {
        mw_file_dialog = new QFileDialog( 0, "HTML-Ausgabe-Datei wählen..." );
    }
    
    mw_file_dialog->setFileMode( QFileDialog::AnyFile );
    
    QObject::connect( mw_file_dialog, &QFileDialog::accepted
                    , this, &MainWindow::on_choose_File_Chosen );
    QObject::connect( mw_file_dialog, &QFileDialog::rejected
                    , this, &MainWindow::on_choose_FileDialog_Close );

    mw_file_dialog->show();
}


void MainWindow::on_generate() {
    if ( ui->md_file->text().length() > 0
      && ui->file->text().length() > 0
    ) {
        if ( QFile::exists( ui->md_file->text() ) ) {
            ui->status->setText("[MarkdownToHtml/Markdown] - Parse Markdown-Datei...");
            mdhtml::MarkdownDocument* markdown = new mdhtml::MarkdownDocument();
            try {
                if ( ! markdown->thisFromFile( ui->md_file->text().toStdString() ) ) {
                    ui->status->setText("Konnte Markdown nicht parsen.");
                    return;
                }
            } catch ( std::exception& e ) {
                ui->status->setText("Konnte Markdown nicht parsen: " + QString(e.what()));
            }
            
            ui->status->setText("[MarkdownToHtml/HTML] - Generiere HTML...");
            try {
                if ( ! markdown->html_toFile( ui->file->text().toStdString() ) ) {
                    ui->status->setText("Konnte HTML nicht generieren.");
                } else {
                    ui->status->setText("Generiert.");
                }
            } catch ( std::exception& e ) {
                ui->status->setText("Konnte HTML nicht schreiben: " + QString(e.what()));
            }
        } else {
            ui->status->setText("Verzeichnis existiert nicht.");
        }
    } else {
        ui->status->setText("Alle Felder müssen ausgefüllt sein.");
    }
}


void MainWindow::on_choose_FileDialog_Close() {
    if ( mw_file_dialog != 0 ) {
        mw_file_dialog->close();
        mw_file_dialog->disconnect();
        delete mw_file_dialog;
    }
}


void MainWindow::on_choose_MarkdownFile_Chosen() {
    ui->md_file->setText( mw_file_dialog->selectedFiles()[0] );
    this->on_choose_FileDialog_Close();
}


void MainWindow::on_choose_File_Chosen() {
    ui->file->setText( mw_file_dialog->selectedFiles()[0] );
    this->on_choose_FileDialog_Close();
}
