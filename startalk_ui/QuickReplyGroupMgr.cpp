#include "QuickReplyGroupMgr.h"
#include "Session.h"
#include "Player.h"
#include <QUuid>
#include "UIFrame.h"
#include "NotifyCenterController.h"
#include "gloableeventobject.h"
#include "QuickReplyMsgMgrV2.h"
/*******************************************
	QuickReplyGroupEditDlg
********************************************/

QuickReplyGroupEditDlg::QuickReplyGroupEditDlg(QWidget *parent,int opt) 
	: LocalManDialog(parent) { 
	setupUi(); 
	using namespace Qt;
	auto remove = WindowTitleHint;
	auto add = FramelessWindowHint /*| WindowMinMaxButtonsHint*/;
	setAttribute(Qt::WA_AlwaysShowToolTips, true);
	//setAttribute(Qt::WA_TranslucentBackground, true); 
	overrideWindowFlags( (Qt::WindowFlags)((windowFlags() & ~remove) | add)); 
	setWindowIcon(QIcon(":/Images/Deal_chat.ico")); 
	titlebar->setSizeable(false);
	titlebar->setMaxable(false);
	titlebar->setMinable(false);
	optionType = opt;
	if (optionType == 1){ 
		titlebar->setLeftTitle(QStringLiteral("�����"));
		setWindowTitle(QStringLiteral("�����"));
	} else { 
		titlebar->setLeftTitle(QStringLiteral("�༭��"));
		setWindowTitle(QStringLiteral("�༭��"));
	}
	connect(titlebar, &TitlebarWidget::sgCloseOnClicked, this, &QuickReplyGroupEditDlg::onClose);
	connect(pbSaveBtn, &QPushButton::clicked, this, &QuickReplyGroupEditDlg::onSaveGroup);
	connect(pbCancelBtn, &QPushButton::clicked, this, &QuickReplyGroupEditDlg::onCancelGroup);

} 
QuickReplyGroupEditDlg::~QuickReplyGroupEditDlg(){}
void QuickReplyGroupEditDlg::setupUi(){ 
	this->setObjectName(QStringLiteral("QuickReplyGroupEditDlg"));
    this->resize(300, 150);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
	
	widget_bk = new QWidget(this);
    widget_bk->setObjectName(QStringLiteral("widget_bk"));
	widget_bk->setGeometry(QRect(0, 0, this->width(), this->height()));
	
	titlebar = new TitlebarWidget(widget_bk);
    titlebar->setObjectName(QStringLiteral("titlebar"));
    titlebar->setGeometry(QRect(0, 0, this->width(), 30));

	groupNameLabel = new QLabel(widget_bk);
	groupNameLabel->setObjectName(QStringLiteral("groupNameLabel"));
	groupNameLabel->setGeometry(QRect(20, titlebar->geometry().bottom() + 5, this->width() - 40, 30)); 
	groupNameLabel->setText(QStringLiteral("������"));

	groupNameTextEdit = new QTextEdit(widget_bk);
	groupNameTextEdit->setObjectName(QStringLiteral("textEdit"));
	groupNameTextEdit->setGeometry(QRect(groupNameLabel->geometry().left(), groupNameLabel->geometry().bottom(), groupNameLabel->width(), this->height()-groupNameLabel->geometry().bottom()-62)); 
	 
	QRect bottomViewFrame;
	bottomViewFrame.setLeft(groupNameTextEdit->geometry().left());
	bottomViewFrame.setWidth(this->width() - 30);
	bottomViewFrame.setTop(groupNameTextEdit->geometry().bottom() + 10);
	bottomViewFrame.setHeight(40);
	bottomBtnView = new QWidget(widget_bk); 
    bottomBtnView->setObjectName(QStringLiteral("bottomBtnView"));
	bottomBtnView->setGeometry(bottomViewFrame); 
	 
	hBoxLayout = new QHBoxLayout(bottomBtnView);
    hBoxLayout->setObjectName(QStringLiteral("hBoxLayout"));

	bottomSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hBoxLayout->addItem(bottomSpacerItem);
	  
	pbSaveBtn = new QPushButton(bottomBtnView);
    pbSaveBtn->setObjectName(QStringLiteral("pbSaveBtn"));
	pbSaveBtn->setText(QStringLiteral("����"));
	hBoxLayout->addWidget(pbSaveBtn);

	pbCancelBtn = new QPushButton(bottomBtnView);
    pbCancelBtn->setObjectName(QStringLiteral("pbCancelBtn"));
	pbCancelBtn->setText(QStringLiteral("ȡ��"));
	hBoxLayout->addWidget(pbCancelBtn);
	
}

