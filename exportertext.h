#ifndef EXPORTERTEXT_H
#define EXPORTERTEXT_H


#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>

#include <QObject>
#include <QTableView>
#include <QStringList>
#include <QSqlDatabase>

class EEO_Field
{
public:
    EEO_Field(const int ic, const QString &sf, const QString &st):
            iCol(ic),sFieldName(sf),sFieldType(st){}

    int     iCol;
    QString sFieldName;
    QString sFieldType;
};

class ExportPDFObject : public QObject
{
    Q_OBJECT
public:
    ExportPDFObject(const QString &filepath, const QString &sheettitle,
                      QTableView *tableview):PdfFilePath(filepath),
                      sheetName(sheettitle), tableView(tableview){}

    ~ExportPDFObject() {QSqlDatabase::removeDatabase("pdfexport");}

public:
    void setOutputFilePath(const QString &spath) {PdfFilePath = spath;}
    void setOutputSheetTitle(const QString &ssheet) {sheetName = ssheet;}
    void setTableView(QTableView *tableview) {tableView = tableview;}

    void addField(const int iCol, const QString &fieldname, const QString &fieldtype)
         {fieldList << new EEO_Field(iCol, fieldname, fieldtype);}

    void removeAllFields()
         {while (!fieldList.isEmpty()) delete fieldList.takeFirst();}

    int export2PDF();

signals:
    void exportedRowCount(int row);

private:
    QString PdfFilePath;
    QString sheetName;
    QTableView *tableView;
    QList<EEO_Field *> fieldList;
};

#endif // EXPORTEXCELOBJECT_H
