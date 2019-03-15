#ifndef DATAAPPLICATION_H
#define DATAAPPLICATION_H

#include <QtWidgets/QApplication>

#define dataApp (static_cast<DataApplication*>(QCoreApplication::instance()))


class DataApplicationPrivate;

class DataApplication : public QApplication
{
public:
#ifdef Q_QDOC
	DataApplication(int &argc, char **argv);
#else
	DataApplication(int &argc, char **argv, int = ApplicationFlags);
#endif
	virtual ~DataApplication();
public:
	bool	mbFirstShowAdv;
	qint32 mSystemVersion; //��¼����ϵͳ���ͣ�����xp��ϵͳ��0x0030,win7��0x0090�����

    bool has(const QString& key);
    QVariant value(const QString& key);
    void put(const QString& key,const QVariant& value);
private:
    DataApplicationPrivate* _d;
};

#endif // DATAAPPLICATION_H