void QuickReplyGroupEditDlg::setGroupInfo(const QSharedPointer<Biz::QuickReplyGroup> &groupItem) { 
	editGroupItem = groupItem;
	groupNameTextEdit->setText(editGroupItem->GroupName());
}

/************************************************
	QuickReplyGroupEditDlg ��ť����¼�
************************************************/
void QuickReplyGroupEditDlg::onClose() {
	this->close();
}

void QuickReplyGroupEditDlg::onSaveGroup() { 
	QString name = groupNameTextEdit->toPlainText();
	if (name.length() > 5)
	{
		MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("������಻�ܳ���5����"));
		return;
	}
	if (name.length() <= 0)
	{
		MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("������Ҫ���õ�����"));
		return;
	}
	if (editGroupItem.isNull())
	{ 
		QSharedPointer<Biz::QuickReplyGroup> groupInfo(new Biz::QuickReplyGroup);
		QString guid = QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "");
		groupInfo->GroupCId(guid);
		groupInfo->GroupName(name);
		groupInfo->GroupSeq(Biz::Session::getServiceManager()->getDaoService()->getMaxQuickReplyGroupSeq()+1);
		groupInfo->GroupVersion(0);
		groupInfo->optionFlag(0);
		QList<QSharedPointer<Biz::QuickReplyGroup>> list;
		list.append(groupInfo);
		bool ret = Biz::Session::getServiceManager()->getDaoService()->saveQuickReplyGroupItems(list);
		if (ret)
		{
			setResult(QDialog::Accepted);
			this->done(QDialog::Accepted);
		} else
		{ 
			MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��������ʧ��"));
		}
	} else
	{ 
		editGroupItem->GroupName(name);
		QList<QSharedPointer<Biz::QuickReplyGroup>> list;
		list.append(editGroupItem);
		bool ret = Biz::Session::getServiceManager()->getDaoService()->updateQuickReplyGroupItems(list);
		if (ret)
		{
			setResult(QDialog::Accepted);
			this->done(QDialog::Accepted);
		} else
		{ 
			MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("�޸�����ʧ��"));
		}
	}
}

void QuickReplyGroupEditDlg::onCancelGroup() {
	setResult(QDialog::Rejected);
	this->done(QDialog::Rejected);
}

/***********************************************
	QuickReplyGroupMgr
*************************************************/
QuickReplyGroupMgr::QuickReplyGroupMgr(QWidget *parent)
	: LocalManDialog(parent)
{
	setupUi(); 
	
    mCallbackReceiver = new Biz::CallbackReceiver(this);

	using namespace Qt;
	auto remove = WindowTitleHint;
	auto add = FramelessWindowHint /*| WindowMinMaxButtonsHint*/;
	setAttribute(Qt::WA_AlwaysShowToolTips, true);
	//setAttribute(Qt::WA_TranslucentBackground, true); 
	overrideWindowFlags( (Qt::WindowFlags)((windowFlags() & ~remove) | add)); 
	setWindowIcon(QIcon(":/Images/Deal_chat.ico")); 
	setWindowTitle(QStringLiteral("��ݻظ������"));
	titlebar->setSizeable(false);
	titlebar->setMaxable(false);
	titlebar->setMinable(false);
	titlebar->setLeftTitle(QStringLiteral("�����ݻظ���"));

	connect(titlebar, &TitlebarWidget::sgCloseOnClicked, this, &QuickReplyGroupMgr::onClose); 
	connect(pbAdd, &QPushButton::clicked, this, &QuickReplyGroupMgr::onAddGroup);
	connect(pbDelete, &QPushButton::clicked, this, &QuickReplyGroupMgr::onDeleteGroup);
	connect(pbMody, &QPushButton::clicked, this, &QuickReplyGroupMgr::onModyGroup);
	connect(pbMoveTop, &QPushButton::clicked, this, &QuickReplyGroupMgr::onMoveUpGroup);
	connect(pbMoveDown, &QPushButton::clicked, this, &QuickReplyGroupMgr::onMoveDownGroup);
	connect(pbSaveBtn, &QPushButton::clicked, this, &QuickReplyGroupMgr::onSaveGroup);
	connect(pbCancelBtn, &QPushButton::clicked, this, &QuickReplyGroupMgr::onCancelGroup); 
	
	loadQuickReplyGroupData();

}

