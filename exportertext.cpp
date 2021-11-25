#include "exportertext.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QVariant>

int ExportPDFObject::export2PDF()
{
    if(fieldList.size() <= 0)
    {
        qDebug() << "ExportPDFObject::export2PDF failed: No fields defined.";
        return -1;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "pdfexport");
    if(!db.isValid())
    {
        qDebug() << "ExportPDFObject::export2PDF failed: QODBC not supported.";
        return -2;
    }
    // set the dsn string
    QString dsn = QString("DRIVER={Adobe Acrobat Reader Driver (*.pdf)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").
                  arg(PdfFilePath).arg(PdfFilePath);
    db.setDatabaseName(dsn);
    if(!db.open())
    {
        qDebug() << "ExportPDFObject::export2PDF failed: Create pdf file failed by DRIVER={Adobe Acrobat Reader Driver (*.pdf)}.";
        //QSqlDatabase::removeDatabase("pdfexport");
        return -3;
    }

    QSqlQuery query(db);

    //drop the table if it's already exists
    QString s, sSql = QString("DROP TABLE [%1] (").arg(sheetName);
    query.exec(sSql);

    //create the table (sheet in pdf file)
    sSql = QString("CREATE TABLE [%1] (").arg(sheetName);
    for (int i = 0; i < fieldList.size(); i++)
    {
        s = QString("[%1] %2").arg(fieldList.at(i)->sFieldName).arg(fieldList.at(i)->sFieldType);
        sSql += s;
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }

    sSql += ")";
    query.prepare(sSql);

    if(!query.exec())
    {
        qDebug() << "ExportPDFObject::export2PDF failed: Create PDF sheet failed.";
        //db.close();
        //QSqlDatabase::removeDatabase("excelexport");
        return -4;
    }



    //add all rows
    sSql = QString("INSERT INTO [%1] (").arg(sheetName);
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += fieldList.at(i)->sFieldName;
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }
    sSql += ") VALUES (";
    for (int i = 0; i < fieldList.size(); i++)
    {
        sSql += QString(":data%1").arg(i);
        if(i < fieldList.size() - 1)
            sSql += " , ";
    }
    sSql += ")";

    qDebug() << sSql;

    int r, iRet = 0;
    for(r = 0 ; r < tableView->model()->rowCount() ; r++)
    {
        query.prepare(sSql);
        for (int c = 0; c < fieldList.size(); c++)
        {
            query.bindValue(QString(":data%1").arg(c), tableView->model()->data(tableView->model()->index(r, fieldList.at(c)->iCol)));
        }

        if(query.exec())
            iRet++;

        if(r % 10 == 0)
            emit exportedRowCount(r);
    }

    emit exportedRowCount(r);

    return iRet;
}
/*mainwindow.cpp:   QString fileName = QFileDialog::getSaveFileName(this, tr("PDF file"), qApp->applicationDirPath (),
                                                    tr("PDF Files (*.pdf)"));
    if (fileName.isEmpty())
        return;

    ExportPDFObject obj(fileName, "mydata", ui->tab_fournisseur);

    //colums to export
    obj.addField(0, "ID_FOURNISSEUR", "char(20)");
    obj.addField(1, "NUM", "char(20)");
    obj.addField(2, "CONTRAT", "char(20)");
    obj.addField(3, "ADRESSE", "char(20)");
    obj.addField(4, "NOM", "char(20)");
    obj.addField(5, "PRENOM", "char(20)");
    obj.addField(6, "CIN", "char(20)");


    int retVal = obj.export2PDF();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }*/
