#ifndef ADVERCONFIGINFO_H
#define ADVERCONFIGINFO_H
#include <QObject>
#include "../LocalManUtils/IJsonSerializeable.h"

namespace Biz
{
	class AdvlistNode : public IJsonSerializeable
	{
		Q_OBJECT
	public:
		AdvlistNode(QObject* parent):IJsonSerializeable(parent){
			adtype(0);
			imgurl("");
			linkurl("");
		};
		~AdvlistNode(){};
		JPROPERTY(int, adtype);
		JPROPERTY(QString, imgurl);
		JPROPERTY(QString, linkurl)
	};

	class AdverConfigInfo : public IJsonSerializeable
	{
		Q_OBJECT

	public:
		AdverConfigInfo(QObject *parent=NULL) : IJsonSerializeable(parent)
		{
			version(0);
			adsce(0);
			carousel(false);
			carouseldelay(0);
			shown(true);
			allowskip(false);
			skiptips("");
			LastUpdateAdvTime(0);

		};
       
         ~AdverConfigInfo(){ };


		JPROPERTY(int,version); //��ǰ�汾��
		JPROPERTY(int,adsce); //�����ʾʱ��
		JPROPERTY(bool,carousel); //�Ƿ��ֲ�
		JPROPERTY(int,carouseldelay); //�ֲ��ļ��ʱ��
		JPROPERTY(bool,shown); //�Ƿ���ʾ false ���������
		JPROPERTY(bool,allowskip); // �Ƿ���������
		JPROPERTY(QString,skiptips); // ��������ʱ����ʾ��Ϣ
		JPROPERTY(QList<IJsonSerializeable*>,adlist);
		JPROPERTY(quint64, LastUpdateAdvTime);
	protected:
		virtual void unserializeItem(const QString& key,QVariant v)
		{
			if ("adlist" == key)
			{
				AdvlistNode* ptemn = new AdvlistNode(this);
				ptemn->innerUnserialize(v);
				madlist.append(ptemn);
			}
		}

	};
}
#endif // ADVERCONFIGINFO_H