QuickReplyGroupMgr::~QuickReplyGroupMgr()
{

}

void QuickReplyGroupMgr::setupUi() { 

	this->setObjectName(QStringLiteral("QuickReplyGroupMgr"));
    this->resize(300, 350);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
	
	widget_bk = new QWidget(this);
    widget_bk->setObjectName(QStringLiteral("widget_bk"));
	widget_bk->setGeometry(QRect(0, 0, this->width(), this->height()));
	
	titlebar = new TitlebarWidget(widget_bk);
    titlebar->setObjectName(QStringLiteral("titlebar"));
    titlebar->setGeometry(QRect(0, 0, this->width(), 30));
	
	QRect groupListFrame;
	groupListFrame.setLeft(15); 
	groupListFrame.setTop(titlebar->geometry().top() + titlebar->geometry().height() + 10);
	groupListFrame.setWidth(this->width() - groupListFrame.left() - 150);
	groupListFrame.setHeight(this->height() - groupListFrame.top() - 60);
	groupListWidget = new QListWidget(widget_bk);
    groupListWidget->setObjectName(QStringLiteral("groupListWidget"));
    groupListWidget->setAlternatingRowColors(true);
	groupListWidget->setGeometry(groupListFrame);

	QRect rightOptionViewFrame;
	rightOptionViewFrame.setLeft(groupListFrame.left() + groupListFrame.width() + 20);
	rightOptionViewFrame.setWidth(this->width() - rightOptionViewFrame.left() - 20);
	rightOptionViewFrame.setTop(groupListFrame.top());
	rightOptionViewFrame.setHeight(groupListFrame.height());
	rigthOptionView = new QWidget(widget_bk); 
    rigthOptionView->setObjectName(QStringLiteral("rigthOptionView"));
	rigthOptionView->setGeometry(rightOptionViewFrame);

	verticalLayout = new QVBoxLayout(rigthOptionView);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    pbAdd = new QPushButton(rigthOptionView);
    pbAdd->setObjectName(QStringLiteral("pbAdd"));
	pbAdd->setText(QStringLiteral("����"));
    verticalLayout->addWidget(pbAdd);

    pbMody = new QPushButton(rigthOptionView);
    pbMody->setObjectName(QStringLiteral("pbMody"));
	pbMody->setText(QStringLiteral("�޸�"));
    verticalLayout->addWidget(pbMody);

	pbDelete = new QPushButton(rigthOptionView);
    pbDelete->setObjectName(QStringLiteral("pbDelete"));
	pbDelete->setText(QStringLiteral("ɾ��"));
	verticalLayout->addWidget(pbDelete);

	pbMoveTop = new QPushButton(rigthOptionView);
    pbMoveTop->setObjectName(QStringLiteral("pbMoveTop"));
	pbMoveTop->setText(QStringLiteral("����"));
	verticalLayout->addWidget(pbMoveTop);

	pbMoveDown = new QPushButton(rigthOptionView);
    pbMoveDown->setObjectName(QStringLiteral("pbDelete"));
	pbMoveDown->setText(QStringLiteral("����"));
	verticalLayout->addWidget(pbMoveDown);

	QRect bottomViewFrame;
	bottomViewFrame.setLeft(groupListFrame.left());
	bottomViewFrame.setWidth(this->width() - 30);
	bottomViewFrame.setTop(groupListFrame.bottom() + 10);
	bottomViewFrame.setHeight(40);
	bottomBtnView = new QWidget(widget_bk); 
    bottomBtnView->setObjectName(QStringLiteral("bottomBtnView"));
	bottomBtnView->setGeometry(bottomViewFrame); 
	 
	hBoxLayout = new QHBoxLayout(bottomBtnView);
    hBoxLayout->setObjectName(QStringLiteral("hBoxLayout"));

	bottomSpacerItem = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hBoxLayout->addItem(bottomSpacerItem);
	 
	pbCancelBtn = new QPushButton(bottomBtnView);
    pbCancelBtn->setObjectName(QStringLiteral("pbCancelBtn"));
	pbCancelBtn->setText(QStringLiteral("ȡ��"));
	hBoxLayout->addWidget(pbCancelBtn); 

	pbSaveBtn = new QPushButton(bottomBtnView);
    pbSaveBtn->setObjectName(QStringLiteral("pbSaveBtn"));
	pbSaveBtn->setText(QStringLiteral("�ϴ�����"));
	hBoxLayout->addWidget(pbSaveBtn); 

}

