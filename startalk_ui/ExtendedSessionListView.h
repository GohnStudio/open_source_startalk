#ifndef EXTENDEDSESSIONLISTVIEW_H
#define EXTENDEDSESSIONLISTVIEW_H

#include <QWidget>

#include "RosterListWidget.h"
class CombinationListView;
class GroupListView;
class FriendsListView;
class RosterTreeView;
class PublicAccountListView;
class BlackNameListView;
class WechatUserListView;
class CollectionTreeView;
class StarPersonListView;

namespace Ui
{
	 class ExtendedSessionListView;
	 
}
class ExtendedSessionListView : public QWidget
{
    Q_OBJECT

public:
    ExtendedSessionListView(QWidget *parent = 0);
    ~ExtendedSessionListView();
public:
    QWidget* getContentView() const;;
    QString getBelongExtendid()const;;
    void setBelongExtendid(const QString& id);;

    QString getLindedId();
    void setLindedId(const QString& id);
	ExtendedSessionListView* getCombinationListView() const;
public:
    void setExtendTitle(const QString& title);
    void setExtendTitleVisable(bool visable);

protected:
	void setContentView(QWidget* pWidget);
protected:
    Ui::ExtendedSessionListView *ui;
private:
    QString beLongExtendId;
    QString lindItemId;
   
	QWidget* mpContentView;

signals:
    void sgBackButtonClicked(const QString& userid);
};

//����Ự�б�
class RecentExtendedSessionListView:public ExtendedSessionListView
{
public:
	RecentExtendedSessionListView(QWidget*parent = 0);
	~RecentExtendedSessionListView();
public:
	RosterListWidget* getRosterListView() const;
	RosterListWidget* getCombinationListView() const;
};

//����б�ĵ�һ���б�
class CombinationExtendedSessionListView:public ExtendedSessionListView
{
public:
	CombinationExtendedSessionListView(QWidget*parent = 0);
	~CombinationExtendedSessionListView();
public:
	CombinationListView* getCombinationListView() const;
};

//����б�ĵڶ����б��е��Ǳ��Ǳ���ϵ��
class CombinationOfStarPersonExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfStarPersonExtendedListView(QWidget*parent = 0);
	~CombinationOfStarPersonExtendedListView();
public:
	StarPersonListView* getCombinationListView() const;
};

//����б�ĵڶ����б��е�Ⱥ��
class CombinationOfGroupExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfGroupExtendedListView(QWidget*parent = 0);
	~CombinationOfGroupExtendedListView();
public:
	GroupListView* getCombinationListView() const;
};

//����б�ĵڶ����б��е���֯�ܹ�
class CombinationOfOrganiExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfOrganiExtendedListView(QWidget*parent = 0);
	~CombinationOfOrganiExtendedListView();
public:
	RosterTreeView* getCombinationListView() const;
};

//����б�ĵڶ����б��еĺ���
class CombinationOfFriendExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfFriendExtendedListView(QWidget*parent = 0);
	~CombinationOfFriendExtendedListView();
public:
	FriendsListView* getCombinationListView() const;
};

//����б��еĵڶ����б��еĹ��ں�
class CombinationOfPublicAccountExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfPublicAccountExtendedListView(QWidget*parent = 0);
	~CombinationOfPublicAccountExtendedListView();
public:
	PublicAccountListView* getCombinationListView() const;
};

//����б��еĵڶ����б��еĺ�����
class CombinationOfBlackNameExtendedListView:public ExtendedSessionListView
{
public:
	CombinationOfBlackNameExtendedListView(QWidget*parent = 0);
	~CombinationOfBlackNameExtendedListView();
public:
	BlackNameListView* getCombinationListView() const;
};

class CombinationOfWechatsExtendedListView:public ExtendedSessionListView
{
public:
    CombinationOfWechatsExtendedListView(QWidget*parent = 0);
    ~CombinationOfWechatsExtendedListView();
public:
    WechatUserListView* getCombinationListView() const;
};

//���յ���չ
class CollectionExtendedListView:public ExtendedSessionListView
{
public:
	CollectionExtendedListView(QWidget*parent = 0);
	~CollectionExtendedListView();
public:
	CollectionTreeView* getcollectionListView() const;
	CollectionTreeView* getCombinationListView() const;
};
#endif // EXTENDEDSESSIONLISTVIEW_H