void QuickReplyGroupMgr::loadQuickReplyGroupData() {
	groupListWidget->clear();
	groupInfoList = Biz::Session::getServiceManager()->getDaoService()->getQuickReplyGroupItems();
	for ( QSharedPointer<Biz::QuickReplyGroup> groupItem : groupInfoList )
	{
		QListWidgetItem * listitem = new QListWidgetItem;
		listitem->setData(Qt::DisplayRole, groupItem->GroupName());
		listitem->setData(Qt::UserRole, groupItem->GroupCId());
		listitem->setToolTip(groupItem->GroupName());
		groupListWidget->addItem(listitem);  
	}
}

/************************************************

************************************************/
void QuickReplyGroupMgr::onClose(){ 
	this->close();
}

void QuickReplyGroupMgr::onAddGroup(){
	QuickReplyGroupEditDlg dlg(0,1);
	if (dlg.exec() == QDialog::Accepted)
	{
		loadQuickReplyGroupData();
		emit GloableEventObject::getInstance()->sgQuickReplyGroupChange();
	}
}
	
void QuickReplyGroupMgr::onModyGroup(){
	QItemSelectionModel *select = groupListWidget->selectionModel();
	if (select->hasSelection())
	{ 
		QModelIndexList indexlist;
		QModelIndex index;
		indexlist = select->selectedRows(); 
		int nRow = select->currentIndex().row(); 
		if (indexlist.count() > 0)
		{ 
			index = indexlist.at(0);  
			QSharedPointer<Biz::QuickReplyGroup> groupItem = groupInfoList.at(index.row());
			QuickReplyGroupEditDlg dlg(0,2);
			dlg.setGroupInfo(groupItem);
			if (dlg.exec() == QDialog::Accepted)
			{   
				loadQuickReplyGroupData();
				emit GloableEventObject::getInstance()->sgQuickReplyGroupChange();
			}
		} 
	} else
	{ 
        MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ѡ��Ҫ�޸ĵ�һ��"));
	}
}
	
void QuickReplyGroupMgr::onDeleteGroup(){
	QItemSelectionModel *select = groupListWidget->selectionModel();
	if (select->hasSelection())
	{ 
		QModelIndexList indexlist;
		QModelIndex index;
		indexlist = select->selectedRows(); 
		int nRow = select->currentIndex().row(); 
		if (indexlist.count() > 0)
		{ 
			index = indexlist.at(0);  
			QSharedPointer<Biz::QuickReplyGroup> groupItem = groupInfoList.at(index.row());
			bool ret = Biz::Session::getServiceManager()->getDaoService()->signDeleteQuickReplyGroup(groupItem->GroupCId());
			if (ret)
			{ 
				loadQuickReplyGroupData();
				emit GloableEventObject::getInstance()->sgQuickReplyGroupChange();
			} else { 
				MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("ɾ����ʧ��"));
			} 
		} 
	} else
	{ 
        MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ѡ��Ҫɾ����һ��"));
	}
}
	
void QuickReplyGroupMgr::onMoveUpGroup(){
	
	QItemSelectionModel *select = groupListWidget->selectionModel();
	if (select->hasSelection())
	{
		int nGroupRow = select->currentIndex().row();
		if (nGroupRow <= 0)
		{
			MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ǰѡ��������Ѿ��ǵ�һ��"));
		} else
		{
			int prepGroupRow = nGroupRow - 1;
			QSharedPointer<Biz::QuickReplyGroup> groupInfo = groupInfoList.at(nGroupRow);
			QSharedPointer<Biz::QuickReplyGroup> prepGroupInfo = groupInfoList.at(prepGroupRow);
			int currntSeq = groupInfo->GroupSeq();
			groupInfo->GroupSeq(prepGroupInfo->GroupSeq());
			prepGroupInfo->GroupSeq(currntSeq);
			QList<QSharedPointer<Biz::QuickReplyGroup>> uGroupList;
			uGroupList.append(groupInfo);
			uGroupList.append(prepGroupInfo);
			bool ret = Biz::Session::getServiceManager()->getDaoService()->updateQuickReplyGroupSeqs(uGroupList);
			if (ret)
			{
				loadQuickReplyGroupData();
				groupListWidget->setCurrentRow(prepGroupRow);
				emit GloableEventObject::getInstance()->sgQuickReplyContentChange(groupInfo->GroupCId());
			} else
			{
				 MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("�޸�����˳��ʧ��"));
			}
		}
	} else {
		MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ѡ��Ҫ�޸ĵ�һ��"));
	}
}
	
void QuickReplyGroupMgr::onMoveDownGroup(){
	QItemSelectionModel *select = groupListWidget->selectionModel();
	if (select->hasSelection())
	{
		int nGroupRow = select->currentIndex().row();
		if (nGroupRow >= groupInfoList.size()-1)
		{
			MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ǰѡ��������Ѿ��ǵ�һ��"));
		} else
		{
			int nextGroupRow = nGroupRow + 1;
			QSharedPointer<Biz::QuickReplyGroup> groupInfo = groupInfoList.at(nGroupRow);
			QSharedPointer<Biz::QuickReplyGroup> prepGroupInfo = groupInfoList.at(nextGroupRow);
			int currntSeq = groupInfo->GroupSeq();
			groupInfo->GroupSeq(prepGroupInfo->GroupSeq());
			prepGroupInfo->GroupSeq(currntSeq);
			QList<QSharedPointer<Biz::QuickReplyGroup>> uGroupList;
			uGroupList.append(groupInfo);
			uGroupList.append(prepGroupInfo);
			bool ret = Biz::Session::getServiceManager()->getDaoService()->updateQuickReplyGroupSeqs(uGroupList);
			if (ret)
			{
				loadQuickReplyGroupData();
				groupListWidget->setCurrentRow(nextGroupRow);
				emit GloableEventObject::getInstance()->sgQuickReplyGroupChange();
			} else
			{
				 MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("�޸�����˳��ʧ��"));
			}
		}
	} else {
		MainApp::UIFrame::getNotifyCenterController ()->alertMessage (QStringLiteral("��ѡ��Ҫ�޸ĵ�һ��"));
	}
}
	
void QuickReplyGroupMgr::onSaveGroup(){
		auto callback = mCallbackReceiver->createCallback<QMap<QString, QVariant>>(
		[this](const QMap<QString, QVariant> &result){  
			bool ret = result.value("ret").toBool();
			if (ret)
			{ 
				bool groupChange = result.value("groupChange").toBool();
				bool contentChange = result.value("contentChange").toBool();
				if (groupChange)
				{
					emit GloableEventObject::getInstance()->sgQuickReplyGroupChange();
				}
				if (contentChange)
				{
					emit GloableEventObject::getInstance()->sgQuickReplyAllContentChange();
				}
			} else
			{
				QString errMsg = result.value("errmsg").toString();
				MainApp::UIFrame::getNotifyCenterController ()->alertMessage (errMsg);
			}
		},[]{}); 
	QuickReplyMsgMgrV2::getInstance()->syncQuickReplyToRemote(callback); 
	this->close();
}
	
void QuickReplyGroupMgr::onCancelGroup(){
	this->close();
}